#pragma once

//tile map names corresponding to ints, used for setting tiles to correct image

// blank space has code -1
#define tileEmpty -1

// floors have code 0<=x<50 (aka things character can walk on)
#define tileFloor1 1

// special floors i.e. spawners:
#define tilePlayerSpawn 0
#define tileBaseEnemySpawn 49

// walls have code 50<=x<150 (aka things character cannot walk through)
#define tileWallNorthMid 50
#define tileWallNorthEast 51
#define tileWallNorthWest 52
#define tileWallSouthMid 53
#define tileWallSouthEast 54
#define tileWallSouthWest 55

// wall tops have code 150<=x<200 (character cannot walk on these either)
#define tileWallTopNorthMid 150
#define tileWallTopNorthEast 151
#define tileWallTopNorthWest 152
#define tileWallTopEast 153
#define tileWallTopWest 154
#define tileWallTopSouthMid 155
#define tileWallTopSouthEast 156
#define tileWallTopSouthWest 157