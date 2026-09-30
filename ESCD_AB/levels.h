#ifndef LEVELS_H
#define LEVELS_H

#define MAX_AMOUNT_OF_ROOMS                       32
#define MAX_AMOUNT_OF_INFLUENCING_OBJECTS         16
#define MAX_AMOUNT_OF_TRANSPORTERS                16
#define AMOUNT_OF_ROOMS_AT_BYTE                   0
#define AMOUNT_OF_TRANSPORTERS_AT_BYTE            1
#define AMOUNT_OF_INFLUENCING_OBJECTS_AT_BYTE     2
#define LEVEL_DOOR_DATA_START_AT_BYTE             3
#define LEVEL_ROOM_DATA_START_AT_BYTE             4
#define ROOMS_DATA_START_AT_BYTE                  5
#define DOORS_DATA_START_AT_BYTE                  ROOMS_DATA_START_AT_BYTE + 1
#define ELEMENTS_DATA_START_AT_BYTE               ROOMS_DATA_START_AT_BYTE + 5            
#define BYTES_USED_FOR_EVERY_ROOM                 13

// ROOM ORDER OF TILES
//                 /\
//                /  \
//               / 00 \
//              /\    /\
//             /  \  /  \
//            / 01 \/ 05 \
//            \    /\    /
// NORTH       \  /  \  /         EAST
//           02 \/ 06 \/ 10  
//        /\    /\    /\    /\
//       /  \  /  \  /  \  /  \
//      / 03 \/ 07 \/ 11 \/ 15 \
//     /\    /\    /\    /\    /\
//    /  \  /  \  /  \  /  \  /  \
//   / 04 \/ 08 \/ 12 \/ 16 \/ 20 \
//   \    /\    /\    /\    /\    /
//    \  /  \  /  \  /  \  /  \  /
//     \/ 09 \/ 13 \/ 17 \/ 21 \/
//      \    /\    /\    /\    /
//       \  /  \  /  \  /  \  /
//        \/ 14 \/ 18 \/ 22 \/
//              /\    /\    
// WEST        /  \  /  \         SOUTH
//            / 19 \/ 23 \
//            \    /\    /
//             \  /  \  /
//              \/ 24 \/
//               \    /
//                \  /
//                 \/


//const unsigned char PROGMEM centerOfTiles[][2] =
//{
//  { 58, 18}, {46, 24}, {34, 30}, {22, 36}, {10, 42}, // Tile  0  1  2  3  4
//  { 70, 24}, {58, 30}, {46, 36}, {34, 42}, {22, 48}, // Tile  5  6  7  8  9
//  { 82, 30}, {70, 36}, {58, 42}, {46, 48}, {34, 54}, // Tile 10 11 12 13 14
//  { 94, 36}, {82, 42}, {70, 48}, {58, 54}, {46, 60}, // Tile 15 16 17 18 19
//  {106, 42}, {94, 48}, {82, 56}, {70, 60}, {58, 66}, // Tile 20 21 22 23 24
//};

// NEXT LEVEL DOOR
//0b00000001,
//  |||||||└->  \  these 2 bits are used to determine what door is the next level door, make sure it exists
//  ||||||└-->  /. NORTH = 0B00000000; EAST = 0B00000001; SOUTH = 0B00000010; WEST : 0B00000011
//  |||||└--->  \ 
//  ||||└---->   |
//  |||└----->   | these 6 bits are used to set in which room the next level door is leading to the exit room
//  ||└------>   |
//  |└------->   |
//  └-------->  / 

// NEXT LEVEL ROOM
//0b00000001,
//  |||||||└--->  \ 
//  ||||||└---->   |
//  |||||└----->   | these 6 bits are used to set in which room the next level TILE is leading to the next level
//  ||||└------>   |
//  |||└------->   |
//  ||└-------->  / 
//  |└--------->  NOT USED
//  └---------->  NOT USED

