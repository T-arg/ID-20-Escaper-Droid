#ifndef SONG_H
#define SONG_H

#include <ATMcmds.h>

#define Song const uint8_t PROGMEM



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

Song titleSong[] = {     // total song bytes = 546
  0x20,                       // Number of tracks
  0x00, 0x00,                 // Track 0  @    0  (silent)
  0x03, 0x00,                 // Track 1  @    3  (lead)
  0x18, 0x00,                 // Track 2  @   24  (bar1)
  0x25, 0x00,                 // Track 3  @   37  (bar2)
  0x32, 0x00,                 // Track 4  @   50  (bar3)
  0x3F, 0x00,                 // Track 5  @   63  (bar4)
  0x4C, 0x00,                 // Track 6  @   76  (bar5)
  0x5D, 0x00,                 // Track 7  @   93  (bar6)
  0x6E, 0x00,                 // Track 8  @  110  (bar7)
  0x7F, 0x00,                 // Track 9  @  127  (bar8)
  0x90, 0x00,                 // Track 10 @  144  (chords)
  0xAB, 0x00,                 // Track 11 @  171  (kick)
  0xB8, 0x00,                 // Track 12 @  184  (beat_D)
  0xC4, 0x00,                 // Track 13 @  196  (beat_G)
  0xD0, 0x00,                 // Track 14 @  208  (beat_A)
  0xDC, 0x00,                 // Track 15 @  220  (beat_Bm)
  0xE8, 0x00,                 // Track 16 @  232  (beat_D_last)
  0xF4, 0x00,                 // Track 17 @  244  (bass)
  0x17, 0x01,                 // Track 18 @  279  (bass_beat)
  0x23, 0x01,                 // Track 19 @  291  (bass_beat4)
  0x2F, 0x01,                 // Track 20 @  303  (bass_bar)
  0x35, 0x01,                 // Track 21 @  309  (bass_beat4_last)
  0x41, 0x01,                 // Track 22 @  321  (bass_bar_last)
  0x47, 0x01,                 // Track 23 @  327  (drums)
  0x59, 0x01,                 // Track 24 @  345  (drum_A)
  0x69, 0x01,                 // Track 25 @  361  (drum_B)
  0x74, 0x01,                 // Track 26 @  372  (drum_pair)
  0x79, 0x01,                 // Track 27 @  377  (drum_bar)
  0x7D, 0x01,                 // Track 28 @  381  (drum_fill)
  0xA6, 0x01,                 // Track 29 @  422  (drum_fill_last)
  0xCF, 0x01,                 // Track 30 @  463  (drum_bar_fill)
  0xD6, 0x01,                 // Track 31 @  470  (drum_bar_fill_last)

  0x01,                         // CH0 entry → track 1 (lead)
  0x0A,                         // CH1 entry → track 10 (chords)
  0x11,                         // CH2 entry → track 17 (bass)
  0x17,                         // CH3 entry → track 23 (drums)

  // Track  0: silent  [3b]  dummy track 0 (never called)
  ATM_VOL(0),
  ATM_STOP_CHAN,

  // Track  1: lead  [21b]  CH0 PULSE: vol + 8 bars
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-2),
  ATM_GOTO(2),
  ATM_GOTO(3),
  ATM_GOTO(4),
  ATM_GOTO(5),
  ATM_GOTO(6),
  ATM_GOTO(7),
  ATM_GOTO(8),
  ATM_GOTO(9),
  ATM_STOP_CHAN,

  // Track  2: bar1  [13b]  lead bar 1 (D)
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
  ATM_RETURN,

  // Track  3: bar2  [13b]  lead bar 2 (G)
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
  ATM_RETURN,

  // Track  4: bar3  [13b]  lead bar 3 (A)
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
  ATM_RETURN,

  // Track  5: bar4  [13b]  lead bar 4 (D)
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
  ATM_RETURN,

  // Track  6: bar5  [17b]  lead bar 5 (D)
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
  ATM_RETURN,

  // Track  7: bar6  [17b]  lead bar 6 (G)
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
  ATM_RETURN,

  // Track  8: bar7  [17b]  lead bar 7 (Bm)
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
  ATM_RETURN,

  // Track  9: bar8  [17b]  lead bar 8 (A, last – 63t loop comp)
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
  ATM_DELAY(7),
  ATM_RETURN,

  // Track 10: chords  [27b]  CH1 SQUARE: kick+stab, 8 bars
  ATM_REPEAT(3,12),
  ATM_REPEAT(3,13),
  ATM_REPEAT(3,14),
  ATM_REPEAT(3,12),
  ATM_REPEAT(3,12),
  ATM_REPEAT(3,15),
  ATM_REPEAT(3,14),
  ATM_REPEAT(2,12),
  ATM_GOTO(16),
  ATM_STOP_CHAN,

  // Track 11: kick  [13b]  cue + pitch-drop kick (4t) + silence (4t)
  ATM_CUE(2),                   // beat marker: fires once per beat (every 16 ticks) -> ATM.check() == 1
  ATM_ARP_OFF,
  ATM_SL_FRQ((uint8_t)-127),
  ATM_VOL(30),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_RETURN,

  // Track 12: beat_D  [12b]  beat: kick + D major stab (root D3)
  ATM_GOTO(11),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_ARP(0x47,0x20),
  ATM_NOTE_D3,
  ATM_DELAY(8),
  ATM_RETURN,

  // Track 13: beat_G  [12b]  beat: kick + G major stab (root G3)
  ATM_GOTO(11),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_ARP(0x47,0x20),
  ATM_NOTE_G3,
  ATM_DELAY(8),
  ATM_RETURN,

  // Track 14: beat_A  [12b]  beat: kick + A major stab (root A3)
  ATM_GOTO(11),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_ARP(0x47,0x20),
  ATM_NOTE_A3,
  ATM_DELAY(8),
  ATM_RETURN,

  // Track 15: beat_Bm  [12b]  beat: kick + Bm minor stab (root B3)
  ATM_GOTO(11),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_ARP(0x37,0x20),
  ATM_NOTE_B3,
  ATM_DELAY(8),
  ATM_RETURN,

  // Track 16: beat_D_last  [12b]  last beat: D stab 7t (loop comp)
  ATM_GOTO(11),
  ATM_SL_VOL((uint8_t)-3),
  ATM_VOL(24),
  ATM_ARP(0x47,0x20),
  ATM_NOTE_D3,
  ATM_DELAY(7),
  ATM_RETURN,

  // Track 17: bass  [35b]  CH2 SAW: transposed bass, 8 bars
  ATM_SL_VOL((uint8_t)-5),
  ATM_SET_TRA(0),
  ATM_GOTO(20),
  ATM_SET_TRA(5),
  ATM_GOTO(20),
  ATM_SET_TRA(7),
  ATM_GOTO(20),
  ATM_SET_TRA(0),
  ATM_GOTO(20),
  ATM_SET_TRA(0),
  ATM_GOTO(20),
  ATM_SET_TRA(9),
  ATM_GOTO(20),
  ATM_SET_TRA(7),
  ATM_GOTO(20),
  ATM_SET_TRA(0),
  ATM_GOTO(22),
  ATM_STOP_CHAN,

  // Track 18: bass_beat  [12b]  bass beat: silence-root-oct-root (16t)
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_VOL(63),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D4,
  ATM_DELAY(4),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_RETURN,

  // Track 19: bass_beat4  [12b]  bass beat 4: silence-root-root-oct (16t)
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_VOL(63),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D4,
  ATM_DELAY(4),
  ATM_RETURN,

  // Track 20: bass_bar  [6b]  bass bar (64t): 3× beat + beat4
  ATM_REPEAT(2,18),
  ATM_GOTO(19),
  ATM_RETURN,

  // Track 21: bass_beat4_last  [12b]  last beat4: final note 3t (loop comp)
  ATM_VOL(0),
  ATM_DELAY(4),
  ATM_VOL(63),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D3,
  ATM_DELAY(4),
  ATM_NOTE_D4,
  ATM_DELAY(3),
  ATM_RETURN,

  // Track 22: bass_bar_last  [6b]  last bass bar
  ATM_REPEAT(2,18),
  ATM_GOTO(21),
  ATM_RETURN,

  // Track 23: drums  [18b]  CH3 NOISE: tempo + 8 bars
  ATM_SET_TEMPO(36),
  ATM_GOTO_ADV(1,10,17,23),
  ATM_REPEAT(2,27),
  ATM_GOTO(30),
  ATM_REPEAT(2,27),
  ATM_GOTO(31),
  ATM_STOP_CHAN,

  // Track 24: drum_A  [16b]  beat 1/3: click, hat, open hat (16t)
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

  // Track 25: drum_B  [11b]  beat 2/4: clap, open hat (16t)
  ATM_VOL(40),
  ATM_SL_VOL((uint8_t)-5),
  ATM_DELAY(8),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_RETURN,

  // Track 26: drum_pair  [5b]  beats 1+2 (32t)
  ATM_GOTO(24),
  ATM_GOTO(25),
  ATM_RETURN,

  // Track 27: drum_bar  [4b]  one bar (64t)
  ATM_REPEAT(1,26),
  ATM_RETURN,

  // Track 28: drum_fill  [41b]  snare roll 16t
  ATM_VOL(22),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(30),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(34),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(42),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(46),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(50),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_RETURN,

  // Track 29: drum_fill_last  [41b]  snare roll 15t (loop comp)
  ATM_VOL(22),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(30),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(34),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(42),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(46),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(50),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(1),
  ATM_RETURN,

  // Track 30: drum_bar_fill  [7b]  bar 4: pair + drum_A + fill
  ATM_GOTO(26),
  ATM_GOTO(24),
  ATM_GOTO(28),
  ATM_RETURN,

  // Track 31: drum_bar_fill_last  [7b]  bar 8: pair + drum_A + fill_last
  ATM_GOTO(26),
  ATM_GOTO(24),
  ATM_GOTO(29),
  ATM_RETURN,

};

