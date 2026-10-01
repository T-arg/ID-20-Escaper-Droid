/*
  Escaper Droid
  Arduboy version 0.9.5
  
  STARTED by TEAM a.r.g.
  2016 - JO3RI - STG

  CONTINUED by
  2026 - JO3RI - Onebit

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 20

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "room.h"
#include "elements.h"
#include "inputs.h"
#include "player.h"
#include "song.h"


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM  mainGameLoop[] =
{
  stateMenuMain,
  stateMenuConf,
  stateMenuSdfx,
  stateMenuInfo,
  stateMenuPlay,
  stateMenuIntro,
  stateGamePlaying,
  stateGameNextRoom,
  stateGameNextLevel,
  stateGamePause,
  stateGameOver,
  stateGameTransporting,
  stateGameFinished,
  stateGameNew,
  stateGameContinue,
};


void setup()
{
  arduboy.boot();
  arduboy.audio.begin();
  arduboy.setFrameRate(45);
  ATM.playSfx(intro, 0);
  if ((EEPROM.read(OFFSET_ESCD_START) == GAME_ID) && (EEPROM.read(OFFSET_ESCD_END) == GAME_ID))
  {
    buttonSchemeOffset = EEPROM.read(OFFSET_BUTTONS);
  }
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
};

