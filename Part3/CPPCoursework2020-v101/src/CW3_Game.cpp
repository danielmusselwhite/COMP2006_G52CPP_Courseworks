#include "header.h"
#include "CW3_Game.h"
#include "CW3_TileManager.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_Player.h"
#include "CW3_SimpleEnemy.h"
#include "CW3_SimpleBullet.h"
#include "CW3_StateEnemy.h"
#include "CW3_SimpleGun.h"
#include "CW3_ShotGun.h"
#include "CW3_ShotGunBullet.h"
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

void CW3_Game::transitionToState(GameState *state) {

	if (m_gameState != nullptr)
		delete m_gameState;
	//if (m_currentLevel != nullptr && m_currentLevel!=state && m_gameState != m_currentLevel) {
	//	delete m_currentLevel;
	//	m_currentLevel = nullptr;
	//}
	m_gameState = state;

	lockAndSetupBackground();
	redrawDisplay();
}

void CW3_Game::setCurrentLevel(LevelState* level)
{
	if (m_currentLevel != nullptr) {
		delete m_currentLevel;
		m_currentLevel = nullptr;
	}

	m_currentLevel = level;
}

void CW3_Game::switchToPauseState() {
	StatePaused* pausedState = new StatePaused(this);

	m_gameState = pausedState;
}

void CW3_Game::switchFromPauseState() {
	if (m_gameState != nullptr)
		delete m_gameState;

	m_gameState = m_currentLevel;
}






CW3_Game::CW3_Game() {
	m_currentLevel = nullptr;
	m_gameState = (new StateInit(this));
}

CW3_Game::~CW3_Game() {
	if (m_gameState != nullptr)
		delete m_gameState;
	ImageManager::destroyImageManager();
}


void CW3_Game::virtSetupBackgroundBuffer()
{
	m_gameState->setUpBackground();
}

void CW3_Game::virtMouseDown(int iButton, int iX, int iY) {
	if (m_gameState == m_currentLevel)
		m_currentLevel->mouseDown(iButton);
}

void CW3_Game::deleteObjectFromArray(int objectID) {
#if showDebugPrintObjectCreationDeletion is 1
	std::cout << "\nAttempting to delete object with ID: " << objectID << "Object array size is: " << m_vecDisplayableObjects.size() << "\n";
#endif
	int i = 0;
	using Iter = std::vector<DisplayableObject*>::const_iterator;
	for (Iter it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++) {
#if showDebugPrintObjectCreationDeletion is 1
		std::cout << "Objects in array index: " << i << " is at memory: " << m_vecDisplayableObjects.at(i) << " and has an ID of: " << dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() << "\n";
#endif
		if (dynamic_cast<CW3_GameObject *>(m_vecDisplayableObjects.at(i))->getObjectID() == objectID) {
#if showDebugPrintObjectCreationDeletion is 1
			std::cout << "Found the object we want to delete at index " << i << "!\n";
#endif

			drawableObjectsChanged();
			delete (m_vecDisplayableObjects.at(i));
			m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + i);

			//drawableObjectsChanged();
			//m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + i); 
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
		delete m_vecDisplayableObjects.at(0);
		m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin());
	}


#if showDebugPrintObjectCreationDeletion is 1
	std::cout << "\nObject should now be 0, this is: " << (m_vecDisplayableObjects.size() == 0 ? "true" : "false") << "\n";
#endif
}
void CW3_Game::virtKeyDown(int iKeyCode) {
	m_gameState->handleKeyPresses(iKeyCode);
}
int CW3_Game::virtInitialiseObjects() {

	m_gameState->initialiseObjects();
	return 0;

}

void CW3_Game::virtDrawStringsOnTop() {
	try {
		m_gameState->drawStringsOnTop();
	}
	catch (int e)
	{
		std::cout << "An exception occurred. Exception number:" << e << '\n';
	}
}

