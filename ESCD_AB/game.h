#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"
#include "text.h"


void stateGameNew()
{
  level = LEVEL_TO_START_WITH - 1;
  scorePlayer = 0;
  player.set();
  EEPROM.write(OFFSET_ESCD_START,GAME_ID);
  EEPROM.write(OFFSET_LEVEL, level);
  EEPROM.write(OFFSET_BUTTONS,buttonSchemeOffset);
  EEPROM.write(OFFSET_ESCD_END,GAME_ID);
  gameState = STATE_GAME_NEXT_LEVEL;
  
}

void stateGameContinue()
{
  scorePlayer = 0;
  player.set();
  gameState = STATE_GAME_NEXT_LEVEL;
}

void stateMenuPlay()
{
  if ((EEPROM.read(OFFSET_ESCD_START) == GAME_ID) && (EEPROM.read(OFFSET_ESCD_END) == GAME_ID))
  {
    level = EEPROM.read(OFFSET_LEVEL);
    drawTitleScreen();
    drawFloor();
    // " BUTTON SCHEME    N<>S  E<>W"  N<>S @ char 18 → x72, E<>W @ char 24 → x96
    drawSelectedWordMask(newGameOffset ? 96 : 72);
    if (arduboy.justPressed(RIGHT_BUTTON))
    {
      play_SFX(SFX_MENU);
      newGameOffset = 4;
      //gameState = STATE_GAME_CONTINUE;
    }
    if (arduboy.justPressed(LEFT_BUTTON))
    {
      play_SFX(SFX_MENU);
      newGameOffset = 0;
      //gameState = STATE_GAME_NEW;
    }
    if (arduboy.justPressed(B_BUTTON))
    {
      play_SFX(SFX_PICKUP);
      gameState = (newGameOffset ? STATE_GAME_CONTINUE : STATE_GAME_NEW);
    }
    if (arduboy.justPressed(A_BUTTON))
    {
      play_SFX(SFX_PICKUP);
      statePrepForMainMenu();
    }
  }
  
  else
  {
    gameState = STATE_GAME_NEW;
  }

  // 1-based: NEXT_LEVEL increments, then buildRooms uses levels[level-1]
}

void stateGamePlaying()
{
  checkOrderOfObjects();
  drawRoom();
  if (!bitRead(player.characteristics, 5))
  {
    if (!bitRead(player.characteristics, 4)) checkInputs();
  }
  else
  {
    if (player.steps < 5)
    {
      if (arduboy.everyXFrames(2)) walkThroughDoor();
    }
    else 
    {
      player.isOnTile = goToTile(currentRoom);
      currentRoomY = setCurrentRoomY(player.isOnTile);
      currentRoom = goToRoom(currentRoom);
      player.x = translateTileToX (player.isOnTile) + offsetXAfterDoor(player.isOnTile);
      player.y = translateTileToY (player.isOnTile) + offsetYAfterDoor(player.isOnTile) + currentRoomY ;
      player.steps = 0;
      enterRoom(currentRoom);
      bitClear (player.characteristics, 5);
      bitSet (player.characteristics, 6);
      gameState = STATE_GAME_NEXT_ROOM;
      return; //don't update the enemies yet, first go through the door
    }
  }
  updatePlayer();
  if (!bitRead(player.characteristics, 4))
  {
    updateEnemies();
    updatePlayerShot();
    updateEnemyShot();
  }
  drawHUD();
}


void stateGameNextRoom()
{
  checkOrderOfObjects();
  drawRoom();

  {
    if (player.steps < 5)
    {
      if (arduboy.everyXFrames(2)) walkThroughDoor();
    }
    else
    {
      player.steps = 0;
      bitClear (player.characteristics, 6);
      statePrepForRoom();
    }
  }
  drawHUD();
}

void stateGameNextLevel()
{
  level++;
  player.life = 3;
  EEPROM.write(OFFSET_LEVEL,level);
  if (level > AMOUNT_OF_LEVELS)
  {
    loadAndFillMessage(7);
    addNumber(scorePlayer,24,6);
    gameState = STATE_GAME_FINISHED;
  }
  else
  {
    currentRoom = 0;
    player.isOnTile = TILE_GAME_STARTS_ON;
    currentRoomY = ROOM_DRAWING_OFFSET;
    player.x = translateTileToX (player.isOnTile);
    player.y = translateTileToY (player.isOnTile) + currentRoomY ;
    buildRooms();
    enterRoom(currentRoom);
    statePrepForPause();
    gameState = STATE_GAME_PAUSE;
  }
}


void stateGamePause()
{
  drawWalls();
  drawFloor();
  drawHUD();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    statePrepForRoom();
  }
}


void stateGameOver()
{
  drawWalls();
  drawFloor();
  drawPlayer();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    playMenuMusic();
    statePrepForMainMenu();
  }
}

void stateGameFinished()
{
  drawWalls();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) 
  {
    playMenuMusic();
    statePrepForMainMenu();
  }
}

void stateGameTransporting()
{
  playerTransporting();
  drawWalls();
  drawFloor();
  drawHUD();
  drawPlayer();
  if (arduboy.everyXFrames(90))
  {
    currentRoom = transportToRoom(currentRoom);
    player.x = translateTileToX (player.isOnTile) ;
    player.y = translateTileToY (player.isOnTile) + currentRoomY ;
    player.steps = 0;
    enterRoom(currentRoom);
  }
}



#endif
