// Happy Disco - finishing tune, 512 ticks/loop, tempo 34
Song finishDisco[] = {     // total song bytes = 144
  0x08,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x0B, 0x00,                 // Address of track 1     11   riff
  0x1A, 0x00,                 // Address of track 2     26   cycL
  0x2B, 0x00,                 // Address of track 3     43   harm
  0x36, 0x00,                 // Address of track 4     54   bass
  0x3F, 0x00,                 // Address of track 5     63   beat
  0x4B, 0x00,                 // Address of track 6     75   cycB
  0x60, 0x00,                 // Address of track 7     96   drum

  0x00,                         // CH0 entry -> track 0 (lead)
  0x03,                         // CH1 entry -> track 3 (harm)
  0x04,                         // CH2 entry -> track 4 (bass)
  0x07,                         // CH3 entry -> track 7 (drum)

  //"Track 0" lead  [11b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(38)),
  ATM_SL_VOL(MS(2)),
  ATM_REPEAT(1, 2),   // 2x cycL
  ATM_GOTO(0),   // -> lead

  //"Track 1" riff  [15b]
  ATM_NOTE_G4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 2" cycL  [17b]
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(5),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(2),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA((uint8_t)-7),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 3" harm  [11b]
  ATM_SET_TRA((uint8_t)-12),
  ATM_VOL(MV(20)),
  ATM_SL_VOL(MS(1)),
  ATM_REPEAT(1, 2),   // 2x cycL
  ATM_GOTO(3),   // -> harm

  //"Track 4" bass  [9b]
  ATM_SL_VOL(MS(5)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 6),   // 2x cycB
  ATM_GOTO(4),   // -> bass

  //"Track 5" beat  [12b]
  ATM_VOL(MV(0)),
  ATM_DELAY(4),
  ATM_VOL(MV(63)),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_NOTE_C4,
  ATM_DELAY(4),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 6" cycB  [21b]
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA(5),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA(2),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA((uint8_t)-7),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 7" drum  [27b]
  ATM_VOL(MV(28)),
  ATM_SL_VOL(MS(14)),
  ATM_DELAY(4),
  ATM_VOL(MV(12)),
  ATM_SL_VOL(MS(6)),
  ATM_DELAY(4),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_GOTO(7),   // -> drum

};

// Victory Night - finishing tune, 512 ticks/loop, tempo 36
Song finishNeon[] = {     // total song bytes = 176
  0x0A,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x0B, 0x00,                 // Address of track 1     11   riff
  0x1A, 0x00,                 // Address of track 2     26   cycL
  0x2B, 0x00,                 // Address of track 3     43   arp
  0x34, 0x00,                 // Address of track 4     52   abeat
  0x3D, 0x00,                 // Address of track 5     61   cycA
  0x52, 0x00,                 // Address of track 6     82   bass
  0x5B, 0x00,                 // Address of track 7     91   beat
  0x67, 0x00,                 // Address of track 8    103   cycB
  0x7C, 0x00,                 // Address of track 9    124   drum

  0x00,                         // CH0 entry -> track 0 (lead)
  0x03,                         // CH1 entry -> track 3 (arp)
  0x06,                         // CH2 entry -> track 6 (bass)
  0x09,                         // CH3 entry -> track 9 (drum)

  //"Track 0" lead  [11b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(38)),
  ATM_SL_VOL(MS(2)),
  ATM_REPEAT(1, 2),   // 2x cycL
  ATM_GOTO(0),   // -> lead

  //"Track 1" riff  [15b]
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 2" cycL  [17b]
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA((uint8_t)-5),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA((uint8_t)-2),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(2),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(10),
  ATM_RETURN,

  //"Track 3" arp  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(22)),
  ATM_REPEAT(1, 5),   // 2x cycA
  ATM_GOTO(3),   // -> arp

  //"Track 4" abeat  [9b]
  ATM_NOTE_C4,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_C5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 5" cycA  [21b]
  ATM_REPEAT(3, 4),   // 4x abeat
  ATM_ADD_TRA((uint8_t)-5),
  ATM_REPEAT(3, 4),   // 4x abeat
  ATM_ADD_TRA((uint8_t)-2),
  ATM_REPEAT(3, 4),   // 4x abeat
  ATM_ADD_TRA(2),
  ATM_REPEAT(3, 4),   // 4x abeat
  ATM_ADD_TRA(10),
  ATM_RETURN,

  //"Track 6" bass  [9b]
  ATM_SL_VOL(MS(5)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 8),   // 2x cycB
  ATM_GOTO(6),   // -> bass

  //"Track 7" beat  [12b]
  ATM_VOL(MV(0)),
  ATM_DELAY(4),
  ATM_VOL(MV(63)),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_NOTE_C4,
  ATM_DELAY(4),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 8" cycB  [21b]
  ATM_REPEAT(3, 7),   // 4x beat
  ATM_ADD_TRA((uint8_t)-5),
  ATM_REPEAT(3, 7),   // 4x beat
  ATM_ADD_TRA((uint8_t)-2),
  ATM_REPEAT(3, 7),   // 4x beat
  ATM_ADD_TRA(2),
  ATM_REPEAT(3, 7),   // 4x beat
  ATM_ADD_TRA(10),
  ATM_RETURN,

  //"Track 9" drum  [27b]
  ATM_VOL(MV(28)),
  ATM_SL_VOL(MS(14)),
  ATM_DELAY(4),
  ATM_VOL(MV(12)),
  ATM_SL_VOL(MS(6)),
  ATM_DELAY(4),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_GOTO(9),   // -> drum

};

