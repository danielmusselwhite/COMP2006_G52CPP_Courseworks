#include "header.h"
#include "CW3_Game.h"
#include "CW3_TileManager.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_Player.h"
#include "CW3_SimpleEnemy.h"
#include <fstream>
#include <sstream>

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

// start with initial state
CW3_Game::CW3_Game() : m_state(stateInit) {
	
}

CW3_Game::~CW3_Game() {

}

void CW3_Game::virtSetupBackgroundBuffer() {

	switch (m_state) {
	case stateInit:
		fillBackground(0x000000);

		//SETTING UP THE TILE MANAGER
		{
			int dungeonTileMapDesign[tmCountYTiles][tmCountXTiles] = {
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
		}

		// SETTING UP BACKGROUND TEXT
		{
			drawBackgroundString(15, 40, "C++ Coursework - Daniel Musselwhite", 0xe3e3e3, NULL);
		}

		break;


	case stateMain:
		
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

		m_tm->drawAllTiles(this, getBackgroundSurface());

		break;

	case statePaused:

		m_tm->drawAllTiles(this, getBackgroundSurface());

		break;

	case stateGameOver:
		fillBackground(0x000000);
		break;

	case stateHighscores:
		fillBackground(0x000000);
		drawBackgroundRectangle(getWindowWidth()/10, getWindowHeight()/25, getWindowWidth() - getWindowWidth()/10 , getWindowHeight()- getWindowHeight() / 25, 0x2a2a2a);
		break;
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

	switch (m_state){

	case stateInit:
		switch (iKeyCode) {

		case SDLK_ESCAPE: // End program when escape is pressed
			setExitWithCode(0);
			break;

		case SDLK_h:
			// view the highscores
			m_state = stateHighscores;

			// Force redraw of background
			lockAndSetupBackground();

			// Redraw the whole screen now
			redrawDisplay();

			break;

		default: // start the game
			m_state = stateMain;
			
			pause();

			// Ensure objects become visible now - we hid them initially
			setAllObjectsVisible(true);

			// Force redraw of background
			lockAndSetupBackground();
			
			// Redraw the whole screen now
			redrawDisplay();

			unpause();
			
			break;
		}

		
		break;




		// move the players controls into here
	case stateMain:

		switch (iKeyCode) {

		case SDLK_ESCAPE: // End program when escape is pressed
			setExitWithCode(0);
			break;

		case SDLK_p: // pause the program when this is pressed
			m_state = statePaused;
			//pause all game objects
			pauseAllGameObjects();
			pause();

			redrawDisplay();
			break;
		}
		break;




	case statePaused:
		switch (iKeyCode) {
		case SDLK_p:

			m_state = stateMain;
			//unpause all game objects
			unpauseAllGameObjects();
			unpause();

			redrawDisplay();
			break;

			// set up logic for saving here
		case SDLK_s:
			break;
		}
		break;
	



	case stateGameOver:
		switch (iKeyCode) {

		case SDLK_ESCAPE: // End program when escape is pressed
			setExitWithCode(0);
			break;

		case SDLK_RETURN: // start the game
			m_state = stateInit;
			
			deleteAllObjectsInArray();
			virtInitialiseObjects();

			lockAndSetupBackground();

			redrawDisplay();
			break;
		}
		break;




	case stateHighscores:
		switch (iKeyCode) {
		case SDLK_ESCAPE:// End program when escape is pressed
			setExitWithCode(0);
			break;

		default: //return to start menu
			m_state = stateInit;

			lockAndSetupBackground();

			redrawDisplay();
			break;
		}
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

	// Make everything invisible to start with
	setAllObjectsVisible(false);

	return 0;
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void CW3_Game::virtDrawStringsOnTop()
{
	char buf[128];

	switch (m_state) {
	case stateInit:
		drawForegroundString(15, getWindowHeight()/2, "Press h to view highscores!", 0xe3e3e3, NULL);
		drawForegroundString(15, getWindowHeight() / 2+30, "Press escp to exit!", 0xe3e3e3, NULL);
		drawForegroundString(15, getWindowHeight() / 2+60, "Press any other button to start!", 0xe3e3e3, NULL);
		break;
	case stateMain:
		// Build the string to print
		sprintf(buf, "Score %d", getObjectOfType<CW3_Player>()->getScore());
		drawForegroundString(1000, 40, buf, 0xe3e3e3, NULL);
		break;
	case statePaused: 
		// Build the string to print
		sprintf(buf, "Score %d", getObjectOfType<CW3_Player>()->getScore());
		drawForegroundString(1000, 40, buf, 0xe3e3e3, NULL);

		drawForegroundRectangle(400, getWindowHeight()/2-5, 900, getWindowHeight()/2+35, 0x262626);

		drawForegroundString(407, getWindowHeight() / 2, "Press p to unpause or s to save!", 0xe3e3e3, NULL);
		break;
	case stateGameOver:

		drawForegroundString(15, 40, "GameOver!", 0xe3e3e3, NULL);

		sprintf(buf, "You got a score of %d", getObjectOfType<CW3_Player>()->getScore());
		drawForegroundString(15, 100, buf, 0xe3e3e3, NULL);

		drawForegroundString(15, getWindowHeight() / 2, "Press escape to quit or enter to play again!", 0xe3e3e3, NULL);
		break;

	case stateHighscores:

		drawForegroundString(500, 40, "Highscores", 0xe3e3e3, NULL);

		// look at the input file (highscores)
		std::ifstream infile("./savedData/highscores.csv");

		//if the file exists..
		if (infile.good()) {

			int i=0; //number of rows in csv
			int j; //number of fields in csv
			std::string input;

			// get each line in the csv
			while (std::getline(infile, input)){

				// create a vector of the different fields for this row by separating the commas
				std::vector<std::string> fields;
				std::stringstream inputStream(input);
				std::string field;
				while (std::getline(inputStream, field, ',')) {
					fields.push_back(field);
				}

				// write this row
				sprintf(buf, "Place: %i Name: %s - Score: %s", i, fields.at(0).c_str(), fields.at(1).c_str());
				drawForegroundString(350, 90 + i * 30, buf, 0xe3e3e3, NULL);

				i++;
			}


			if(i==0)
				drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
		}
		else {
			drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
		}
		

		break;
	}

	
	
}

void CW3_Game::virtMainLoopDoBeforeUpdate()
{
	pause();
	sortObjectsByYAxis();
	unpause();
}

void CW3_Game::pauseAllGameObjects()
{
	std::vector<CW3_GameObject*> gameObjects = getObjectsOfType<CW3_GameObject>();

	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects.at(i)->setPausedValueTo(true);
}

void CW3_Game::unpauseAllGameObjects()
{
	std::vector<CW3_GameObject*> gameObjects = getObjectsOfType<CW3_GameObject>();

	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects.at(i)->setPausedValueTo(false);
	
}


void CW3_Game::deleteObjectFromArray(int objectID) {

	
#if showDebugPrintObjectCreationDeletion is 1
	std::cout << "\nAttempting to delete object with ID: " << objectID << "Object array size is: "<< m_vecDisplayableObjects.size() << "\n";
#endif
	int i = 0;
	using Iter = std::vector<DisplayableObject*>::const_iterator;
	for (Iter it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++) {
#if showDebugPrintObjectCreationDeletion is 1
		std::cout << "Objects in array index: " << i << " is at memory: " << m_vecDisplayableObjects.at(i) << " and has an ID of: "<< dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() << "\n";
#endif
		if (dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() == objectID) {
#if showDebugPrintObjectCreationDeletion is 1
			std::cout << "Found the object we want to delete at index " << i << "!\n";
#endif
			drawableObjectsChanged();
			m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + i); 
			break;
		}
			
		i++;
	}

}

void CW3_Game::deleteAllObjectsInArray() {


#if showDebugPrintObjectCreationDeletion is 1
	std::cout << "\nAttempting to delete all Objects in array; initial size is: " << m_vecDisplayableObjects.size() << "\n";
#endif
	int i = 0;
	using Iter = std::vector<DisplayableObject*>::const_iterator;

	while (m_vecDisplayableObjects.size() != 0) {
		drawableObjectsChanged();
		m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin());
	}
		

#if showDebugPrintObjectCreationDeletion is 1
	std::cout << "\nObject should now be 0, this is: " << (m_vecDisplayableObjects.size() == 0 ? "true" : "false") << "\n";
#endif
}