// ALL THE DATA FOR EACH ROOM AND EACH ROOM HAS 13 BYTES
//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
//0b11001110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
//  ||||||||    ||||||||                                        ||||||||                ||||||||    ||||||||
//  ||||||||    ||||||||                                        ||||||||                ||||||||    |||||||└->0  \  these 3 bits are used to determine kind of sprite used for the floor
//  ||||||||    ||||||||                                        ||||||||                ||||||||    ||||||└-->1   | 0 = none; 1 = box; 2 = spike; 3 = piramide; 4 = pit; 5 = ; 6 =; 7= LEVEL UP
//  ||||||||    ||||||||                                        ||||||||                ||||||||    |||||└--->2  /
//  ||||||||    ||||||||                                        ||||||||                ||||||||    ||||└---->3  \
//  ||||||||    ||||||||                                        ||||||||                ||||||||    |||└----->4   | if the floor is 
//  ||||||||    ||||||||                                        ||||||||                ||||||||    ||└------>5   | these 5 bits are used to determine on what floor tile the element is
//  ||||||||    ||||||||                                        ||||||||                ||||||||    |└------->6   |
//  ||||||||    ||||||||                                        ||||||||                ||||||||    └-------->7  /  if all 8 bits == 0 => no floor element
//  ||||||||    ||||||||                                        ||||||||                ||||||||
//  ||||||||    ||||||||                                        ||||||||                |||||||└->0  \   these 3 bits are used to determine kind of sprite used for the object
//  ||||||||    ||||||||                                        ||||||||                ||||||└-->1   |  0 = black card; 1 = white card; 2 = battery; 3 = bullet; 4 = chip; 5 = teleport, 6 = switch OFF, 7 switch = ON,
//  ||||||||    ||||||||                                        ||||||||                |||||└--->2  /
//  ||||||||    ||||||||                                        ||||||||                ||||└---->3  \
//  ||||||||    ||||||||                                        ||||||||                |||└----->4   |
//  ||||||||    ||||||||                                        ||||||||                ||└------>5   |  these 5 bits are used to determine on what floor tile the object is
//  ||||||||    ||||||||                                        ||||||||                |└------->6   |
//  ||||||||    ||||||||                                        ||||||||                └-------->7  /   if all 8 bits == 0 => no object
//  ||||||||    ||||||||                                        |||||||| 
//  ||||||||    ||||||||                                        |||||||└->0  \   hese 3 bits are used to determine kind of sprite used for the enemy
//  ||||||||    ||||||||                                        ||||||└-->1   |  0 = BOX; 1 = FLYER; 2 = MOVER; 3 = SHOOTER;
//  ||||||||    ||||||||                                        |||||└--->2  /
//  ||||||||    ||||||||                                        ||||└---->3  \
//  ||||||||    ||||||||                                        |||└----->4   |
//  ||||||||    ||||||||                                        ||└------>5   |  these 5 bits are used to determine on what floor tile the enemy is
//  ||||||||    ||||||||                                        |└------->6   |
//  ||||||||    ||||||||                                        └-------->7  /   if all 8 bits == 0 => no enemy
//  ||||||||    ||||||||
//  ||||||||    |||||||└->0  \  these 2 bits are used to determine what door you'll go to
//  ||||||||    ||||||└-->1  /
//  ||||||||    |||||└--->2  \
//  ||||||||    ||||└---->3   |
//  ||||||||    |||└----->4   | these 6 bits are used for the roomnumber you'll go to
//  ||||||||    ||└------>5   |
//  ||||||||    |└------->6   |
//  ||||||||    └-------->7  /
//  ||||||||
//  |||||||└->0  DOOR NORTH  is closed (0 = false / 1 = true)
//  ||||||└-->1  DOOR EAST   is closed (0 = false / 1 = true)
//  |||||└--->2  DOOR SOUTH  is closed (0 = false / 1 = true)
//  ||||└---->3  DOOR WEST   is closed (0 = false / 1 = true)
//  |||└----->4  DOOR NORTH  exists    (0 = false / 1 = true)
//  ||└------>5  DOOR EAST   exists    (0 = false / 1 = true)
//  |└------->6  DOOR SOUTH  exists    (0 = false / 1 = true)
//  └-------->7  DOOR WEST   exists    (0 = false / 1 = true)
//
//
//
// transporters data, the order of the data is by ascending numbers (ROOM X, ROOM Y, ROOM Z , ...)
// GOTO ROOM
//0b00000001,
//  |||||||└->0  \
//  ||||||└-->1   |
//  |||||└--->2   | these 6 bits are used for the roomnumber you'll go to
//  ||||└---->3   |
//  |||└----->4   |
//  ||└------>5  /
//  |└------->6 NOT USED
//  └-------->7 NOT USED
//
//
//
// influence record is 2 bytes (old unused middle "from room" byte removed)
// ELEMENTS      WHAT
//  IN ROOM    ELEMENTS
//0b00000011, 0b00011111,
//  ||||||||    ||||||||
//  ||||||||    |||||||└->0 FLOOR  5 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||||||└-->1 FLOOR  4 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |||||└--->2 FLOOR  3 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||||└---->3 FLOOR  2 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |||└----->4 FLOOR  1 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||└------>5 OBJECT 3 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |└------->6 ENEMY  2 INFLUENCED (0 = false / 1 = true)
//  ||||||||    └-------->7 ENEMY  1 INFLUENCED (0 = false / 1 = true)
//  ||||||||
//  |||||||└->0  \
//  ||||||└-->1   |
//  |||||└--->2   | these 6 bits are the room whose elements get toggled
//  ||||└---->3   |
//  |||└----->4   |
//  ||└------>5  /
//  |└------->6 NOT USED
//  └-------->7 NOT USED
//
//

