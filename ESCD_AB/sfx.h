#ifndef SFX_H
#define SFX_H

// 0: music + SFX   1: music only   2: SFX only   3: mute
byte soundMode = 0;

#define SFX_DOOR    0
#define SFX_PICKUP  1

const uint8_t sfxDoorClosed[] PROGMEM = {
  ATM_VOL(63),
  //ATM_SL_VOL(-8),
  ATM_NOTE_C2,
  ATM_DELAY(16),
  ATM_STOP_CHAN,
};

const uint8_t pickUp[] PROGMEM = {
  ATM_VOL(63),
  ATM_SL_VOL(-8),
  ATM_NOTE_F6,
  ATM_DELAY(5),
  ATM_NOTE_G6,
  ATM_DELAY(11),
  ATM_STOP_CHAN,
};

const unsigned char * const PROGMEM soundFX[] =
{
  sfxDoorClosed, pickUp,
};

#endif
