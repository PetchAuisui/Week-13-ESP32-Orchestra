#ifndef MIDI_SONGS_H
#define MIDI_SONGS_H

#include "orchestra_common.h"

// Note Event Structure for Orchestra
typedef struct
{
    uint8_t note;         // MIDI note number (0 = rest)
    uint16_t duration_ms; // ความยาวโน๊ต
    uint16_t delay_ms;    // หน่วงเวลาก่อนโน๊ตถัดไป
} note_event_t;

// Song Part Structure
typedef struct
{
    const note_event_t *events; // Array ของโน๊ต
    uint16_t event_count;       // จำนวนโน๊ต
    const char *part_name;      // ชื่อ part
} song_part_t;

// Complete Song Structure
typedef struct
{
    const char *song_name;    // ชื่อเพลง
    uint8_t song_id;          // รหัสเพลง
    uint8_t tempo_bpm;        // Beats per minute
    uint8_t part_count;       // จำนวน parts
    const song_part_t *parts; // Array ของ parts
} orchestra_song_t;

// =============================================================
// 🎵 SONG 1: Twinkle Twinkle Little Star (4 Parts)
// =============================================================

// Part A: Main Melody
static const note_event_t twinkle_melody[] = {
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 800, 200},

    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_C4, 800, 200},

    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 800, 200},

    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 800, 200},

    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 800, 200},

    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_C4, 800, 400},
    {NOTE_REST, 0, 0}};

// Part B: Harmony (3rd above melody)
static const note_event_t twinkle_harmony[] = {
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_C5, 400, 100},
    {NOTE_C5, 400, 100},
    {NOTE_B4, 800, 200},

    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 800, 200},

    {NOTE_B4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 800, 200},

    {NOTE_B4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 800, 200},

    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_B4, 400, 100},
    {NOTE_C5, 400, 100},
    {NOTE_C5, 400, 100},
    {NOTE_B4, 800, 200},

    {NOTE_A4, 400, 100},
    {NOTE_A4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_F4, 400, 100},
    {NOTE_E4, 800, 400},
    {NOTE_REST, 0, 0}};

// Part C: Bass Line (octave lower)
static const note_event_t twinkle_bass[] = {
    {NOTE_C3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},

    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_G3, 800, 200},
    {NOTE_C3, 800, 200},

    {NOTE_C3, 800, 200},
    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_G3, 800, 200},

    {NOTE_C3, 800, 200},
    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_G3, 800, 200},

    {NOTE_C3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},

    {NOTE_F3, 800, 200},
    {NOTE_C3, 800, 200},
    {NOTE_G3, 800, 200},
    {NOTE_C3, 800, 400},
    {NOTE_REST, 0, 0}};

// Part D: Rhythm/Percussion (using different frequencies)
static const note_event_t twinkle_rhythm[] = {
    {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 200}, {NOTE_REST, 0, 200}, {NOTE_G3, 200, 600},

    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 600},

    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 600},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 600},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 200},
    {NOTE_REST, 0, 200},
    {NOTE_G3, 200, 400},
    {NOTE_REST, 0, 0}};

// Twinkle Star Parts Array
static const song_part_t twinkle_parts[] = {
    {twinkle_melody, (uint16_t)(sizeof(twinkle_melody) / sizeof(note_event_t) - 1), "Melody"},
    {twinkle_harmony, (uint16_t)(sizeof(twinkle_harmony) / sizeof(note_event_t) - 1), "Harmony"},
    {twinkle_bass, (uint16_t)(sizeof(twinkle_bass) / sizeof(note_event_t) - 1), "Bass"},
    {twinkle_rhythm, (uint16_t)(sizeof(twinkle_rhythm) / sizeof(note_event_t) - 1), "Rhythm"}};

// =============================================================
// 🎵 SONG 2: Happy Birthday (3 Parts)
// =============================================================