void CW3_Game::virtMainLoopDoBeforeUpdate() {
	m_gameState->DoBeforeUpdate();
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




// STATEINIT
StateInit::StateInit(CW3_Game *pGameEngine) {
	setContext(pGameEngine);

	m_stateID = 0;

	std::vector<std::pair<SimpleImage, int>> coinAnim;
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f0.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f1.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f2.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f3.png", true), 50));
	m_bgAnim = new CW3_AnimatedImage(coinAnim);
}

StateInit::~StateInit() {
	delete m_bgAnim;
}

void StateInit::setUpBackground() {
	m_pGameEngine->fillBackground(0x000000);
	m_pGameEngine->drawBackgroundString(15, 40, "C++ Coursework - Daniel Musselwhite", 0xe3e3e3, NULL);
}

void StateInit::handleKeyPresses(int iKeyCode) {
	switch (iKeyCode) {

	case SDLK_ESCAPE: // End program when escape is pressed
		m_pGameEngine->setExitWithCode(0);
		break;

	case SDLK_h:
		// view the highscores
		m_pGameEngine->transitionToState(new StateHighscores(m_pGameEngine));
		return;

	case SDLK_l:

	{
		// look at the input file (quicksave)
		std::ifstream infile("./savedData/quicksave.csv");

		//if the file exists..
		if (infile.good()) {
			std::vector<std::string> rows;

			std::string input;
			std::getline(infile, input);
			std::vector<std::string> fields;
			std::stringstream inputStream(input);
			std::string field;
			while (std::getline(inputStream, field, ',')) {
				fields.push_back(field);
			}

			infile.close();
			std::remove("./savedData/quicksave.csv");

			if (fields.at(0) == "level") {
				if (fields.at(1) == "0") {
					//StateLevel0* level = new StateLevel0(&infile, m_pGameEngine);
					//m_pGameEngine->setCurrentLevel(level);
					//m_pGameEngine->transitionToState(level);
					return;
				}

				else if (fields.at(1) == "1") {
					StateLevel1* level = new StateLevel1(&infile, m_pGameEngine);
					m_pGameEngine->setCurrentLevel(level);
					m_pGameEngine->transitionToState(level);
					return;
				}
			}
		}


	}
	break;

	case SDLK_RETURN: // start the game
		//StateLevel0* level = new StateLevel0(m_pGameEngine);
		StateLevel1* level = new StateLevel1(m_pGameEngine);
		m_pGameEngine->setCurrentLevel(level);
		m_pGameEngine->transitionToState(level);
		return;
	}
}

void StateInit::drawStringsOnTop() {
	m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2, "Press h to view highscores!", 0xe3e3e3, NULL);
	m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2 + 30, "Press escp to exit!", 0xe3e3e3, NULL);

	{
		// look at the input file (quicksave)
		std::ifstream infile("./savedData/quicksave.csv");
		//if the file exists..
		if (infile.good()) {
			m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2 + 60, "Press enter to start new game! (This will delete your quicksave)", 0xe3e3e3, NULL);
			m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2 + 90, "Press l to load game your quicksave game! (This will delete your quicksave)", 0xe3e3e3, NULL);
		}
		else {
			m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2 + 60, "Press enter to start new game!", 0xe3e3e3, NULL);
		}

		infile.close();
	}
}

