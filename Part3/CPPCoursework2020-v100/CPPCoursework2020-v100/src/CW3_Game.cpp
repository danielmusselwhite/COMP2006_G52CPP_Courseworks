#include "header.h"
#include "CW3_Game.h"
#include "CW3_TileManager.h"
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
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, puddleLight, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
		{tileWallTopSouthWest, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallSouthMid, tileWallTopSouthEast},
	};



	// base the tiles dimensions on the windows height and the number of tiles in the x plane
	m_tmTileDimensions = (getWindowHeight()*.75) / tmCountYTiles;

	//start drawing from the remaining space divided by 2, so it is centered
	m_tmStartingX = (getWindowWidth() - m_tmTileDimensions * tmCountXTiles) / 2;
	m_tmStartingY = (getWindowHeight() - m_tmTileDimensions * tmCountYTiles) / 2;

	std::cout << "Tile Dimensions: " << m_tmTileDimensions << " Window Height: " << getWindowHeight() << "\n";

	m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

	// setting all tiles to tile map int 2D array
	for (int x = 0; x < tmCountXTiles; x++)
		for (int y = 0; y < tmCountYTiles; y++)
			m_tm->setMapValue(x, y, dungeonTileMapDesign[y][x]);
	m_tm->setTopLeftPositionOnScreen(m_tmStartingX, m_tmStartingY);
	m_tm->drawAllTiles(this, getBackgroundSurface());

}

void CW3_Game::virtMouseDown(int iButton, int iX, int iY) {

}

void CW3_Game::virtKeyDown(int iKeyCode) {
	
}
int CW3_Game::virtInitialiseObjects() {
	std::vector<std::pair<int,int>> floors;

	// setting all tiles to tile map int 2D array
	for (int x = 0; x < tmCountXTiles; x++)
		for (int y = 0; y < tmCountYTiles; y++)
			if (m_tm->getMapValue(x, y) >= 0 && m_tm->getMapValue(x, y) < 50)
				floors.push_back((std::make_pair(x,y)));

	// spawn player at random floor
	int floorIndex = rand() % floors.size();
	std::pair<int, int> floor = floors.at(floorIndex);

	appendObjectToArray(new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, m_vecDisplayableObjects.size(), 100, 1, 3, 7));

	//erase this floor so we can't have more than one thing spawn on same floor
	floors.erase(floors.begin(), floors.begin() + floorIndex);

	return 0;
}