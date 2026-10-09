#ifndef SONG_H
#define SONG_H

// ---------------------------------------------------------------------------
//  Game songs, size-optimised (same notes, volumes, slides, tempo and cues as before)
//
//    gameOver   106 B  unchanged (nothing left to save: every track is used, the pieces that repeat are
//                      already shared; moving the toll slide into the drum track saves 0 bytes)
//    titleSong  546 B -> 351 B   (Escaper Droid, loops, ATM_CUE(2) once per beat, tempo 36 set in the song)
//    gameSong   245 B -> 212 B   (Quest Theme, loops, no tempo in the song: the sketch sets it)
//
//  The two loops are now hop-free self-loops: every channel's entry track ends with ATM_GOTO(itself)
//  and sums to exactly the loop length (titleSong 512 ticks, gameSong 1024 ticks), so there is no
//  ATM_STOP_CHAN / ATM_GOTO_ADV any more and no silent tick at the seam.
//  Checked tick by tick against the old data: identical note and cue events and identical volume /
//  frequency of all four channels, and every loop pass is identical.
// ---------------------------------------------------------------------------

#include <ATMcmds.h>

#define Song const uint8_t PROGMEM

// in-game music plays at 60 % of the title music volume (ATMlib README: "Keep the music quieter than the effects")
// only gameSong uses MV() / MS(); titleSong and gameOver stay at 100 %. Scaled at compile time, no extra bytes.
#define MUSIC_VOL_PCT 60                       // 100 = original
#define MV(v) ((v) * MUSIC_VOL_PCT / 100)
// the fade step, scaled the same way and never below 1 (a 0 would stop the fade)
#define MS(n) ((uint8_t)-((((n) * MUSIC_VOL_PCT + 50) / 100) < 1 ? 1 : (((n) * MUSIC_VOL_PCT + 50) / 100)))


Song gameOver[] = {     // total song bytes = 106
  0x06,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   drums
  0x06, 0x00,                 // Address of track 1      6   toll
  0x0C, 0x00,                 // Address of track 2     12   lead
  0x23, 0x00,                 // Address of track 3     35   lead_phrase
  0x2A, 0x00,                 // Address of track 4     42   chords
  0x42, 0x00,                 // Address of track 5     66   bass

  0x02,                         // CH0 entry -> track 2 (lead)
  0x04,                         // CH1 entry -> track 4 (chords)
  0x05,                         // CH2 entry -> track 5 (bass)
  0x00,                         // CH3 entry -> track 0 (drums)

  //"Track 0" drums  [6b]
  ATM_SET_TEMPO(20),
  ATM_REPEAT(4, 1),   // 5x toll
  ATM_STOP_CHAN,

  //"Track 1" toll  [6b]
  ATM_VOL(46),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(64),
  ATM_RETURN,

  //"Track 2" lead  [23b]
  ATM_VOL(40),
  ATM_SL_VOL((uint8_t)-1),
  ATM_GOTO(3),   // -> lead_phrase
  ATM_ADD_TRA((uint8_t)-2),
  ATM_GOTO(3),   // -> lead_phrase
  ATM_ADD_TRA((uint8_t)-2),
  ATM_GOTO(3),   // -> lead_phrase
  ATM_ADD_TRA((uint8_t)-1),
  ATM_GOTO(3),   // -> lead_phrase
  ATM_SET_TRA(0),
  ATM_NOTE_A4,
  ATM_DELAY(64),
  ATM_STOP_CHAN,

  //"Track 3" lead_phrase  [7b]
  ATM_NOTE_A5,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_A4,
  ATM_DELAY(32),
  ATM_RETURN,

  //"Track 4" chords  [24b]
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-1),
  ATM_ARP(0x34, 0x20),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_ARP(0x43, 0x20),
  ATM_NOTE_G3,
  ATM_DELAY(64),
  ATM_NOTE_F3,
  ATM_DELAY(64),
  ATM_NOTE_E3,
  ATM_DELAY(64),
  ATM_ARP(0x34, 0x20),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_STOP_CHAN,

  //"Track 5" bass  [23b]
  ATM_VOL(48),
  ATM_SL_VOL((uint8_t)-1),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_ADD_TRA((uint8_t)-2),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_ADD_TRA((uint8_t)-2),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_ADD_TRA((uint8_t)-1),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_SET_TRA(0),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_STOP_CHAN,

};

