#ifndef SFX_H
#define SFX_H

// 0: music + SFX   1: music only   2: SFX only   3: mute
byte soundMode = 0;

#define TEMPO_NORMAL          36
#define TEMPO_FAST            40

#define SFX_DOOR              0
#define SFX_PICKUP            1
#define SFX_MENU              2
#define SFX_SHOOT             3
#define SFX_LEVELUP           4
#define SFX_BEAMMEUPSCOTTY    5
#define SFX_YOUHURTME         6

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


const uint8_t levelUp[] PROGMEM = {
  ATM_VOL(16),
  ATM_SET_TEMPO(50),
  ATM_GLIS(1),
  ATM_ARP(0B01010011,0B00100001),
  ATM_SL_VOL(1),
  ATM_NOTE_C4,
  ATM_DELAY(64),
  ATM_SET_TEMPO(36),
  ATM_STOP_CHAN,
};

const uint8_t beamMeUpScotty[] PROGMEM = {
  ATM_VOL(32),
  ATM_GLIS(0B10000001),
  ATM_ARP(0B01010011,0B00100001),
  ATM_SL_VOL(1),
  ATM_VIB(32,0B10000111),
  ATM_NOTE_C7,
  ATM_DELAY(64),
  ATM_STOP_CHAN,
};

const uint8_t youHurtMe[] PROGMEM = {
  ATM_VOL(63),
  ATM_VIB(8,0B10000011),
  ATM_ARP(0B01010011,0B00100001),
  ATM_NOTE_G3,
  ATM_DELAY(16),
  ATM_GLIS(0B10000001),
  ATM_SL_VOL(-2),
  ATM_DELAY(16),
  ATM_STOP_CHAN,
};

const unsigned char * const PROGMEM soundFX[] =
{
  sfxDoorClosed, pickUp, menuClick, shootBullet, levelUp, beamMeUpScotty, youHurtMe,
};

const uint8_t intro[] PROGMEM = {
  ATM_SET_TEMPO(30),
  ATM_DELAY(16),
  ATM_VOL(63),
  ATM_SL_VOL(-8),
  ATM_ARP(0B01010011,0B00100001),
  ATM_NOTE_D6,
  ATM_DELAY(12),
  ATM_NOTE_D6,
  ATM_DELAY(10),
  ATM_NOTE_D6,
  ATM_DELAY(4),
  ATM_NOTE_A5,
  ATM_DELAY(32),
  ATM_CUE(1),
  ATM_STOP_CHAN,
};

#endif
