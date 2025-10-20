/*
 * ESP32 Orchestra Conductor Main - ESP-IDF Version
 * ผู้บังคับการวงดนตรีที่ควบคุมการเล่นเพลงผ่าน ESP-NOW
 * 
 * หน้าที่:
 * 1. จัดการเพลงและแบ่ง parts ให้ musicians
 * 2. ส่งคำสั่งผ่าน ESP-NOW broadcast
 * 3. ซิงค์เวลาให้ musicians เล่นพร้อมกัน
 * 4. ควบคุมการเริ่ม/หยุดเพลง
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "orchestra_common.h"
#include "midi_songs.h"
#include "espnow_conductor.h"

static const char *TAG = "MAIN";

// External function from espnow_conductor.c
extern void conductor_send_song_events(void);

// Button and LED state
static uint8_t selected_index = 0; // ✅ ใช้อิง index ใน all_songs[] (0..TOTAL_SONGS-1)
static led_pattern_t current_led_pattern = LED_SLOW_BLINK;
static uint32_t led_last_update = 0;
static bool led_state = false;

// Task handles
static TaskHandle_t button_task_handle = NULL;
static TaskHandle_t led_task_handle = NULL;
static TaskHandle_t orchestra_task_handle = NULL;

// Function Prototypes
static void setup_gpio(void);
static void button_task(void *pvParameters);
static void led_task(void *pvParameters);
static void orchestra_task(void *pvParameters);
static void handle_button_press(uint32_t press_duration);

void app_main(void) {
    ESP_LOGI(TAG, "🎵 ESP32 Orchestra Conductor Starting...");
    
    // Setup GPIO
    setup_gpio();
    
    // Initialize ESP-NOW
    esp_err_t ret = espnow_conductor_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "❌ Failed to initialize ESP-NOW: %s", esp_err_to_name(ret));
        current_led_pattern = LED_FAST_BLINK; // Error pattern
    } else {
        current_led_pattern = LED_SLOW_BLINK; // Ready pattern
        ESP_LOGI(TAG, "✅ Conductor ready!");
    }
    
    // Display available songs
    ESP_LOGI(TAG, "🎼 Available songs (TOTAL_SONGS=%d):", (int)TOTAL_SONGS);
    for (int i = 0; i < (int)TOTAL_SONGS; i++) {
        ESP_LOGI(TAG, "   [%d] %s (id=%d, parts=%d, %d BPM)", 
                 i, 
                 all_songs[i].song_name,
                 all_songs[i].song_id,
                 all_songs[i].part_count,
                 all_songs[i].tempo_bpm);
    }
    if (TOTAL_SONGS == 0) {
        ESP_LOGW(TAG, "⚠️  No songs registered in all_songs[].");
    } else {
        ESP_LOGI(TAG, "➡️  Default selected: [%d] %s", selected_index, all_songs[selected_index].song_name);
    }
    ESP_LOGI(TAG, "📝 Short press BOOT: cycle songs | Long press: Play/Stop");
    
    // Create tasks
    xTaskCreate(button_task, "button_task", 2048, NULL, 5, &button_task_handle);
    xTaskCreate(led_task, "led_task", 2048, NULL, 3, &led_task_handle);
    xTaskCreate(orchestra_task, "orchestra_task", 4096, NULL, 4, &orchestra_task_handle);
    
    ESP_LOGI(TAG, "🚀 All tasks created, conductor is running!");
}

static void setup_gpio(void) {
    // Configure LED pin
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << STATUS_LED),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);
    gpio_set_level(STATUS_LED, 0);
    
    // Configure button pin (BOOT button)
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&button_config);
    
    ESP_LOGI(TAG, "✅ GPIO setup complete");
}

static void button_task(void *pvParameters) {
    bool last_button_state = true; // Pull-up, so true when not pressed
    uint32_t button_press_start = 0;
    
    while (1) {
        bool current_button_state = gpio_get_level(BUTTON_PIN);
        uint32_t current_time = get_time_ms();
        
        // Button press detection (active LOW)
        if (last_button_state == true && current_button_state == false) {
            button_press_start = current_time;
            ESP_LOGD(TAG, "🔘 Button pressed");
        }
        
        // Button release detection
        if (last_button_state == false && current_button_state == true) {
            uint32_t press_duration = current_time - button_press_start;
            handle_button_press(press_duration);
        }
        
        last_button_state = current_button_state;
        vTaskDelay(pdMS_TO_TICKS(50)); // Check every 50ms
    }
}

static void handle_button_press(uint32_t press_duration) {
    if (press_duration < 1000) {
        // Short press: Cycle through songs by INDEX (ไม่อิง song_id)
        if (TOTAL_SONGS == 0) {
            ESP_LOGW(TAG, "⚠️  No songs to select.");
            return;
        }
        selected_index = (uint8_t)((selected_index + 1) % TOTAL_SONGS);

        const orchestra_song_t* song = &all_songs[selected_index];
        ESP_LOGI(TAG, "🎵 Selected: [%d] %s (id=%d)", selected_index, song->song_name, song->song_id);
        
        // Quick LED flash to indicate selection
        gpio_set_level(STATUS_LED, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(STATUS_LED, 0);

    } else {
        // Long press: Start/Stop song
        if (TOTAL_SONGS == 0) {
            ESP_LOGW(TAG, "⚠️  No songs registered; cannot play.");
            return;
        }
        const orchestra_song_t* song = &all_songs[selected_index];

        if (is_conductor_playing()) {
            // Stop current song
            if (stop_song()) {
                ESP_LOGI(TAG, "⏹️  Stopped: %s", song->song_name);
                current_led_pattern = LED_SLOW_BLINK;
            } else {
                ESP_LOGE(TAG, "❌ Failed to stop song");
                current_led_pattern = LED_FAST_BLINK;
            }
        } else {
            // Start selected song (ส่งเป็น song_id ของ element นั้น)
            if (start_song(song->song_id)) {
                ESP_LOGI(TAG, "▶️  Playing: [%d] %s (id=%d)", selected_index, song->song_name, song->song_id);
                current_led_pattern = LED_ON;
            } else {
                ESP_LOGE(TAG, "❌ Failed to start song");
                current_led_pattern = LED_FAST_BLINK;
            }
        }
    }
}

static void led_task(void *pvParameters) {
    while (1) {
        uint32_t current_time = get_time_ms();
        
        switch (current_led_pattern) {
            case LED_OFF:
                gpio_set_level(STATUS_LED, 0);
                break;
            case LED_ON:
                gpio_set_level(STATUS_LED, 1);
                break;
            case LED_SLOW_BLINK: // 1 Hz
                if (current_time - led_last_update > 500) {
                    led_state = !led_state;
                    gpio_set_level(STATUS_LED, led_state);
                    led_last_update = current_time;
                }
                break;
            case LED_FAST_BLINK: // 5 Hz
                if (current_time - led_last_update > 100) {
                    led_state = !led_state;
                    gpio_set_level(STATUS_LED, led_state);
                    led_last_update = current_time;
                }
                break;
            case LED_HEARTBEAT: { // Double pulse
                static uint8_t heartbeat_phase = 0;
                static uint32_t heartbeat_timer = 0;
                if (current_time - heartbeat_timer > 100) {
                    switch (heartbeat_phase) {
                        case 0: case 2: gpio_set_level(STATUS_LED, 1); break;
                        case 1: case 3: gpio_set_level(STATUS_LED, 0); break;
                        default: heartbeat_phase = 0; break;
                    }
                    heartbeat_phase = (heartbeat_phase + 1) % 20; // 2 seconds cycle
                    heartbeat_timer = current_time;
                }
                break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Update every 10ms
    }
}

static void orchestra_task(void *pvParameters) {
    uint32_t last_heartbeat = 0;
    
    while (1) {
        uint32_t current_time = get_time_ms();
        
        // Send song events if playing
        conductor_send_song_events();
        
        // Send periodic heartbeat
        if (current_time - last_heartbeat > 5000) { // Every 5 seconds
            send_heartbeat();
            last_heartbeat = current_time;
        }
        
        // Update conductor status
        update_conductor_status();
        
        vTaskDelay(pdMS_TO_TICKS(10)); // Update every 10ms for precise timing
    }
}