void StateInit::DoBeforeUpdate() {
	m_pGameEngine->unpause();
	m_pGameEngine->lockBackgroundForDrawing();
	m_pGameEngine->virtSetupBackgroundBuffer();
	m_bgAnim->renderCurrentFrame(m_pGameEngine, m_pGameEngine->getBackgroundSurface(), 10, 10, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
	m_bgAnim->renderCurrentFrame(m_pGameEngine, m_pGameEngine->getBackgroundSurface(), 10, m_pGameEngine->getWindowHeight() - 20, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
	m_bgAnim->renderCurrentFrame(m_pGameEngine, m_pGameEngine->getBackgroundSurface(), m_pGameEngine->getWindowWidth() - 20, 10, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
	m_bgAnim->renderCurrentFrame(m_pGameEngine, m_pGameEngine->getBackgroundSurface(), m_pGameEngine->getWindowWidth() - 20, m_pGameEngine->getWindowHeight() - 20, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
	m_pGameEngine->unlockBackgroundForDrawing();
	m_pGameEngine->redrawDisplay();
	m_pGameEngine->pause();
}




// STATELEVEL
void LevelState::mouseDown(int iButton) {
	try {
		CW3_Player* player = m_pGameEngine->getObjectOfType<CW3_Player>();
		if (iButton == SDL_BUTTON_LEFT) {
			player->shootGun();
		}
	}

	catch (int e) {
		std::cout << "\nPlayer could not be found";
	}
}













// STATELEVEL1

StateLevel1::StateLevel1(CW3_Game *pGameEngine) {
	setContext(pGameEngine);

	m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

	m_stateID = 2;

	m_minEnemySpawnTimeBetweenSpawns = 1000;
	m_maxEnemySpawnTimeBetweenSpawns = 7500;
	m_enemySpawnTimeBetweenSpawns = m_maxEnemySpawnTimeBetweenSpawns;
	m_enemySpawnNextEnemyTime = m_pGameEngine->getRawTime() + m_maxEnemySpawnTimeBetweenSpawns;

	//reset tilemap design
	m_dungeonTileMapDesign = {
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

	// base the tiles dimensions on the windows height and the number of tiles in the y plane
	m_tmTileDimensions = (m_pGameEngine->getWindowHeight()*.75) / tmCountYTiles;

	m_pGameEngine->pause();


	{

		//start drawing from the remaining space divided by 2, so it is centered
		m_tmStartingX = (m_pGameEngine->getWindowWidth() - m_tmTileDimensions * tmCountXTiles) / 2;
		m_tmStartingY = (m_pGameEngine->getWindowHeight() - m_tmTileDimensions * tmCountYTiles) / 2;

		std::cout << "Tile Dimensions: " << m_tmTileDimensions << " Window Height: " << m_pGameEngine->getWindowHeight() << "\n";

		m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

		// setting all tiles to tile map int 2D array
		for (int x = 0; x < tmCountXTiles; x++)
			for (int y = 0; y < tmCountYTiles; y++)
				m_tm->setMapValue(x, y, m_dungeonTileMapDesign.at(y).at(x));
		m_tm->setTopLeftPositionOnScreen(m_tmStartingX, m_tmStartingY);

	}

	// Force redraw of background
	m_pGameEngine->lockAndSetupBackground();

	//initialise objects for this state
	initialiseObjects();
	// Ensure objects become visible now - we hid them initially
	m_pGameEngine->setAllObjectsVisible(true);

	// Redraw the whole screen now
	m_pGameEngine->redrawDisplay();

	//player has started a new game so abandon their save game
	std::remove("./savedData/quicksave.csv");

	m_pGameEngine->unpause();
}



StateLevel1::StateLevel1(std::ifstream* loadGame, CW3_Game *pGameEngine) {
	setContext(pGameEngine);

	m_stateID = 2;

	m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

	m_pGameEngine->deleteAllObjectsInArray();

	m_minEnemySpawnTimeBetweenSpawns = 1000;
	m_maxEnemySpawnTimeBetweenSpawns = 7500;

	std::string input;

	// base the tiles dimensions on the windows height and the number of tiles in the y plane
	m_tmTileDimensions = (m_pGameEngine->getWindowHeight()*.75) / tmCountYTiles;

	m_dungeonTileMapDesign.clear(); // clearing the tilemaps design as we are loading a new one

	// get each line in the csv
	while (std::getline(*loadGame, input)) {

		// create a vector of the different fields for this row by separating the commas
		std::vector<std::string> fields;
		std::stringstream inputStream(input);
		std::string field;
		while (std::getline(inputStream, field, ',')) {
			fields.push_back(field);
		}

		if (fields.at(0) == "nextEnemySpawnTime")
			m_enemySpawnNextEnemyTime = m_pGameEngine->getRawTime() + std::stoi(fields.at(1));
		else if (fields.at(0) == "enemySpawnDelay")
			m_enemySpawnTimeBetweenSpawns = std::stoi(fields.at(1));

		else if (fields.at(0) == "tileManager") {
			std::vector<int> tileMapRow;
			for (int i = 1; i < fields.size(); i++) {
				tileMapRow.push_back(std::stoi(fields.at(i)));
			}
			m_dungeonTileMapDesign.push_back(tileMapRow);
		}

		else if (fields.at(0) == "player") {
			m_pGameEngine->drawableObjectsChanged();

			CW3_BaseGun * pGun;

			if ((fields.at(9)) == "simpleGun")
				pGun = new CW3_SimpleGun(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, 2, 2);
			else if ((fields.at(9)) == "shotGun")
				pGun = new CW3_ShotGun(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, 2, 2);
			else
				pGun = new CW3_SimpleGun(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, 2, 2);

			m_pGameEngine->appendObjectToArray(new CW3_Player(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8)), pGun));
		}
		else if (fields.at(0) == "simpleBullet") {
			m_pGameEngine->drawableObjectsChanged();
			m_pGameEngine->appendObjectToArray(new CW3_SimpleBullet(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, 10, 10, std::stod(fields.at((3)))));
		}
		else if (fields.at(0) == "shotGunBullet") {
			m_pGameEngine->drawableObjectsChanged();
			m_pGameEngine->appendObjectToArray(new CW3_ShotGunBullet(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, 10, 10, std::stod(fields.at((3)))));
		}
		else if (fields.at(0) == "simpleEnemy") {
			m_pGameEngine->drawableObjectsChanged();
			m_pGameEngine->appendObjectToArray(new CW3_SimpleEnemy(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8))));
		}
		else if (fields.at(0) == "stateEnemy") {
			m_pGameEngine->drawableObjectsChanged();
			m_pGameEngine->appendObjectToArray(new CW3_StateEnemy(std::stoi(fields.at(1)), std::stoi(fields.at(2)), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8)), std::stoi(fields.at(9))));
		}
	}

	m_pGameEngine->pause();

	// Ensure objects become visible now - we hid them initially
	m_pGameEngine->setAllObjectsVisible(true);

	// Force redraw of background
	m_pGameEngine->lockAndSetupBackground();

	// Redraw the whole screen now
	m_pGameEngine->redrawDisplay();

	m_pGameEngine->unpause();

	loadGame->close();

	//player can only load from the same file once
	std::remove("./savedData/quicksave.csv");
}