Song titleSong[] = {     // total song bytes = 351
  0x0F,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   drums
  0x07, 0x00,                 // Address of track 1      7   drum_half
  0x27, 0x00,                 // Address of track 2     39   drum_A
  0x37, 0x00,                 // Address of track 3     55   drum_pair
  0x44, 0x00,                 // Address of track 4     68   lead
  0xBA, 0x00,                 // Address of track 5    186   chords
  0xD1, 0x00,                 // Address of track 6    209   kick
  0xE2, 0x00,                 // Address of track 7    226   beat_D
  0xEA, 0x00,                 // Address of track 8    234   beat_G
  0xF2, 0x00,                 // Address of track 9    242   beat_A
  0xFA, 0x00,                 // Address of track 10   250   beat_Bm
  0x02, 0x01,                 // Address of track 11   258   bass
  0x23, 0x01,                 // Address of track 12   291   bass_head
  0x2B, 0x01,                 // Address of track 13   299   bass_beat
  0x32, 0x01,                 // Address of track 14   306   bass_bar

  0x04,                         // CH0 entry -> track 4 (lead)
  0x05,                         // CH1 entry -> track 5 (chords)
  0x0B,                         // CH2 entry -> track 11 (bass)
  0x00,                         // CH3 entry -> track 0 (drums)

  //"Track 0" drums  [7b]
  ATM_SET_TEMPO(36),
  ATM_REPEAT(1, 1),   // 2x drum_half
  ATM_GOTO(0),   // -> drums  (loop: this very track)

  //"Track 1" drum_half  [32b]
  ATM_REPEAT(6, 3),   // 7x drum_pair
  ATM_GOTO(2),   // -> drum_A
  ATM_VOL(22),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(26),
  ATM_DELAY(2),
  ATM_VOL(30),
  ATM_DELAY(2),
  ATM_VOL(34),
  ATM_DELAY(2),
  ATM_VOL(38),
  ATM_DELAY(2),
  ATM_VOL(42),
  ATM_DELAY(2),
  ATM_VOL(46),
  ATM_DELAY(2),
  ATM_VOL(50),
  ATM_DELAY(2),
  ATM_RETURN,

  //"Track 2" drum_A  [16b]
  ATM_VOL(28),
  ATM_SL_VOL((uint8_t)-14),
  ATM_DELAY(4),
  ATM_VOL(12),
  ATM_SL_VOL((uint8_t)-6),
  ATM_DELAY(4),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 3" drum_pair  [13b]
  ATM_GOTO(2),   // -> drum_A
  ATM_VOL(40),
  ATM_SL_VOL((uint8_t)-5),
  ATM_DELAY(8),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 4" lead  [118b]
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-2),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_F5_,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_F5_,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(12),
  ATM_NOTE_B5,
  ATM_DELAY(12),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_B5,
  ATM_DELAY(12),
  ATM_NOTE_D6,
  ATM_DELAY(12),
  ATM_NOTE_B5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_C6_,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_C6_,
  ATM_DELAY(8),
  ATM_NOTE_F5_,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_B4,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_G4,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_B5,
  ATM_DELAY(16),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(4),
  ATM_NOTE_C5_,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_C5_,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_GOTO(4),   // -> lead  (loop: this very track)

  //"Track 5" chords  [23b]
  ATM_REPEAT(3, 7),   // 4x beat_D
  ATM_REPEAT(3, 8),   // 4x beat_G
  ATM_REPEAT(3, 9),   // 4x beat_A
  ATM_REPEAT(7, 7),   // 8x beat_D
  ATM_REPEAT(3, 10),   // 4x beat_Bm
  ATM_REPEAT(3, 9),   // 4x beat_A
  ATM_REPEAT(3, 7),   // 4x beat_D
  ATM_GOTO(5),   // -> chords  (loop: this very track)

  //"Track 6" kick  [17b]
  ATM_CUE(2),                   // beat marker: fires once per beat (every 16 ticks)
  ATM_ARP_OFF,
  ATM_SL_FRQ((uint8_t)-127),
  ATM_VOL(30),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_RETURN,

  //"Track 7" beat_D  [8b]
  ATM_GOTO(6),   // -> kick
  ATM_ARP(0x47, 0x20),
  ATM_NOTE_D3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 8" beat_G  [8b]
  ATM_GOTO(6),   // -> kick
  ATM_ARP(0x47, 0x20),
  ATM_NOTE_G3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 9" beat_A  [8b]
  ATM_GOTO(6),   // -> kick
  ATM_ARP(0x47, 0x20),
  ATM_NOTE_A3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 10" beat_Bm  [8b]
  ATM_GOTO(6),   // -> kick
  ATM_ARP(0x37, 0x20),
  ATM_NOTE_B3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 11" bass  [33b]
  ATM_SL_VOL((uint8_t)-5),
  ATM_SET_TRA(0),
  ATM_GOTO(14),   // -> bass_bar
  ATM_SET_TRA(5),
  ATM_GOTO(14),   // -> bass_bar
  ATM_SET_TRA(7),
  ATM_GOTO(14),   // -> bass_bar
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 14),   // 2x bass_bar
  ATM_SET_TRA(9),
  ATM_GOTO(14),   // -> bass_bar
  ATM_SET_TRA(7),
  ATM_GOTO(14),   // -> bass_bar
  ATM_SET_TRA(0),
  ATM_GOTO(14),   // -> bass_bar
  ATM_GOTO(11),   // -> bass  (loop: this very track)

  //"Track 12" bass_head  [8b]
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_VOL(63),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 13" bass_beat  [7b]
  ATM_GOTO(12),   // -> bass_head
  ATM_NOTE_D4,
  ATM_DELAY(4),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 14" bass_bar  [10b]
  ATM_REPEAT(2, 13),   // 3x bass_beat
  ATM_GOTO(12),   // -> bass_head
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D4,
  ATM_DELAY(4),
  ATM_RETURN,

};