const unsigned char PROGMEM ESCDlevel01[] =
{
  4,          // amount of rooms
  0,          // amount of transporters
  1,          // amount of rooms with influenceable objects

  0b00001010,  // NEXT LEVEL DOOR
  0b00000010,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b10111011, 0b00001010, 0b00000111, 0b00000000, 0b00001101, 0b00000000, 0b00000000, 0b10110001, 0b10001001, 0b10111001, 0b10101001, 0b00000000, 0b00000000, // room0
  0b10100000, 0b00000000, 0b00001111, 0b00000000, 0b00000001, 0b00100000, 0b10100000, 0b00000000, 0b00101100, 0b00110100, 0b00111100, 0b01000100, 0b01001100, // room1
  0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100001, 0b00000001, 0b10100011, 0b10011011, 0b10010011, 0b10001011, 0b10000011, 0b01111011, // room2
  0b10100000, 0b00000000, 0b00000011, 0b00000000, 0b00000101, 0b00000010, 0b11000010, 0b01100110, 0b10001001, 0b01101001, 0b00111001, 0b01011001, 0b00000000, // room3

  // transporters

  // influence
  0b00000001, 0b00011111, // I0
};
// LAYOUT 0:180,180 1:320,180 2:180,40 3:40,180



const unsigned char PROGMEM ESCDlevel02[] =
{
  5,          // amount of rooms
  0,          // amount of transporters
  1,          // amount of rooms with influenceable objects

  0b00001110,  // NEXT LEVEL DOOR
  0b00000011,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b00100000, 0b00000000, 0b00000111, 0b00000000, 0b00000000, 0b01010001, 0b00000000, 0b00011011, 0b00100001, 0b01011100, 0b10000100, 0b01000001, 0b00010001, // room0
  0b11110001, 0b00001110, 0b00001011, 0b00010000, 0b00000001, 0b00100001, 0b00000000, 0b00000010, 0b00111100, 0b00110100, 0b00101100, 0b01000100, 0b01001100, // room1
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000101, 0b00000010, 0b10100010, 0b01010110, 0b01111011, 0b00101011, 0b01011011, 0b00110011, 0b10000011, // room2
  0b01000000, 0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00100000, 0b00000000, 0b00010100, 0b01101011, 0b01011011, 0b01110011, 0b01010011, 0b01100111, // room3
  0b00010000, 0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b01010000, 0b01110000, 0b10110000, 0b00101100, 0b01001100, 0b11000100, 0b10100100, 0b10001100, // room4

  // transporters

  // influence
  0b00000001, 0b00011111, // I0
};
// LAYOUT 0:40,180 1:180,180 2:320,180 3:180,40 4:180,320