StateLevel1::~StateLevel1() {
	m_pGameEngine->deleteAllObjectsInArray();
	delete m_tm;
}

void StateLevel1::setUpBackground() {
	m_pGameEngine->fillBackground(clrBgMain);

	// SETTING UP THE STARRY BACKGROUND
	{
		int starSize = 0; // stars can be different sizes

		//for each x coordinate..
		for (int iX = 0; iX < m_pGameEngine->getWindowWidth(); iX += starSizeGap) {

			//.. for each y coordinate..
			for (int iY = 0; iY < m_pGameEngine->getWindowHeight(); iY += starSizeGap) {

				starSize = (rand() % starSizeRange) + starSizeMin; // get random star size

				//.. generate a random number and modulo it with for example, 100..
				switch (rand() % starChanceDenominator)
				{
					//.. if it results in a 0, 1, 2, or 3, draw a spot with the specified colour; if not don't draw a spot. (1/100 chance of a specific coloured spot, 1/25 chance of their being a spot)
				case 0: m_pGameEngine->drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarWhite); break;
				case 1: m_pGameEngine->drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarRed); break;
				case 2: m_pGameEngine->drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarBlue); break;
				case 3: m_pGameEngine->drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarYellow); break;

				}
			}
		}
	}

	//SETTING UP THE TILE MANAGER
	{

		//start drawing from the remaining space divided by 2, so it is centered
		m_tmStartingX = (m_pGameEngine->getWindowWidth() - m_tmTileDimensions * tmCountXTiles) / 2;
		m_tmStartingY = (m_pGameEngine->getWindowHeight() - m_tmTileDimensions * tmCountYTiles) / 2;

		std::cout << "Tile Dimensions: " << m_tmTileDimensions << " Window Height: " << m_pGameEngine->getWindowHeight() << "\n";

		m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

		// setting all tiles to tile map int 2D array
		for (int x = 0; x < tmCountXTiles; x++)
			for (int y = 0; y < tmCountYTiles; y++)
				m_tm->setMapValue(x, y, m_dungeonTileMapDesign.at(y).at(x));
		m_tm->setTopLeftPositionOnScreen(m_tmStartingX, m_tmStartingY);

		m_tm->drawAllTiles(m_pGameEngine, m_pGameEngine->getBackgroundSurface());
	}
}