Song gameSong[] = {     // total song bytes = 212
  0x0B,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   drums
  0x05, 0x00,                 // Address of track 1      5   drum
  0x1F, 0x00,                 // Address of track 2     31   lead
  0x34, 0x00,                 // Address of track 3     52   lead_riff
  0x53, 0x00,                 // Address of track 4     83   lead_w
  0x5C, 0x00,                 // Address of track 5     92   chords
  0x85, 0x00,                 // Address of track 6    133   bass
  0x9C, 0x00,                 // Address of track 7    156   bass_w
  0xA7, 0x00,                 // Address of track 8    167   bass_bar
  0xAD, 0x00,                 // Address of track 9    173   bass_beat
  0xB2, 0x00,                 // Address of track 10   178   bass_beat4

  0x02,                         // CH0 entry -> track 2 (lead)
  0x05,                         // CH1 entry -> track 5 (chords)
  0x06,                         // CH2 entry -> track 6 (bass)
  0x00,                         // CH3 entry -> track 0 (drums)

  //"Track 0" drums  [5b]
  ATM_REPEAT(31, 1),   // 32x drum
  ATM_GOTO(0),   // -> drums  (loop: this very track)

  //"Track 1" drum  [26b]
  ATM_VOL(MV(48)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(4),
  ATM_VOL(MV(14)),
  ATM_SL_VOL(MS(7)),
  ATM_DELAY(4),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_VOL(MV(44)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 2" lead  [21b]
  ATM_VOL(MV(38)),
  ATM_SL_VOL(MS(2)),
  ATM_SET_TRA(0),
  ATM_GOTO(4),   // -> lead_w
  ATM_GOTO(3),   // -> lead_riff
  ATM_ADD_TRA(7),
  ATM_GOTO(3),   // -> lead_riff
  ATM_SET_TRA(2),
  ATM_REPEAT(1, 4),   // 2x lead_w
  ATM_GOTO(2),   // -> lead  (loop: this very track)

  //"Track 3" lead_riff  [31b]
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(4),
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_G4,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 4" lead_w  [9b]
  ATM_GOTO(3),   // -> lead_riff
  ATM_ADD_TRA(5),
  ATM_GOTO(3),   // -> lead_riff
  ATM_ADD_TRA((uint8_t)-5),
  ATM_RETURN,

  //"Track 5" chords  [41b]
  ATM_VOL(MV(30)),
  ATM_SL_VOL(MS(1)),
  ATM_ARP(0x34, 0x20),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_NOTE_D4,
  ATM_DELAY(64),
  ATM_NOTE_D4,
  ATM_DELAY(64),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_GOTO(5),   // -> chords  (loop: this very track)

  //"Track 6" bass  [23b]
  ATM_VOL(MV(63)),
  ATM_SL_VOL(MS(5)),
  ATM_SET_TRA(0),
  ATM_GOTO(7),   // -> bass_w
  ATM_REPEAT(1, 8),   // 2x bass_bar
  ATM_ADD_TRA(7),
  ATM_REPEAT(1, 8),   // 2x bass_bar
  ATM_SET_TRA(2),
  ATM_REPEAT(1, 7),   // 2x bass_w
  ATM_GOTO(6),   // -> bass  (loop: this very track)

  //"Track 7" bass_w  [11b]
  ATM_REPEAT(1, 8),   // 2x bass_bar
  ATM_ADD_TRA(5),
  ATM_REPEAT(1, 8),   // 2x bass_bar
  ATM_ADD_TRA((uint8_t)-5),
  ATM_RETURN,

  //"Track 8" bass_bar  [6b]
  ATM_REPEAT(2, 9),   // 3x bass_beat
  ATM_GOTO(10),   // -> bass_beat4
  ATM_RETURN,

  //"Track 9" bass_beat  [5b]
  ATM_NOTE_A2,
  ATM_DELAY(8),
  ATM_NOTE_A3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 10" bass_beat4  [7b]
  ATM_NOTE_A2,
  ATM_DELAY(8),
  ATM_NOTE_A2,
  ATM_DELAY(4),
  ATM_NOTE_A3,
  ATM_DELAY(4),
  ATM_RETURN,

};

#endif