// Glitter Finale - finishing tune, 512 ticks/loop, tempo 35
Song finishGlitter[] = {     // total song bytes = 174
  0x0A,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x0B, 0x00,                 // Address of track 1     11   riff
  0x26, 0x00,                 // Address of track 2     38   cycL
  0x37, 0x00,                 // Address of track 3     55   harm
  0x42, 0x00,                 // Address of track 4     66   bass
  0x4B, 0x00,                 // Address of track 5     75   beat
  0x57, 0x00,                 // Address of track 6     87   cycB
  0x6C, 0x00,                 // Address of track 7    108   drum
  0x78, 0x00,                 // Address of track 8    120   dA
  0x88, 0x00,                 // Address of track 9    136   pair

  0x00,                         // CH0 entry -> track 0 (lead)
  0x03,                         // CH1 entry -> track 3 (harm)
  0x04,                         // CH2 entry -> track 4 (bass)
  0x07,                         // CH3 entry -> track 7 (drum)

  //"Track 0" lead  [11b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(38)),
  ATM_SL_VOL(MS(2)),
  ATM_REPEAT(1, 2),   // 2x cycL
  ATM_GOTO(0),   // -> lead

  //"Track 1" riff  [27b]
  ATM_NOTE_C5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_G4,
  ATM_DELAY(4),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 2" cycL  [17b]
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(5),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA(2),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA((uint8_t)-2),
  ATM_GOTO(1),   // -> riff
  ATM_ADD_TRA((uint8_t)-3),
  ATM_RETURN,

  //"Track 3" harm  [11b]
  ATM_SET_TRA((uint8_t)-12),
  ATM_VOL(MV(20)),
  ATM_SL_VOL(MS(1)),
  ATM_REPEAT(1, 2),   // 2x cycL
  ATM_GOTO(3),   // -> harm

  //"Track 4" bass  [9b]
  ATM_SL_VOL(MS(5)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 6),   // 2x cycB
  ATM_GOTO(4),   // -> bass

  //"Track 5" beat  [12b]
  ATM_VOL(MV(0)),
  ATM_DELAY(4),
  ATM_VOL(MV(63)),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_NOTE_C4,
  ATM_DELAY(4),
  ATM_NOTE_C3,
  ATM_DELAY(4),
  ATM_RETURN,

  //"Track 6" cycB  [21b]
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA(5),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA(2),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA((uint8_t)-2),
  ATM_REPEAT(3, 5),   // 4x beat
  ATM_ADD_TRA((uint8_t)-3),
  ATM_RETURN,

  //"Track 7" drum  [12b]
  ATM_REPEAT(14, 9),   // 15x pair
  ATM_GOTO(8),   // -> dA
  ATM_VOL(MV(10)),
  ATM_SL_VOL(3),
  ATM_DELAY(16),
  ATM_GOTO(7),   // -> drum

  //"Track 8" dA  [16b]
  ATM_VOL(MV(28)),
  ATM_SL_VOL(MS(14)),
  ATM_DELAY(4),
  ATM_VOL(MV(12)),
  ATM_SL_VOL(MS(6)),
  ATM_DELAY(4),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 9" pair  [13b]
  ATM_GOTO(8),   // -> dA
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(3)),
  ATM_DELAY(8),
  ATM_RETURN,

};