void StateLevel1::initialiseObjects()
{
	std::vector<std::pair<int, int>> floors;

	//  getting all floor tiles (that the player could spawn on)
	for (int x = 0; x < tmCountXTiles; x++)
		for (int y = 0; y < tmCountYTiles; y++)
			if (m_tm->getMapValue(x, y) >= 0 && m_tm->getMapValue(x, y) < 50)
				floors.push_back((std::make_pair(x, y)));



	// spawn player at random floor
	int floorIndex = rand() % floors.size();
	std::pair<int, int> floor = floors.at(floorIndex);

	m_pGameEngine->drawableObjectsChanged();
	//m_pPlayer = new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, m_vecDisplayableObjects.size(), 100, 1, 3, 7);
	m_pGameEngine->appendObjectToArray(new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, 100, 100, 2, 4, 10, 0, new CW3_SimpleGun(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, 2, 2)));

	//erase this floor so we can't have more than one thing spawn on same floor
	floors.erase(floors.begin() + floorIndex);

	/*
			floorIndex = rand() % floors.size();
			floor = floors.at(floorIndex);

			drawableObjectsChanged();
			appendObjectToArray(new CW3_StateEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 100, 100, 1, 10, 2, 10,0));*/
			// Make everything invisible to start with
	m_pGameEngine->setAllObjectsVisible(false);
}

void StateLevel1::handleKeyPresses(int iKeyCode)
{
	switch (iKeyCode) {
	case SDLK_ESCAPE: // End program when escape is pressed
		m_pGameEngine->setExitWithCode(0);
		break;

	case SDLK_p: // pause the program when this is pressed
		m_pGameEngine->switchToPauseState();
		//pause all game objects
		m_pGameEngine->pauseAllGameObjects();
		m_pGameEngine->pause();
		m_pGameEngine->redrawDisplay();
		break;
	}
}

void StateLevel1::drawStringsOnTop()
{
	char buf[128];
	// Build the string to print
	sprintf(buf, "Score %d", m_pGameEngine->getObjectOfType<CW3_Player>()->getScore());
	m_pGameEngine->drawForegroundString(1000, 40, buf, 0xe3e3e3, NULL);

	m_pGameEngine->drawForegroundString(10, 40, "Level 1", 0xe3e3e3, NULL);
}

void StateLevel1::DoBeforeUpdate() {
	if (m_pGameEngine->getObjectOfType<CW3_Player>()->isDead()) {
		int playerScore = m_pGameEngine->getObjectOfType<CW3_Player>()->getScore();
		m_pGameEngine->setCurrentLevel(nullptr);
		m_pGameEngine->transitionToState(new StateGameOver(playerScore, m_pGameEngine));
		return;
	}

	if (!m_pGameEngine->isPaused() && m_pGameEngine->getRawTime() > m_enemySpawnNextEnemyTime) {
		std::vector<std::pair<int, int>> floors;

		//  getting all floor tiles (that the enemy could spawn on)
		for (int x = 0; x < tmCountXTiles; x++)
			for (int y = 0; y < tmCountYTiles; y++)
				if (m_tm->getMapValue(x, y) >= 0 && m_tm->getMapValue(x, y) < 50)
					floors.push_back((std::make_pair(x, y)));

		// spawn enemy at random floor
		int floorIndex = rand() % floors.size();
		std::pair<int, int> floor = floors.at(floorIndex);
		floor.first = floors.at(floorIndex).first;
		floor.second = floors.at(floorIndex).second;
		m_pGameEngine->drawableObjectsChanged();

		int simpleEnemyMaxHealth = 25 + (std::rand() % (100 - 25 + 1));
		int simpleEnemySpeed = 1 + (std::rand() % (3 - 1 + 1));

		int enemyType = rand() % 2;
		if (enemyType == 0)
			m_pGameEngine->appendObjectToArray(new CW3_SimpleEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, simpleEnemyMaxHealth, simpleEnemyMaxHealth, 10, 25, simpleEnemySpeed, 10));
		else if (enemyType == 1)
			m_pGameEngine->appendObjectToArray(new CW3_StateEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), m_pGameEngine, m_tmTileDimensions, m_tmTileDimensions, simpleEnemyMaxHealth, simpleEnemyMaxHealth, 10, 25, simpleEnemySpeed, 10, 0));
		m_enemySpawnNextEnemyTime = m_pGameEngine->getRawTime() + m_enemySpawnTimeBetweenSpawns;

		if (m_enemySpawnTimeBetweenSpawns * 0.9 >= m_minEnemySpawnTimeBetweenSpawns)
			m_enemySpawnTimeBetweenSpawns *= 0.9;
		else
			m_enemySpawnTimeBetweenSpawns = m_minEnemySpawnTimeBetweenSpawns;

	}
}