const unsigned char PROGMEM ESCDlevel03[] =
{
  9,          // amount of rooms
  2,          // amount of transporters
  2,          // amount of rooms with influenceable objects

  0b00001010,  // NEXT LEVEL DOOR
  0b00000010,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b11110001, 0b00001010, 0b00000111, 0b00010100, 0b00001101, 0b00000001, 0b00000000, 0b11000011, 0b10011100, 0b10111100, 0b10010100, 0b00001011, 0b00101011, // room0
  0b10100000, 0b00000000, 0b00010011, 0b00000000, 0b00000001, 0b01011001, 0b00000000, 0b10100010, 0b00010100, 0b00111100, 0b01100100, 0b10001100, 0b10110100, // room1
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000100, 0b01100111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // room2
  0b00100000, 0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b01001011, 0b10111010, 0b01100110, 0b10010011, 0b01101011, 0b00111011, 0b01000011, 0b00000000, // room3
  0b11000100, 0b00000000, 0b00000000, 0b00011100, 0b00000101, 0b10100000, 0b00100000, 0b01100110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // room4
  0b00010000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b01000001, 0b10000001, 0b11000001, 0b01100011, 0b00000011, 0b00100011, 0b10100011, 0b00000000, // room5
  0b01010000, 0b00011110, 0b00000000, 0b00100000, 0b00000000, 0b00100000, 0b00000000, 0b11000000, 0b01110010, 0b01100010, 0b01101010, 0b01011010, 0b01010010, // room6
  0b01010100, 0b00010010, 0b00000000, 0b00011000, 0b00000000, 0b11000010, 0b00000000, 0b01100101, 0b01101100, 0b01011100, 0b00000000, 0b00000000, 0b00000000, // room7
  0b00010000, 0b00011010, 0b00000000, 0b00000000, 0b00000000, 0b10101011, 0b00000000, 0b01100101, 0b01101100, 0b01011100, 0b00000000, 0b00000000, 0b00000000, // room8

  // transporters
  0b00000110, // T0
  0b00000110, // T1

  // influence
  0b00000001, 0b00010001, // I0
  0b00000000, 0b00011100, // I1
};
// LAYOUT 0:160,160 1:300,160 2:160,20 3:20,160 4:440,160 5:160,300 6:440,440 7:440,300 8:440,580


const unsigned char PROGMEM ESCDlevel04[] =
{
  9,          // amount of rooms
  1,          // amount of transporters
  2,          // amount of rooms with influenceable objects

  0b00001011,  // NEXT LEVEL DOOR
  0b00000010,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b01100000, 0b00000000, 0b00000111, 0b00010100, 0b00000000, 0b00100000, 0b10100000, 0b11000010, 0b10001100, 0b01011100, 0b00000000, 0b00000000, 0b00000000, // room0
  0b10100010, 0b00000000, 0b00001111, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01100101, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // room1
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00010101, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // room2
  0b11000000, 0b00000000, 0b00000000, 0b00010000, 0b00000101, 0b11000010, 0b00000000, 0b00000111, 0b00001011, 0b00110011, 0b00101011, 0b10011100, 0b10111100, // room3
  0b01010000, 0b00001110, 0b00000000, 0b00100000, 0b00000000, 0b10100011, 0b00000000, 0b11000011, 0b01110001, 0b01101001, 0b01100001, 0b01011001, 0b01010001, // room4
  0b01110010, 0b00000010, 0b00001011, 0b00011000, 0b00000000, 0b00100001, 0b00000000, 0b10100001, 0b01100010, 0b10010010, 0b11000010, 0b00110010, 0b00000010, // room5
  0b00110000, 0b00010110, 0b00011111, 0b00000000, 0b00000000, 0b10111011, 0b10011011, 0b11000000, 0b00011100, 0b01000100, 0b01100100, 0b00110100, 0b00001100, // room6
  0b10101000, 0b00000000, 0b00100011, 0b00000000, 0b00011001, 0b00100000, 0b10100010, 0b10110110, 0b10001001, 0b01011001, 0b01111001, 0b01101001, 0b10011001, // room7
  0b10010000, 0b00010010, 0b00000000, 0b00000000, 0b00011101, 0b01111001, 0b10101001, 0b10100001, 0b01010100, 0b10110100, 0b10000100, 0b01100001, 0b01000001, // room8

  // transporters
  0b00000101, // T0

  // influence
  0b00001000, 0b00011100, // I0
  0b00000011, 0b00000011, // I1
};
// LAYOUT 0:40,40 1:180,40 2:180,180 3:320,40 4:320,180 5:40,180 6:40,320 7:180,320 8:320,320