// Part A: Main Melody
static const note_event_t birthday_melody[] = {
    {NOTE_REST, 0, 400},
    {NOTE_C4, 200, 100},
    {NOTE_C4, 400, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 800, 100},
    {NOTE_F4, 800, 100},
    {NOTE_E4, 1200, 200},

    {NOTE_C4, 200, 100},
    {NOTE_C4, 400, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 800, 100},
    {NOTE_G4, 800, 100},
    {NOTE_F4, 1200, 200},

    {NOTE_C4, 200, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C5, 800, 100},
    {NOTE_A4, 800, 100},
    {NOTE_F4, 800, 100},
    {NOTE_E4, 800, 100},
    {NOTE_D4, 1200, 200},

    {NOTE_B4, 200, 100},
    {NOTE_B4, 400, 100},
    {NOTE_A4, 800, 100},
    {NOTE_F4, 800, 100},
    {NOTE_G4, 800, 100},
    {NOTE_F4, 1200, 400},
    {NOTE_REST, 0, 0}};

// Part B: Harmony
static const note_event_t birthday_harmony[] = {
    {NOTE_REST, 0, 400},
    {NOTE_A3, 200, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 800, 100},
    {NOTE_A3, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 1200, 200},

    {NOTE_A3, 200, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 800, 100},
    {NOTE_A3, 800, 100},
    {NOTE_E4, 800, 100},
    {NOTE_D4, 1200, 200},

    {NOTE_A3, 200, 100},
    {NOTE_A3, 400, 100},
    {NOTE_A4, 800, 100},
    {NOTE_F4, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_C4, 800, 100},
    {NOTE_B3, 1200, 200},

    {NOTE_G4, 200, 100},
    {NOTE_G4, 400, 100},
    {NOTE_F4, 800, 100},
    {NOTE_D4, 800, 100},
    {NOTE_E4, 800, 100},
    {NOTE_D4, 1200, 400},
    {NOTE_REST, 0, 0}};

// Part C: Bass
static const note_event_t birthday_bass[] = {
    {NOTE_REST, 0, 400},
    {NOTE_F3, 600, 200},
    {NOTE_F3, 800, 100},
    {NOTE_C3, 800, 100},
    {NOTE_F3, 800, 100},
    {NOTE_C3, 1200, 200},

    {NOTE_F3, 600, 200},
    {NOTE_F3, 800, 100},
    {NOTE_C3, 800, 100},
    {NOTE_G3, 800, 100},
    {NOTE_F3, 1200, 200},

    {NOTE_F3, 600, 200},
    {NOTE_F3, 800, 100},
    {NOTE_F3, 800, 100},
    {NOTE_F3, 800, 100},
    {NOTE_B3, 800, 100},
    {NOTE_A3, 800, 100},
    {NOTE_G3, 1200, 200},

    {NOTE_G3, 600, 200},
    {NOTE_G3, 800, 100},
    {NOTE_F3, 800, 100},
    {NOTE_F3, 800, 100},
    {NOTE_C3, 800, 100},
    {NOTE_F3, 1200, 400},
    {NOTE_REST, 0, 0}};

// Happy Birthday Parts Array
static const song_part_t birthday_parts[] = {
    {birthday_melody, (uint16_t)(sizeof(birthday_melody) / sizeof(note_event_t) - 1), "Melody"},
    {birthday_harmony, (uint16_t)(sizeof(birthday_harmony) / sizeof(note_event_t) - 1), "Harmony"},
    {birthday_bass, (uint16_t)(sizeof(birthday_bass) / sizeof(note_event_t) - 1), "Bass"}};

// =============================================================
// 🎵 SONG 3: Mary Had a Little Lamb (2 Parts)
// =============================================================

// Part A: Melody
static const note_event_t mary_melody[] = {
    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 800, 200},

    {NOTE_D4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_D4, 800, 200},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 800, 200},

    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_E4, 400, 100},
    {NOTE_D4, 400, 100},
    {NOTE_C4, 800, 400},
    {NOTE_REST, 0, 0}};

// Part B: Harmony
static const note_event_t mary_harmony[] = {
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 800, 200},

    {NOTE_B3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_B3, 800, 200},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 800, 200},

    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_A3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_C4, 400, 100},
    {NOTE_B3, 400, 100},
    {NOTE_A3, 800, 400},
    {NOTE_REST, 0, 0}};

// Mary Parts Array
static const song_part_t mary_parts[] = {
    {mary_melody, (uint16_t)(sizeof(mary_melody) / sizeof(note_event_t) - 1), "Melody"},
    {mary_harmony, (uint16_t)(sizeof(mary_harmony) / sizeof(note_event_t) - 1), "Harmony"}};