// STATEPAUSED

void StatePaused::handleKeyPresses(int iKeyCode)
{
	switch (iKeyCode) {
	case SDLK_ESCAPE: // End program when escape is pressed
		m_pGameEngine->setExitWithCode(0);
		break;

	case SDLK_p:

		//unpause all game objects
		m_pGameEngine->unpauseAllGameObjects();
		m_pGameEngine->unpause();

		m_pGameEngine->getCurrentLevel()->incrementNextEnemySpawnTime(m_pGameEngine->getRawTime()); // adding the time back onto the difference between when to spawn the enemy

		m_pGameEngine->redrawDisplay();
		m_pGameEngine->switchFromPauseState();
		return;

		// set up logic for saving here
	case SDLK_s:

		//file for saving to
		std::ofstream outfile("./savedData/quicksave.csv");

		if (m_pGameEngine->getCurrentLevel() != nullptr) {
			outfile << "level," << m_pGameEngine->getCurrentLevel()->getLevelID() << "\n";
		}

		//saving enemy spawn time variables
		outfile << "nextEnemySpawnTime," << m_pGameEngine->getCurrentLevel()->getEnemySpawnNextEnemyTime() << "\n"; // time until next enemy spawns - the current time
		outfile << "enemySpawnDelay," << m_pGameEngine->getCurrentLevel()->getEnemySpawnTimeBetweenSpawns() << "\n";

		//saving game world
		for (int y = 0; y < tmCountYTiles; y++) {
			outfile << "tileManager,";
			for (int x = 0; x < tmCountXTiles; x++) {
				outfile << m_pGameEngine->getTileManager()->getMapValue(x, y);
				if (x < tmCountXTiles - 1)
					outfile << ",";
			}
			outfile << "\n";
		}



		//saving game objects
		// for each object in the game
		for (int i = 0; i < m_pGameEngine->get_m_vecDisplayableObjects()->size(); i++) {
			// cast to a CW3_GameObject then get its state
			std::vector<std::string> objectState = ((CW3_GameObject *)m_pGameEngine->get_m_vecDisplayableObjects()->at(i))->getState();

			std::string stateString;

			// iterate through the object state vector converting it to csv format
			for (int i = 0; i < objectState.size(); i++) {
				stateString.append(objectState.at(i));
				if (i != objectState.size() - 1)
					stateString.push_back(',');
			}
			// write to the game save file
			outfile << stateString << "\n";
		}

		outfile.close();

		//saved game now returning to menu
		m_pGameEngine->deleteAllObjectsInArray();
		m_pGameEngine->setCurrentLevel(nullptr);
		m_pGameEngine->transitionToState(new StateInit(m_pGameEngine));
		return;
	}
}

void StatePaused::drawStringsOnTop()
{
	char buf[128];

	// Build the string to print
	sprintf(buf, "Score %d", m_pGameEngine->getObjectOfType<CW3_Player>()->getScore());
	m_pGameEngine->drawForegroundString(1000, 40, buf, 0xe3e3e3, NULL);

	m_pGameEngine->drawForegroundRectangle(400, m_pGameEngine->getWindowHeight() / 2 - 5, 900, m_pGameEngine->getWindowHeight() / 2 + 35, 0x262626);

	m_pGameEngine->drawForegroundString(407, m_pGameEngine->getWindowHeight() / 2, "Press p to unpause or s to save!", 0xe3e3e3, NULL);
}






