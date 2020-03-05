#include "header.h"
#include "CW3_Game.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_Player.h"

// customisable tilemap
#define tmCountXTiles 12
#define tmCountYTiles 12

// customisable background
#define starSizeGap starSize //can be defined as variables i.e. starSize or other MACROs
#define starSizeMin 1
#define starSizeRange 10
#define starChanceDenominator 500 //higher it is, lower the chance of their being a star (and thus frequency of stars)

// Colours
#define clrBgMain 0x3d2f30
#define clrBgStarWhite 0xffffff
#define clrBgStarRed 0xffe0e0
#define clrBgStarBlue 0xe0fffc
#define clrBgStarYellow 0xfeffe0

int tmTileDimensions; //global variable to store size of tiles
int tmStartingX; //global variable to store starting x coord to draw from
int tmStartingY; //global variable to store starting y coord to draw from

CW3_Game::CW3_Game() {

}

CW3_Game::~CW3_Game() {
	
}

void CW3_Game::virtSetupBackgroundBuffer() {
	fillBackground(clrBgMain);
	
	// declared local in this block as nothing inside of it is needed outside of it
	{
		int starSize = 0; // stars can be different sizes

		//for each x coordinate..
		for (int iX = 0; iX < getWindowWidth(); iX += starSizeGap) {

			//.. for each y coordinate..
			for (int iY = 0; iY < getWindowHeight(); iY += starSizeGap) {
			
				starSize = (rand() % starSizeRange) + starSizeMin; // get random star size

				//.. generate a random number and modulo it with for example, 100..
				switch (rand() % starChanceDenominator)
				{
					//.. if it results in a 0, 1, 2, or 3, draw a spot with the specified colour; if not don't draw a spot. (1/100 chance of a specific coloured spot, 1/25 chance of their being a spot)
				case 0: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarWhite); break;
				case 1: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarRed); break;
				case 2: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarBlue); break;
				case 3: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarYellow); break;

				}
			}
		}		
		
	}

	int dungeonTileMapDesign[tmCountYTiles][tmCountXTiles] = {
		//{tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty},
		//{tileWallTopNorthWest, tileWallNorthWest, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthEast, tileWallTopNorthEast},
		{tileWallTopNorthWest, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthEast},
		{tileWallTopWest, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tilePlayerSpawn, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopSouthWest, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallTopSouthEast},
	};

	

	// base the tiles dimensions on the windows height and the number of tiles in the x plane
	tmTileDimensions = (getWindowHeight()*.75) / tmCountYTiles;

	//start drawing from the remaining space divided by 2, so it is centered
	tmStartingX = (getWindowWidth() - tmTileDimensions * tmCountXTiles) / 2;
	tmStartingY = (getWindowHeight() - tmTileDimensions * tmCountYTiles) / 2;

	std::cout << "Tile Dimensions: " << tmTileDimensions << " Window Height: " << getWindowHeight() << "\n";

	CW3_Game::tm = new CW3_TileManager(tmTileDimensions, tmTileDimensions, tmCountXTiles, tmCountYTiles);
	
	// setting all tiles to tile map int 2D array
	for (int x = 0; x < tmCountXTiles; x++)
		for (int y = 0; y < tmCountYTiles; y++)
			tm->setMapValue(x,y, dungeonTileMapDesign[y][x]);
	tm->setTopLeftPositionOnScreen(tmStartingX, tmStartingY);
	tm->drawAllTiles(this, getBackgroundSurface());

}

void CW3_Game::virtMouseDown(int iButton, int iX, int iY) {
	
	if(tm->isValidTilePosition(iX, iY))
		std::cout << "Mouse clicked at: " << tm->getTileValueAtCoordinates(iX, iY) << "\n";
}

void CW3_Game::virtKeyDown(int iKeyCode) {
	/*
	switch (iKeyCode) {
	case SDLK_SPACE:
		lockBackgroundForDrawing(); //lock background so only 1 thing can draw to it at a time
		virtSetupBackgroundBuffer(); //call the method for setting up the background
		unlockBackgroundForDrawing();  //unlock backgruond so other things can draw to it
		redrawDisplay(); //redraw the background
		break;
	}*/
}

int CW3_Game::virtInitialiseObjects() {
	/*
	// Record the fact that we are about to change the array
	// so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);
	// Creates an array big enough for the number of objects that you want.
	createObjectArray(1);
	// You MUST set the array entry after the last one that you create to NULL,
	// so that the system knows when to stop.
	storeObjectInArray(0, new CW3_Player(,this));
	// NOTE: We also need to destroy the objects, but the method at the
	// top of this function will destroy all objects pointed at by the
	// array elements so we can ignore that here.
	setAllObjectsVisible(true);*/
	return 0;

}

CW3_TileManager * CW3_Game::getTileManager() {
	return tm;
}