const unsigned char PROGMEM ESCDlevel05[] =
{
  5,          // amount of rooms
  0,          // amount of transporters
  1,          // amount of rooms with influenceable objects

  0b00010011,  // NEXT LEVEL DOOR
  0b00000100,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b00100000, 0b00000000, 0b00000111, 0b00000000, 0b00000000, 0b11000000, 0b00000000, 0b00100011, 0b00011100, 0b01001100, 0b01011100, 0b10000100, 0b00110100, // room0
  0b11110000, 0b00001010, 0b00001011, 0b00001000, 0b00000001, 0b00100001, 0b00000000, 0b10100000, 0b11000010, 0b10010010, 0b01100010, 0b00110010, 0b00000010, // room1
  0b11110000, 0b00000110, 0b00001111, 0b00000100, 0b00000101, 0b11000001, 0b00000000, 0b00000110, 0b00100010, 0b01000010, 0b01100010, 0b10000010, 0b10100010, // room2
  0b10100010, 0b00000000, 0b00010011, 0b00000000, 0b00001001, 0b01010010, 0b00000000, 0b00000010, 0b01111011, 0b10000011, 0b00101011, 0b00110011, 0b01100011, // room3
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00001101, 0b10100011, 0b00000000, 0b00000100, 0b01100111, 0b00101011, 0b00001011, 0b01111011, 0b10101011, // room4

  // transporters

  // influence
  0b00000000, 0b00011000, // I0
};
// LAYOUT 0:40,40 1:180,40 2:320,40 3:460,40 4:600,40


const unsigned char PROGMEM ESCDlevel06[] =
{
  8,          // amount of rooms
  1,          // amount of transporters
  3,          // amount of rooms with influenceable objects

  0b00001001,  // NEXT LEVEL DOOR
  0b00000010,  // NEXT LEVEL ROOM

//DOOR+STATE  NORTH GOTO  EAST  GOTO  SOUTH GOTO  WEST  GOTO   ENEMY 1      ENEMY 2    OBJECT 3     FLOOR 1     FLOOR 2     FLOOR 3     FLOOR 4     FLOOR 5
  0b01100100, 0b00000000, 0b00000111, 0b00001100, 0b00000000, 0b11000001, 0b00000000, 0b00100100, 0b01010001, 0b00011011, 0b01001011, 0b01000011, 0b10010100, // room0
  0b11000000, 0b00000000, 0b00000000, 0b00010000, 0b00000001, 0b00000000, 0b00000000, 0b01011001, 0b00010001, 0b01100001, 0b01010001, 0b10000001, 0b01000001, // room1
  0b00100000, 0b00000000, 0b00001111, 0b00000000, 0b00000000, 0b11000001, 0b00000000, 0b00100100, 0b01001011, 0b00011011, 0b01111011, 0b01011011, 0b00101011, // room2
  0b10111000, 0b00000010, 0b00010011, 0b00000000, 0b00001001, 0b10110011, 0b00000000, 0b00000101, 0b10100100, 0b10000100, 0b01100100, 0b01000100, 0b00100100, // room3
  0b11111000, 0b00000110, 0b00011011, 0b00010100, 0b00001101, 0b00000000, 0b00000000, 0b01011011, 0b11000100, 0b10010100, 0b01100100, 0b00110100, 0b00000100, // room4
  0b00010000, 0b00010010, 0b00000000, 0b00000000, 0b00000000, 0b11000011, 0b00000000, 0b01100111, 0b00111100, 0b00110100, 0b01011100, 0b00000000, 0b00000000, // room5
  0b11000000, 0b00000000, 0b00000000, 0b00011100, 0b00010001, 0b00101000, 0b00001000, 0b00000110, 0b00010100, 0b00111100, 0b01100100, 0b01011100, 0b01010100, // room6
  0b00010000, 0b00011010, 0b00000000, 0b00000000, 0b00000000, 0b01100010, 0b00000000, 0b10000110, 0b00110100, 0b00111100, 0b10010100, 0b01101100, 0b01000100, // room7

  // transporters
  0b00000100, // T0

  // influence
  0b00000110, 0b00011111, // I0
  0b00000100, 0b00000100, // I1
  0b00000011, 0b00000100, // I2
};
// LAYOUT 0:220,40 1:360,40 2:80,180 3:220,180 4:360,180 5:360,320 6:500,180 7:500,320


// pointer table in flash too — 2 bytes per level, no SRAM copy
const unsigned char * const PROGMEM levels[] =
{
  ESCDlevel01, ESCDlevel02, ESCDlevel03, ESCDlevel04, ESCDlevel05, ESCDlevel06
};

#define AMOUNT_OF_LEVELS  (sizeof(levels) / sizeof(levels[0]))

#endif
