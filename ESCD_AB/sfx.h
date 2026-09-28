#ifndef SFX_H
#define SFX_H

// 0: music + SFX   1: music only   2: SFX only   3: mute
byte soundMode = 0;

#define SFX_DOOR              0
#define SFX_PICKUP            1
#define SFX_MENU              2
#define SFX_SHOOT             3
#define SFX_SPEEDUP           4
#define SFX_SPEEDNORMAL       5

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

const uint8_t menuClick[] PROGMEM = {
  ATM_VOL(63),
  ATM_SL_VOL(-8),
  ATM_NOTE_G3,
  ATM_DELAY(7),
  ATM_STOP_CHAN,
};

const uint8_t shootBullet[] PROGMEM = {
  ATM_VOL(63),
  ATM_SL_VOL(-8),
  ATM_GLIS(1),
  ATM_CUT(0),
  ATM_NOTE_C3,
  ATM_DELAY(8),
  ATM_STOP_CHAN,
};

const uint8_t speedUp[] PROGMEM = {
  ATM_SET_TEMPO(40),
  ATM_STOP_CHAN,
};

const uint8_t normalSpeed[] PROGMEM = {
  ATM_SET_TEMPO(36),
  ATM_STOP_CHAN,
};

const unsigned char * const PROGMEM soundFX[] =
{
  sfxDoorClosed, pickUp, menuClick, shootBullet, speedUp, normalSpeed, 
};

const uint8_t intro[] PROGMEM = {
  ATM_SET_TEMPO(30),
  ATM_VOL(63),
  ATM_SL_VOL(-8),
  ATM_DELAY(16),
  ATM_NOTE_D6,
  ATM_DELAY(16),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(32),
  ATM_CUE(1),
  ATM_STOP_CHAN,
};

#endif
