#include "header.h"
#include "CW3_Game.h"
#include "CW3_TileManager.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_Player.h"
#include "CW3_SimpleEnemy.h"

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
#define clrText 0xe0fffb

CW3_Game::CW3_Game() {

}

CW3_Game::~CW3_Game() {

}

void CW3_Game::virtSetupBackgroundBuffer() {
	fillBackground(clrBgMain);

	// SETTING UP THE STARRY BACKGROUND
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

	//SETTING UP THE TILE MANAGER
	{
		
		int dungeonTileMapDesign[tmCountYTiles][tmCountXTiles] = {
			//{tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty, tileEmpty},
			//{tileWallTopNorthWest, tileWallNorthWest, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthEast, tileWallTopNorthEast},
			{tileWallTopNorthWest, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthMid, tileWallTopNorthEast},
			{tileWallTopWest, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallNorthMid, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloorWithCrate, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
			{tileWallTopWest, tileFloorWithCrate, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileFloor1, tileWallTopEast},
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

	// SETTING UP BACKGROUND TEXT
	{
		drawBackgroundString(15, 40, "C++ Coursework - Daniel Musselwhite", clrText, NULL);
	}
}

void CW3_Game::virtMouseDown(int iButton, int iX, int iY) {
	try {
		CW3_Player* player = getObjectOfType<CW3_Player>();
		if (iButton == SDL_BUTTON_LEFT) {
			player->shootGun();
		}
	}

	catch (int e) {
		std::cout << "\nPlayer could not be found";
	}
	
}

void CW3_Game::virtKeyDown(int iKeyCode) {
	switch (iKeyCode) {
	case SDLK_ESCAPE: // End program when escape is pressed
		setExitWithCode(0);
		break;
	}
}

int CW3_Game::virtInitialiseObjects() {
	std::vector<std::pair<int,int>> floors;

	//  getting all floor tiles (that the player could spawn on)
	for (int x = 0; x < tmCountXTiles; x++)
		for (int y = 0; y < tmCountYTiles; y++)
			if (m_tm->getMapValue(x, y) >= 0 && m_tm->getMapValue(x, y) < 50)
				floors.push_back((std::make_pair(x,y)));

	// spawn player at random floor
	int floorIndex = rand() % floors.size();
	std::pair<int, int> floor = floors.at(floorIndex);

	//m_pPlayer = new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, m_vecDisplayableObjects.size(), 100, 1, 3, 7);
	appendObjectToArray(new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 100, 2, 4, 10));

	//erase this floor so we can't have more than one thing spawn on same floor
	floors.erase(floors.begin() + floorIndex);

	// spawn enemy at random floor
	floorIndex = rand() % floors.size();
	floor.first = floors.at(floorIndex).first;
	floor.second = floors.at(floorIndex).second;
	appendObjectToArray(new CW3_SimpleEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 50, 20, 30, 1, 10));
	floors.erase(floors.begin() + floorIndex);
	
	// spawn enemy at random floor
	floorIndex = rand() % floors.size();
	floor.first = floors.at(floorIndex).first;
	floor.second = floors.at(floorIndex).second;
	appendObjectToArray(new CW3_SimpleEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 100, 20, 30, 2, 25));
	floors.erase(floors.begin() + floorIndex);

	return 0;
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void CW3_Game::virtDrawStringsOnTop()
{
	// Build the string to print
	char buf[128];
	sprintf(buf, "Score %d", getObjectOfType<CW3_Player>()->getScore());
	drawForegroundString(1000, 40, buf, clrText, NULL);
}


void CW3_Game::deleteObjectFromArray(int objectID) {

#if showDebugPrintObjectCreationDeletion == 1
	std::cout << "\nAttempting to delete object with ID: " << objectID << "\n";
#endif
	int i = 0;
	using Iter = std::vector<DisplayableObject*>::const_iterator;
	for (Iter it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++) {
#if showDebugPrintObjectCreationDeletion == 1
		std::cout << "Objects in array index: " << i << " is at memory: " << m_vecDisplayableObjects.at(i) << " and has an ID of: "<< dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() << "\n";
#endif
		if (dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() == objectID) {
#if showDebugPrintObjectCreationDeletion == 1
			std::cout << "Found the object we want to delete at index " << i << "!\n";
#endif
			drawableObjectsChanged();
			m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + i); 
			break;
		}
			
		i++;
	}

}