Song gameSong[] = {     // total song bytes = 245
  0x0D,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   drums
  0x0C, 0x00,                 // Address of track 1     12   drum_core
  0x25, 0x00,                 // Address of track 2     37   drum_half
  0x29, 0x00,                 // Address of track 3     41   lead
  0x40, 0x00,                 // Address of track 4     64   lead_riff
  0x5E, 0x00,                 // Address of track 5     94   lead_cycle
  0x6C, 0x00,                 // Address of track 6    108   chords
  0x94, 0x00,                 // Address of track 7    148   bass
  0xAC, 0x00,                 // Address of track 8    172   bass_cycle
  0xBA, 0x00,                 // Address of track 9    186   bass_bar
  0xC0, 0x00,                 // Address of track 10   192   bass_bar_last
  0xCA, 0x00,                 // Address of track 11   202   bass_beat
  0xCF, 0x00,                 // Address of track 12   207   bass_beat4

  0x03,                         // CH0 entry -> track 3 (lead)
  0x06,                         // CH1 entry -> track 6 (chords)
  0x07,                         // CH2 entry -> track 7 (bass)
  0x00,                         // CH3 entry -> track 0 (drums)

  //"Track 0" drums  [12b]
  ATM_GOTO_ADV(3, 6, 7, 0),   // loop point per channel
  ATM_REPEAT(30, 2),   // 31x drum_half
  ATM_GOTO(1),   // -> drum_core
  ATM_DELAY(7),
  ATM_STOP_CHAN,

  //"Track 1" drum_core  [25b]
  ATM_VOL(48),
  ATM_SL_VOL((uint8_t)-12),
  ATM_DELAY(4),
  ATM_VOL(14),
  ATM_SL_VOL((uint8_t)-7),
  ATM_DELAY(4),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_VOL(44),
  ATM_SL_VOL((uint8_t)-5),
  ATM_DELAY(8),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_RETURN,

  //"Track 2" drum_half  [4b]
  ATM_GOTO(1),   // -> drum_core
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 3" lead  [23b]
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-2),
  ATM_SET_TRA(0),
  ATM_GOTO(5),   // -> lead_cycle
  ATM_ADD_TRA(7),
  ATM_GOTO(4),   // -> lead_riff
  ATM_DELAY(16),
  ATM_SET_TRA(2),
  ATM_GOTO(5),   // -> lead_cycle
  ATM_ADD_TRA(5),
  ATM_GOTO(4),   // -> lead_riff
  ATM_DELAY(15),
  ATM_STOP_CHAN,

  //"Track 4" lead_riff  [30b]
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
  ATM_RETURN,

  //"Track 5" lead_cycle  [14b]
  ATM_GOTO(4),   // -> lead_riff
  ATM_DELAY(16),
  ATM_ADD_TRA(5),
  ATM_GOTO(4),   // -> lead_riff
  ATM_DELAY(16),
  ATM_ADD_TRA((uint8_t)-5),
  ATM_GOTO(4),   // -> lead_riff
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 6" chords  [40b]
  ATM_VOL(30),
  ATM_SL_VOL((uint8_t)-1),
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
  ATM_DELAY(63),
  ATM_STOP_CHAN,

  //"Track 7" bass  [24b]
  ATM_VOL(63),
  ATM_SL_VOL((uint8_t)-5),
  ATM_SET_TRA(0),
  ATM_GOTO(8),   // -> bass_cycle
  ATM_ADD_TRA(7),
  ATM_REPEAT(1, 9),   // 2x bass_bar
  ATM_SET_TRA(2),
  ATM_GOTO(8),   // -> bass_cycle
  ATM_SET_TRA(7),
  ATM_GOTO(9),   // -> bass_bar
  ATM_GOTO(10),   // -> bass_bar_last
  ATM_STOP_CHAN,

  //"Track 8" bass_cycle  [14b]
  ATM_REPEAT(1, 9),   // 2x bass_bar
  ATM_ADD_TRA(5),
  ATM_REPEAT(1, 9),   // 2x bass_bar
  ATM_ADD_TRA((uint8_t)-5),
  ATM_REPEAT(1, 9),   // 2x bass_bar
  ATM_RETURN,

  //"Track 9" bass_bar  [6b]
  ATM_REPEAT(2, 11),   // 3x bass_beat
  ATM_GOTO(12),   // -> bass_beat4
  ATM_RETURN,

  //"Track 10" bass_bar_last  [10b]
  ATM_REPEAT(2, 11),   // 3x bass_beat
  ATM_NOTE_A2,
  ATM_DELAY(8),
  ATM_NOTE_A2,
  ATM_DELAY(4),
  ATM_NOTE_A3,
  ATM_DELAY(3),
  ATM_RETURN,

  //"Track 11" bass_beat  [5b]
  ATM_NOTE_A2,
  ATM_DELAY(8),
  ATM_NOTE_A3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 12" bass_beat4  [7b]
  ATM_NOTE_A2,
  ATM_DELAY(8),
  ATM_NOTE_A2,
  ATM_DELAY(4),
  ATM_NOTE_A3,
  ATM_DELAY(4),
  ATM_RETURN,

};

#endif