// =============================================================
// 🎵 SONG 4: เต่า (Taotao)
//    - Key: C Major
//    - Tempo is assumed (e.g., Quarter Note = 400ms)
//    - {NOTE, Duration_ms, Volume}
// =============================================================

// Part A: Main Melody
static const note_event_t taotao_melody[] = {
    // ท่อน 1: "เต่า เต่า เต่า"
    {NOTE_G4, 400, 100}, // เต่า (Quarter Note)
    {NOTE_G4, 400, 100}, // เต่า
    {NOTE_G4, 400, 100}, // เต่า
    {NOTE_G4, 400, 100}, // *พัก* / เชื่อม

    // "นา"
    {NOTE_A4, 400, 100}, // นา
    {NOTE_G4, 400, 100}, // *พัก*
    {NOTE_F4, 400, 100}, // *พัก*
    {NOTE_E4, 400, 100}, // *พัก*

    // ท่อน 2: "มันมีสี่ขา"
    {NOTE_C4, 400, 100}, // มัน
    {NOTE_C4, 400, 100}, // มี
    {NOTE_C4, 400, 100}, // สี่
    {NOTE_C4, 400, 100}, // ขา

    // "สี่ตีนเดินมา"
    {NOTE_D4, 400, 100}, // สี่
    {NOTE_D4, 400, 100}, // ตีน
    {NOTE_D4, 400, 100}, // เดิน
    {NOTE_D4, 400, 100}, // มา

    // ท่อน 3: "มันทำหัว"
    {NOTE_G4, 400, 100}, // มัน
    {NOTE_G4, 400, 100}, // ทำ
    {NOTE_G4, 400, 100}, // หัว
    {NOTE_G4, 400, 100}, // *พัก* / เชื่อม

    // "ผลุบโผล่"
    {NOTE_A4, 400, 100}, // ผลุบ
    {NOTE_G4, 400, 100}, // โผล่
    {NOTE_F4, 400, 100}, // *พัก*
    {NOTE_E4, 400, 100}, // *พัก*

    // ท่อน 4: "มันทำหัว" (ซ้ำ)
    {NOTE_C4, 400, 100}, // มัน
    {NOTE_C4, 400, 100}, // ทำ
    {NOTE_C4, 400, 100}, // หัว
    {NOTE_C4, 400, 100}, // *พัก* / เชื่อม

    // "ผลุบโผล่" (ซ้ำ)
    {NOTE_D4, 400, 100}, // ผลุบ
    {NOTE_C4, 400, 100}, // โผล่
    {NOTE_REST, 400, 0}, // *พัก*
    {NOTE_REST, 400, 0}, // *พัก*

    {NOTE_REST, 0, 0} // End
};

// Part B: Harmony (Simple Octave Down / Supporting Thirds)
static const note_event_t taotao_harmony[] = {
    // ท่อน 1: "เต่า เต่า เต่า"
    {NOTE_G3, 400, 80}, // Harmony (Octave below)
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},

    // "นา"
    {NOTE_F4, 400, 80}, // Harmony (Lower Third)
    {NOTE_E4, 400, 80},
    {NOTE_D4, 400, 80},
    {NOTE_C4, 400, 80},

    // ท่อน 2: "มันมีสี่ขา"
    {NOTE_G3, 400, 80}, // Harmony (Lower Octave/Fifth)
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},

    // "สี่ตีนเดินมา"
    {NOTE_F3, 400, 80}, // Harmony (Lower Third)
    {NOTE_F3, 400, 80},
    {NOTE_F3, 400, 80},
    {NOTE_F3, 400, 80},

    // ท่อน 3: "มันทำหัว"
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},

    // "ผลุบโผล่"
    {NOTE_F4, 400, 80},
    {NOTE_E4, 400, 80},
    {NOTE_D4, 400, 80},
    {NOTE_C4, 400, 80},

    // ท่อน 4: "มันทำหัว" (ซ้ำ)
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_G3, 400, 80},

    // "ผลุบโผล่" (ซ้ำ)
    {NOTE_F3, 400, 80},
    {NOTE_G3, 400, 80},
    {NOTE_REST, 400, 0},
    {NOTE_REST, 400, 0},

    {NOTE_REST, 0, 0}};