// STATEGAMEOVER

void StateGameOver::setUpBackground()
{
	m_pGameEngine->fillBackground(0x000000);
}

void StateGameOver::handleKeyPresses(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_RETURN: // start the game

		int m_playersHighscorePlace;

		// look at the input file (highscores)
		std::ifstream infile("./savedData/highscores.csv");

		//if the file exists..
		if (infile.good()) {

			std::string input;

			int i = 0; // row counter

			// get each line in the csv (max 10 lines)
			while (std::getline(infile, input) && i < 10) {

				// create a vector of the different fields for this row by separating the commas
				std::vector<std::string> fields;
				std::stringstream inputStream(input);
				std::string field;
				while (std::getline(inputStream, field, ',')) {
					fields.push_back(field);
				}

				//if the players highscore is better than this row store this index and break the loop
				if (m_highScore > std::stoi(fields.at(1))) {
					m_playersHighscorePlace = i;
					break;
				}

				i++;
			}

			infile.close();

			//player has a highscore as there aren't 10 rows yet
			if (i < 10) {
				m_playersHighscorePlace = i;
				m_pGameEngine->transitionToState(new StateNewHighscores(m_playersHighscorePlace, m_pGameEngine));
				return;
			}

			//player hasn't got a highscore as i reached greater than 9 hence we have 10 rows that the player isn't higher than
			else {
				m_pGameEngine->deleteAllObjectsInArray();
				m_pGameEngine->transitionToState(new StateInit(m_pGameEngine));
				return;
			}
		}
		//player has a highscore as there isn't a highscore file yet
		else {
			m_playersHighscorePlace = 0;
			m_pGameEngine->transitionToState(new StateNewHighscores(m_playersHighscorePlace, m_pGameEngine));
			return;
		}

		break;
	}
}

void StateGameOver::drawStringsOnTop()
{
	char buf[128];

	m_pGameEngine->drawForegroundString(15, 40, "GameOver!", 0xe3e3e3, NULL);

	sprintf(buf, "You got a score of %d", m_pGameEngine->getObjectOfType<CW3_Player>()->getScore());
	m_pGameEngine->drawForegroundString(15, 100, buf, 0xe3e3e3, NULL);

	m_pGameEngine->drawForegroundString(15, m_pGameEngine->getWindowHeight() / 2, "Press enter to play again!", 0xe3e3e3, NULL);
}






// STATEHIGHSCORES

void StateHighscores::setUpBackground()
{
	m_pGameEngine->fillBackground(0x000000);
	m_pGameEngine->drawBackgroundRectangle(m_pGameEngine->getWindowWidth() / 10, m_pGameEngine->getWindowHeight() / 25, m_pGameEngine->getWindowWidth() - m_pGameEngine->getWindowWidth() / 10, m_pGameEngine->getWindowHeight() - m_pGameEngine->getWindowHeight() / 25, 0x2a2a2a);


	m_pGameEngine->drawBackgroundString(550, 40, "Highscores", 0xe3e3e3, NULL);

	m_pGameEngine->drawBackgroundString(300, 500, "Press any key to return to menu", 0xe3e3e3, NULL);

}

void StateHighscores::handleKeyPresses(int iKeyCode)
{
	switch (iKeyCode) {

	default: //return to start menu
		m_pGameEngine->transitionToState(new StateInit(m_pGameEngine));
		return;
		break;
	}
}

