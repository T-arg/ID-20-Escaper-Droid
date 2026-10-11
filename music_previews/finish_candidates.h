// Hop Hop Hooray - finishing tune, 512 ticks/loop, tempo 36
Song finishHop[] = {     // total song bytes = 103
  0x05,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x09, 0x00,                 // Address of track 1      9   harm
  0x12, 0x00,                 // Address of track 2     18   bass
  0x1B, 0x00,                 // Address of track 3     27   drum
  0x27, 0x00,                 // Address of track 4     39   lcyc

  0x00,                         // CH0 entry -> track 0 (lead)
  0x01,                         // CH1 entry -> track 1 (harm)
  0x02,                         // CH2 entry -> track 2 (bass)
  0x03,                         // CH3 entry -> track 3 (drum)

  //"Track 0" lead  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(63)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(0),   // -> lead

  //"Track 1" harm  [9b]
  ATM_SET_TRA((uint8_t)-12),
  ATM_VOL(MV(30)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(1),   // -> harm

  //"Track 2" bass  [9b]
  ATM_SET_TRA((uint8_t)-24),
  ATM_VOL(MV(45)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(2),   // -> bass

  //"Track 3" drum  [12b]
  ATM_VOL(MV(48)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(8),
  ATM_VOL(MV(14)),
  ATM_SL_VOL(MS(7)),
  ATM_DELAY(8),
  ATM_GOTO(3),   // -> drum

  //"Track 4" lcyc  [49b]
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(16),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_F5,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(32),
  ATM_ADD_TRA(7),
  ATM_RETURN,

};

// Marching Home - finishing tune, 512 ticks/loop, tempo 32
Song finishMarch[] = {     // total song bytes = 143
  0x07,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x09, 0x00,                 // Address of track 1      9   harm
  0x12, 0x00,                 // Address of track 2     18   bass
  0x1B, 0x00,                 // Address of track 3     27   drum
  0x27, 0x00,                 // Address of track 4     39   lcyc
  0x62, 0x00,                 // Address of track 5     98   bcyc
  0x77, 0x00,                 // Address of track 6    119   pair

  0x00,                         // CH0 entry -> track 0 (lead)
  0x01,                         // CH1 entry -> track 1 (harm)
  0x02,                         // CH2 entry -> track 2 (bass)
  0x03,                         // CH3 entry -> track 3 (drum)

  //"Track 0" lead  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(63)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(0),   // -> lead

  //"Track 1" harm  [9b]
  ATM_SET_TRA((uint8_t)-12),
  ATM_VOL(MV(30)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(1),   // -> harm

  //"Track 2" bass  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(45)),
  ATM_REPEAT(1, 5),   // 2x bcyc
  ATM_GOTO(2),   // -> bass

  //"Track 3" drum  [12b]
  ATM_VOL(MV(48)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(16),
  ATM_VOL(MV(30)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(16),
  ATM_GOTO(3),   // -> drum

  //"Track 4" lcyc  [59b]
  ATM_NOTE_G4,
  ATM_DELAY(12),
  ATM_NOTE_A4,
  ATM_DELAY(4),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_F5_,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(12),
  ATM_NOTE_F5_,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(16),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_A4,
  ATM_DELAY(8),
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 5" bcyc  [21b]
  ATM_REPEAT(1, 6),   // 2x pair
  ATM_ADD_TRA(5),
  ATM_REPEAT(1, 6),   // 2x pair
  ATM_ADD_TRA(2),
  ATM_REPEAT(1, 6),   // 2x pair
  ATM_ADD_TRA((uint8_t)-7),
  ATM_REPEAT(1, 6),   // 2x pair
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 6" pair  [5b]
  ATM_NOTE_G2,
  ATM_DELAY(16),
  ATM_NOTE_D3,
  ATM_DELAY(16),
  ATM_RETURN,

};

// Skipping Waltz - finishing tune, 288 ticks/loop, tempo 28
Song finishWaltz[] = {     // total song bytes = 129
  0x08,                       // Number of tracks
  0x00, 0x00,                 // Address of track 0      0   lead
  0x09, 0x00,                 // Address of track 1      9   harm
  0x12, 0x00,                 // Address of track 2     18   bass
  0x1B, 0x00,                 // Address of track 3     27   drum
  0x25, 0x00,                 // Address of track 4     37   lcyc
  0x4C, 0x00,                 // Address of track 5     76   bcyc
  0x61, 0x00,                 // Address of track 6     97   wbar
  0x66, 0x00,                 // Address of track 7    102   tick

  0x00,                         // CH0 entry -> track 0 (lead)
  0x01,                         // CH1 entry -> track 1 (harm)
  0x02,                         // CH2 entry -> track 2 (bass)
  0x03,                         // CH3 entry -> track 3 (drum)

  //"Track 0" lead  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(63)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(0),   // -> lead

  //"Track 1" harm  [9b]
  ATM_SET_TRA((uint8_t)-12),
  ATM_VOL(MV(30)),
  ATM_REPEAT(1, 4),   // 2x lcyc
  ATM_GOTO(1),   // -> harm

  //"Track 2" bass  [9b]
  ATM_SET_TRA(0),
  ATM_VOL(MV(45)),
  ATM_REPEAT(1, 5),   // 2x bcyc
  ATM_GOTO(2),   // -> bass

  //"Track 3" drum  [10b]
  ATM_VOL(MV(48)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(12),
  ATM_REPEAT(1, 7),   // 2x tick
  ATM_GOTO(3),   // -> drum

  //"Track 4" lcyc  [39b]
  ATM_NOTE_F4,
  ATM_DELAY(6),
  ATM_NOTE_A4,
  ATM_DELAY(6),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_A4,
  ATM_DELAY(6),
  ATM_NOTE_C5,
  ATM_DELAY(6),
  ATM_NOTE_D5,
  ATM_DELAY(6),
  ATM_NOTE_F5,
  ATM_DELAY(6),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_F5,
  ATM_DELAY(6),
  ATM_NOTE_D5,
  ATM_DELAY(6),
  ATM_NOTE_C5,
  ATM_DELAY(6),
  ATM_NOTE_E5,
  ATM_DELAY(6),
  ATM_NOTE_G5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(6),
  ATM_NOTE_C5,
  ATM_DELAY(6),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_A4,
  ATM_DELAY(12),
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 5" bcyc  [21b]
  ATM_REPEAT(0, 6),   // 1x wbar
  ATM_ADD_TRA((uint8_t)-3),
  ATM_REPEAT(0, 6),   // 1x wbar
  ATM_ADD_TRA((uint8_t)-2),
  ATM_REPEAT(0, 6),   // 1x wbar
  ATM_ADD_TRA(5),
  ATM_REPEAT(0, 6),   // 1x wbar
  ATM_ADD_TRA(7),
  ATM_RETURN,

  //"Track 6" wbar  [5b]
  ATM_NOTE_F2,
  ATM_DELAY(12),
  ATM_NOTE_C3,
  ATM_DELAY(24),
  ATM_RETURN,

  //"Track 7" tick  [6b]
  ATM_VOL(MV(14)),
  ATM_SL_VOL(MS(7)),
  ATM_DELAY(12),
  ATM_RETURN,

};