// Taotao Parts Array
static const song_part_t taotao_parts[] = {
    {taotao_melody, sizeof(taotao_melody) / sizeof(note_event_t) - 1, "Melody"},
    {taotao_harmony, sizeof(taotao_harmony) / sizeof(note_event_t) - 1, "Harmony"}};
// =============================================================
// 🎵 SONG 4: Baby Shark (extended 9 verses) — 3 buzzers, Key: G
//    A: Melody  B: Ostinato ("doo doo")  C: Bass
//    duration_ms = เวลาเปิดเสียง, delay_ms = หน่วงก่อนโน้ตถัดไป
// =============================================================

// ---------- Ostinato helpers ----------
#define DOO_NOTE_DUR 150
#define DOO_NOTE_GAP 100
#define DOO_COUNT 6
#define DOO_PHRASE_MS ((DOO_NOTE_DUR + DOO_NOTE_GAP) * DOO_COUNT) // 1500ms

#define DOO_DOO_CHUNK                                                                 \
    {NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP}, {NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP},     \
        {NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP}, {NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP}, \
        {NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP}, { NOTE_G3, DOO_NOTE_DUR, DOO_NOTE_GAP }

// หนึ่ง verse ของ Ostinato = 3 บล็อก "doo" + เว้นให้ Melody ช่วงตะโกน + เว้นเล็กน้อย
#define OST_VERSE                                                           \
    DOO_DOO_CHUNK, {NOTE_REST, 0, 0},                                       \
        DOO_DOO_CHUNK, {NOTE_REST, 0, 0},                                   \
        DOO_DOO_CHUNK, {NOTE_REST, 0, 200},                                 \
        /* support shout (เบา ๆ) */ {NOTE_G3, 200, 80}, {NOTE_G3, 200, 80}, \
        {NOTE_REST, 0, 400}

// ---------- Melody helpers ----------
#define MELODY_PHRASE(N1, N2, N3) \
    {N1, 200, 100}, {N2, 200, 100}, {N3, 400, 0}, { NOTE_REST, 0, DOO_PHRASE_MS }

// หนึ่ง verse ของ Melody = 3 phrase + โน้ตยาวตบท้าย + เว้นเล็กน้อย
#define MELODY_VERSE(N1, N2, N3, FINAL) \
    MELODY_PHRASE(N1, N2, N3),          \
        MELODY_PHRASE(N1, N2, N3),      \
        MELODY_PHRASE(N1, N2, N3),      \
        {FINAL, 800, 200}, {NOTE_REST, 0, 400}

// -----------------------------
// Part A: Melody (Lead voice)
// -----------------------------
static const note_event_t baby_shark_melody[] = {
    // 1) Baby Shark (D–E–G) → End on G4
    MELODY_VERSE(NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4),

    // 2) Mommy Shark (G–A–C5) → End on C5
    MELODY_VERSE(NOTE_G4, NOTE_A4, NOTE_C5, NOTE_C5),

    // 3) Daddy Shark (A–B–D5) → End on D5
    MELODY_VERSE(NOTE_A4, NOTE_B4, NOTE_D5, NOTE_D5),

    // 4) Grandma Shark (E–F#–A4) → End on A4
    MELODY_VERSE(NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_A4),

    // 5) Grandpa Shark (B–C#–E4) → End on E4
    MELODY_VERSE(NOTE_B3, NOTE_CS4, NOTE_E4, NOTE_E4),

    // 6) Let's go hunt (กลับมาทำนองหลัก D–E–G) → End on G4
    MELODY_VERSE(NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4),

    // 7) Run away (วิ่งหนี เพิ่มความตึงด้วย A–B–D5) → End on D5
    MELODY_VERSE(NOTE_A4, NOTE_B4, NOTE_D5, NOTE_D5),

    // 8) Safe at last (ปลอดภัย เนียนลงมาที่ G–A–C5) → End on C5
    MELODY_VERSE(NOTE_G4, NOTE_A4, NOTE_C5, NOTE_C5),

    // 9) It’s the end (ปิดเพลง กลับทำนอง D–E–G) → End ยาวบน G4
    MELODY_VERSE(NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4),

    {NOTE_REST, 0, 0}};

// -----------------------------------------
// Part B: Ostinato — “doo doo doo ...”
// -----------------------------------------
static const note_event_t baby_shark_ostinato[] = {
    // รองรับ 9 verses เต็ม
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    OST_VERSE,
    {NOTE_REST, 0, 0}};