void StateHighscores::drawStringsOnTop()
{
	{
		char buf[128];

		// look at the input file (highscores)
		std::ifstream infile("./savedData/highscores.csv");

		//if the file exists..
		if (infile.good()) {

			int i = 0; //number of rows in csv
			int j; //number of fields in csv
			std::string input;

			// get each line in the csv (max 10 lines)
			while (std::getline(infile, input) && i < 10) {

				// create a vector of the different fields for this row by separating the commas
				std::vector<std::string> fields;
				std::stringstream inputStream(input);
				std::string field;
				while (std::getline(inputStream, field, ',')) {
					fields.push_back(field);
				}

				// write this row
				sprintf(buf, "Place %i: %s - %s", i + 1, fields.at(0).c_str(), fields.at(1).c_str());
				m_pGameEngine->drawForegroundString(350, 90 + i * 30, buf, 0xe3e3e3, NULL);

				i++;
			}


			if (i == 0)
				m_pGameEngine->drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
		}
		else {
			m_pGameEngine->drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
		}

		infile.close();
	}
}




// STATENEWHIGHSCORES

void StateNewHighscores::setUpBackground()
{
	m_pGameEngine->fillBackground(0x000000);

	m_pGameEngine->drawBackgroundString(15, 40, "You have achieved a new highscore!", 0xe3e3e3, NULL);

	m_pGameEngine->drawBackgroundString(15, 500, "Input your name (a-z) then press enter to save your highscore!", 0xe3e3e3, NULL);
}

void StateNewHighscores::handleKeyPresses(int iKeyCode)
{
	//allowing user to enter their name
	switch (iKeyCode) {
	case SDLK_a:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'a';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_b:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'b';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_c:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'c';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_d:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'd';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_e:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'e';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_f:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'f';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_g:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'g';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_h:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'h';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_i:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'i';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_j:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'j';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_k:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'k';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_l:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'l';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_m:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'm';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_n:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'n';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_o:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'o';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_p:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'p';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_q:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'q';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_r:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'r';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_s:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 's';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_t:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 't';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_u:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'u';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_v:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'v';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_w:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'w';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_x:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'x';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_y:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'y';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;

	case SDLK_z:
		m_pGameEngine->lockForegroundForDrawing();
		m_playerName += 'z';
		m_pGameEngine->unlockForegroundForDrawing();

		m_pGameEngine->redrawDisplay();
		break;




	case SDLK_BACKSPACE: // removing the last character

		if (m_playerName.size() > 0) {
			m_pGameEngine->lockForegroundForDrawing();
			m_playerName.pop_back();
			m_pGameEngine->unlockForegroundForDrawing();

			m_pGameEngine->redrawDisplay();
		}

		break;



	case SDLK_RETURN:

		if (m_playerName.size() > 0) {

			// writing the users highscore to a file
			{
				char buf[128];

				// look at the input file (highscores)
				std::ifstream infile("./savedData/highscores.csv");

				std::vector<std::string> rows;

				//if the file exists..
				if (infile.good()) {

					int i = 0; //number of rows in csv
					int j; //number of fields in csv
					std::string input;

					// get each line in the csv (up to the place the player has beat)
					while (i < m_playersHighscorePlace && std::getline(infile, input)) {

						//add this row into the vector which will be used to overwrite the file
						rows.push_back(input.c_str());

						i++;
					}

					// now push the player in the middle
					rows.push_back(m_playerName + "," + std::to_string(m_pGameEngine->getObjectOfType<CW3_Player>()->getScore()));
					i++;

					// now push the ones after the player (up to a max of 10 total rows) after
					while (i < 10 && std::getline(infile, input)) {

						//add this row into the vector which will be used to overwrite the file
						rows.push_back(input);

						i++;
					}

				}
				else {
					rows.push_back(m_playerName + "," + std::to_string(m_pGameEngine->getObjectOfType<CW3_Player>()->getScore()));
				}

				infile.close();

				//writing rows to the highscore file
				std::ofstream outfile("./savedData/highscores.csv");
				for (int i = 0; i < rows.size(); i++)
					outfile << rows.at(i) << '\n';

				outfile.close();
			}

			m_pGameEngine->transitionToState(new StateInit(m_pGameEngine));
		}

		break;
	}
}

void StateNewHighscores::drawStringsOnTop()
{
	char buf[128];
	// write this row
	sprintf(buf, "Name: %s", m_playerName.c_str());
	m_pGameEngine->drawForegroundString(15, 100, buf, 0xe3e3e3, NULL);
}