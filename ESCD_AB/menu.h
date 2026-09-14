#ifndef MENU_H
#define MENU_H

#define SET_THE_DANCERS_Y       ROOM_DRAWING_OFFSET + 9

#include "globals.h"
#include "room.h"

// main ticker: "      CONF SDFX INFO PLAY"
// each glyph is 4 columns; words start at charBox x = 24, 44, 64, 84
PROGMEM const byte menuWordX[] = { 16, 36, 64, 84 };

void drawTitleScreen()
{
  if (currentRoomY == 0) currentRoomY = ROOM_DRAWING_OFFSET;
  drawWalls();
}

void checkSoundState(byte mode)
{
  soundMode = mode;
  if (mode == 3)
  {
    ATM.stop();
    arduboy.audio.off();
    return;
  }
  arduboy.audio.on();
  ATM.play(menuSong);
  if (mode >= 2) ATM.pause();   // SFX only: keep ISR, freeze score
}

byte tickerYAt(byte x)
{
  return (x < 58) ? (x >> 1) : (58 - (x >> 1));
}

void drawSelectedWordMask(byte x0)
{
  if (arduboy.everyXFrames(16)) bitToggle(showMask, 0);
  if (!showMask) return;
  for (byte i = 0; i < 8; i++)
  {
    byte x = x0 + (i << 1);
    sprites.drawPlusMask(x, currentRoomY + 38 - tickerYAt(x), selector_plus_mask, 0);
  }
}

void statePrepForMainMenu()
{
  currentRoomY = ROOM_DRAWING_OFFSET;
  loadAndFillMessage(0);
  setTicker = TEXT_STAND_STILL;
  showTicker = TRUE;
  gameState = STATE_MENU_MAIN;
}

void stateMenuIntro()
{
  if (arduboy.everyXFrames(120))
  {
    playMenuMusic();
    statePrepForMainMenu();
  }
  sprites.drawSelfMasked(49, 20, T_arg, 0);
}

void stateMenuMain()
{
  drawTitleScreen();
  drawFloor();
  //drawGameName();

  drawSelectedWordMask(pgm_read_byte(&menuWordX[menuSelection]));

  if (arduboy.everyXFrames(26)) danceDroid = !danceDroid;

  sprites.drawPlusMask(51, 9+SET_THE_DANCERS_Y, droid_plus_mask, 2+danceDroid);

  // drawing the 4 enemies on the title screen a loop is not saving memory
  sprites.drawPlusMask(75, 21+SET_THE_DANCERS_Y, enemies_plus_mask, 2+danceDroid);
  sprites.drawPlusMask(27, 21+SET_THE_DANCERS_Y, enemies_plus_mask, 6+danceDroid);
  sprites.drawPlusMask(99, 33+SET_THE_DANCERS_Y, enemies_plus_mask, 10+danceDroid);
  sprites.drawPlusMask(3, 33+SET_THE_DANCERS_Y, enemies_plus_mask, 14+danceDroid);



  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 3))
  {
    play_SFX(SFX_MENU);
    menuSelection++;
  }
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 0))
  {
    play_SFX(SFX_MENU);
    menuSelection--;
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    play_SFX(SFX_PICKUP);
    gameState = menuSelection + 1;
    loadAndFillMessage(menuSelection + 1);
    if (gameState == STATE_MENU_SDFX)
    {
      menuSelection = soundMode;
    }
    
  }
}

void stateMenuConf()
{
  drawTitleScreen();
  drawFloor();
  // " BUTTON SCHEME    N<>S  E<>W"  N<>S @ char 18 → x72, E<>W @ char 24 → x96
  drawSelectedWordMask(buttonSchemeOffset ? 96 : 72);
  if (arduboy.justPressed(RIGHT_BUTTON))
  {
    play_SFX(SFX_MENU);
    buttonSchemeOffset = 4;
  }
  if (arduboy.justPressed(LEFT_BUTTON))
  {
    play_SFX(SFX_MENU);
    buttonSchemeOffset = 0;
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    play_SFX(SFX_PICKUP);
    statePrepForMainMenu();
  }
}

void stateMenuInfo()
{
  drawTitleScreen();
  drawFloor();
  setTicker = TEXT_SCROLL_LEFT;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    play_SFX(SFX_PICKUP);
    statePrepForMainMenu();
  }
}

void stateMenuSdfx()
{
  drawTitleScreen();
  drawFloor();
  drawSelectedWordMask(pgm_read_byte(&menuWordX[menuSelection]));
  // " MUSIC SOUND       ON   OFF"  ON @ char 19 → x76, OFF @ char 24 → x96
  //drawSelectedWordMask(arduboy.audio.enabled() ? 76 : 96);
  //if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.on();
  //if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.off();
  
  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 3))
  {
    play_SFX(SFX_MENU);
    menuSelection++;
    checkSoundState(menuSelection);
  }
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 0))
  {
    play_SFX(SFX_MENU);
    menuSelection--;
    checkSoundState(menuSelection);
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    play_SFX(SFX_MENU);
    arduboy.audio.saveOnOff();
    menuSelection = STATE_MENU_SELECT_SDFX;
    statePrepForMainMenu();
  }
}

#endif