// -----------------------------
// Part C: Bass (root / I–IV–V สีสันเปลี่ยนราย verse)
// -----------------------------
#define BASS_BLOCK(ROOT) {ROOT, 800, 100}, {ROOT, 600, 0} // ≈ 1500ms ต่อบล็อก doo
#define BASS_VERSE(R1, R2, R3, SHOUT)               \
    BASS_BLOCK(R1), BASS_BLOCK(R2), BASS_BLOCK(R3), \
        {SHOUT, 600, 0}, {NOTE_REST, 0, 400}

static const note_event_t baby_shark_bass[] = {
    // 1) I–I–I (G–G–G)
    BASS_VERSE(NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2),

    // 2) I–IV–V (G–C–D)
    BASS_VERSE(NOTE_G2, NOTE_C3, NOTE_D3, NOTE_G2),

    // 3) I–V–I (G–D–G)
    BASS_VERSE(NOTE_G2, NOTE_D3, NOTE_G2, NOTE_G2),

    // 4) IV–I–V (C–G–D)
    BASS_VERSE(NOTE_C3, NOTE_G2, NOTE_D3, NOTE_G2),

    // 5) I–IV–I (G–C–G)
    BASS_VERSE(NOTE_G2, NOTE_C3, NOTE_G2, NOTE_G2),

    // 6) I–I–V (G–G–D)
    BASS_VERSE(NOTE_G2, NOTE_G2, NOTE_D3, NOTE_G2),

    // 7) V–IV–I (D–C–G)
    BASS_VERSE(NOTE_D3, NOTE_C3, NOTE_G2, NOTE_G2),

    // 8) IV–I–IV (C–G–C)
    BASS_VERSE(NOTE_C3, NOTE_G2, NOTE_C3, NOTE_G2),

    // 9) I–V–I (G–D–G) ปิดกลับบ้าน
    BASS_VERSE(NOTE_G2, NOTE_D3, NOTE_G2, NOTE_G2),

    {NOTE_REST, 0, 0}};

// ---------- Parts (3 buzzers) ----------
static const song_part_t baby_shark_parts[] = {
    {baby_shark_melody, (uint16_t)(sizeof(baby_shark_melody) / sizeof(note_event_t) - 1), "Melody"},
    {baby_shark_ostinato, (uint16_t)(sizeof(baby_shark_ostinato) / sizeof(note_event_t) - 1), "Ostinato"},
    {baby_shark_bass, (uint16_t)(sizeof(baby_shark_bass) / sizeof(note_event_t) - 1), "Bass"}};

// =============================================================
// 🎵 All Songs Database
// =============================================================
static const orchestra_song_t all_songs[] = {
    {.song_name = "Twinkle Twinkle Little Star",
     .song_id = SONG_TWINKLE_STAR,
     .tempo_bpm = 120,
     .part_count = 4,
     .parts = twinkle_parts},
    {.song_name = "Happy Birthday",
     .song_id = SONG_HAPPY_BIRTHDAY,
     .tempo_bpm = 100,
     .part_count = 3,
     .parts = birthday_parts},
    {.song_name = "Mary Had a Little Lamb",
     .song_id = SONG_MARY_LAMB,
     .tempo_bpm = 140,
     .part_count = 2,
     .parts = mary_parts},
    {.song_name = "เต่า (Taotao)",
     .song_id = SONG_TAOTAO,
     .tempo_bpm = 100,
     .part_count = 2,
     .parts = taotao_parts},
    {
        .song_name = "Baby Shark",
        .song_id = SONG_BABY_SHARK,
        .tempo_bpm = 120,
        .part_count = 3,          // ✅ แก้ตรงนี้เป็น 3
        .parts = baby_shark_parts // ✅ ชี้ไปยังอาร์เรย์ใหม่ที่มี Melody, Ostinato, Bass
    }};

#define TOTAL_SONGS (sizeof(all_songs) / sizeof(orchestra_song_t))

// Helper function to get song by ID
static inline const orchestra_song_t *get_song_by_id(uint8_t song_id)
{
    for (int i = 0; i < (int)TOTAL_SONGS; i++)
    {
        if (all_songs[i].song_id == song_id)
        {
            return &all_songs[i];
        }
    }
    return NULL;
}

#endif // MIDI_SONGS_H
