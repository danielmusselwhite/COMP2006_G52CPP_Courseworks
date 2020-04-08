#include "header.h"
#include "CW3_Game.h"
#include "CW3_TileManager.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_Player.h"
#include "CW3_SimpleEnemy.h"
#include "CW3_SimpleBullet.h"
#include "CW3_StateEnemy.h"
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
	m_minEnemySpawnTimeBetweenSpawns = 3333;
	m_maxEnemySpawnTimeBetweenSpawns = 7500;
	//m_maxEnemySpawnTimeBetweenSpawns = 7500000;
	// setting up coin anim
	std::vector<std::pair<SimpleImage, int>> coinAnim;
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f0.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f1.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f2.png", true), 50));
	coinAnim.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Items\\Coins\\coin_anim_f3.png", true), 50));
	m_bgAnim = new CW3_AnimatedImage(coinAnim);
}

CW3_Game::~CW3_Game() {
	deleteAllObjectsInArray();
	delete m_bgAnim;
	ImageManager::destroyImageManager();
}

void CW3_Game::virtSetupBackgroundBuffer() {

	switch (m_state) {
	case stateInit:
		fillBackground(0x000000);

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

		//SETTING UP THE TILE MANAGER
		{

			//start drawing from the remaining space divided by 2, so it is centered
			m_tmStartingX = (getWindowWidth() - m_tmTileDimensions * tmCountXTiles) / 2;
			m_tmStartingY = (getWindowHeight() - m_tmTileDimensions * tmCountYTiles) / 2;

			std::cout << "Tile Dimensions: " << m_tmTileDimensions << " Window Height: " << getWindowHeight() << "\n";

			m_tm = new CW3_TileManager(m_tmTileDimensions, m_tmTileDimensions, tmCountXTiles, tmCountYTiles);

			// setting all tiles to tile map int 2D array
			for (int x = 0; x < tmCountXTiles; x++)
				for (int y = 0; y < tmCountYTiles; y++)
					m_tm->setMapValue(x, y, m_dungeonTileMapDesign.at(y).at(x));
			m_tm->setTopLeftPositionOnScreen(m_tmStartingX, m_tmStartingY);

			m_tm->drawAllTiles(this, getBackgroundSurface());
		}

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
		

		drawBackgroundString(550, 40, "Highscores", 0xe3e3e3, NULL);

		drawBackgroundString(300, 500, "Press any key to return to menu", 0xe3e3e3, NULL);


		break;

	case stateNewHighscore:
		
		fillBackground(0x000000);

		drawBackgroundString(15, 40, "You have achieved a new highscore!", 0xe3e3e3, NULL);

		drawBackgroundString(15, 500, "Input your name (a-z) then press enter to save your highscore!", 0xe3e3e3, NULL);

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

		case SDLK_l:

			{
				// look at the input file (quicksave)
				std::ifstream infile("./savedData/quicksave.csv");

				std::vector<std::string> rows;

				//if the file exists..
				if (infile.good()) {

					m_state = stateMain;

					deleteAllObjectsInArray();

					std::string input;

					// base the tiles dimensions on the windows height and the number of tiles in the y plane
					m_tmTileDimensions = (getWindowHeight()*.75) / tmCountYTiles;

					m_dungeonTileMapDesign.clear(); // clearing the tilemaps design as we are loading a new one

					// get each line in the csv
					while (std::getline(infile, input)) {

						// create a vector of the different fields for this row by separating the commas
						std::vector<std::string> fields;
						std::stringstream inputStream(input);
						std::string field;
						while (std::getline(inputStream, field, ',')) {
							fields.push_back(field);
						}
						
						if (fields.at(0) == "nextEnemySpawnTime")
							m_enemySpawnNextEnemyTime = getRawTime() + std::stoi(fields.at(1));
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
							drawableObjectsChanged();
							appendObjectToArray(new CW3_Player(std::stoi(fields.at(1)), std::stoi(fields.at(2)), this, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8))));
						}
						else if (fields.at(0) == "simpleEnemy") {
							drawableObjectsChanged();
							appendObjectToArray(new CW3_SimpleEnemy(std::stoi(fields.at(1)),std::stoi(fields.at(2)), this, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8))));
						}
						else if (fields.at(0) == "simpleBullet") {
							drawableObjectsChanged();
							appendObjectToArray(new CW3_SimpleBullet(std::stoi(fields.at(1)),std::stoi(fields.at(2)), this, 10, 10, std::stod(fields.at((3)))));
						}
						else if (fields.at(0) == "stateEnemy") {
							drawableObjectsChanged();
							appendObjectToArray(new CW3_StateEnemy(std::stoi(fields.at(1)), std::stoi(fields.at(2)), this, m_tmTileDimensions, m_tmTileDimensions, std::stoi(fields.at(3)), std::stoi(fields.at(4)), std::stoi(fields.at(5)), std::stoi(fields.at(6)), std::stoi(fields.at(7)), std::stoi(fields.at(8)), std::stoi(fields.at(9))));
						}

					}

					pause();

					// Ensure objects become visible now - we hid them initially
					setAllObjectsVisible(true);

					// Force redraw of background
					lockAndSetupBackground();

					// Redraw the whole screen now
					redrawDisplay();

					unpause();
					

				}

				infile.close();

				//player can only load from the same file once
				std::remove("./savedData/quicksave.csv");

			}
			break;

		case SDLK_RETURN: // start the game
			//reset tilenap design
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
			m_tmTileDimensions = (getWindowHeight()*.75) / tmCountYTiles;

			//reset enemy spawn times
			m_enemySpawnTimeBetweenSpawns = m_maxEnemySpawnTimeBetweenSpawns;
			m_enemySpawnNextEnemyTime = getRawTime() + m_enemySpawnTimeBetweenSpawns;
			
			m_state = stateMain;
			
			pause();

			
			// Force redraw of background
			lockAndSetupBackground();

			//initialise objects for this state
			virtInitialiseObjects();
			// Ensure objects become visible now - we hid them initially
			setAllObjectsVisible(true);
			
			// Redraw the whole screen now
			redrawDisplay();

			//player has started a new game so abandon their save game
			std::remove("./savedData/quicksave.csv");

			unpause();
			
			break;
		}

		
		break;




	case stateMain:

		switch (iKeyCode) {

		case SDLK_p: // pause the program when this is pressed
			m_state = statePaused;
			//pause all game objects
			pauseAllGameObjects();
			pause();

			m_enemySpawnNextEnemyTime -= getRawTime(); // we have paused it so subtract the current time from the time limit to get the difference then add the time onto that difference when unpaused

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

			m_enemySpawnNextEnemyTime += getRawTime(); // adding the time back onto the difference between when to spawn the enemy

			redrawDisplay();
			break;

			// set up logic for saving here
		case SDLK_s:

			//file for saving to
			std::ofstream outfile("./savedData/quicksave.csv");

			//saving enemy spawn time variables
			outfile << "nextEnemySpawnTime,"<<m_enemySpawnNextEnemyTime<<"\n"; // time until next enemy spawns - the current time
			outfile << "enemySpawnDelay," << m_enemySpawnTimeBetweenSpawns << "\n";

			//saving game world
			for (int y = 0; y < tmCountYTiles; y++) {
				outfile << "tileManager,";
				for (int x = 0; x < tmCountXTiles; x++) {
					outfile << m_tm->getMapValue(x, y);
					if (x < tmCountXTiles - 1)
						outfile << ",";
				}
				outfile << "\n";
			}
			
			

			//saving game objects
			// for each object in the game
			for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
				// cast to a CW3_GameObject then get its state
				std::vector<std::string> objectState = ((CW3_GameObject *)m_vecDisplayableObjects.at(i))->getState();
				
				std::string stateString;

				// iterate through the object state vector converting it to csv format
				for (int i = 0; i < objectState.size(); i++) {
					stateString.append(objectState.at(i));
					if(i != objectState.size()-1)
						stateString.push_back(',');
				}
				// write to the game save file
				outfile << stateString << "\n";
			}

			outfile.close();

			//saved game now returning to menu

			delete m_tm;

			m_state = stateInit;

			deleteAllObjectsInArray();

			lockAndSetupBackground();

			redrawDisplay();

			break;
		}
		break;
	



	case stateGameOver:
		switch (iKeyCode) {

		case SDLK_RETURN: // start the game

			delete m_tm;

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
					if (getObjectOfType<CW3_Player>()->getScore() > std::stoi(fields.at(1))) {
						m_playersHighscorePlace = i;
						break;
					}

					i++;
				}


				//player has a highscore as there aren't 10 rows yet
				if (i < 10) {
					m_playersHighscorePlace = i;
					m_state = stateNewHighscore;
				}
					
				//player hasn't got a highscore as i reached greater than 9 hence we have 10 rows that the player isn't higher than
				else {
					m_state = stateInit;

					deleteAllObjectsInArray();
				}
			}
			//player has a highscore as there isn't a highscore file yet
			else {
				m_playersHighscorePlace = 0;
				m_state = stateNewHighscore;
			}
				
		
			infile.close();

			

			lockAndSetupBackground();

			redrawDisplay();
			break;
		}
		break;




	case stateHighscores:
		switch (iKeyCode) {

		default: //return to start menu
			m_state = stateInit;

			lockAndSetupBackground();

			redrawDisplay();
			break;
		}
		break;



	case stateNewHighscore:

		

		//allowing user to enter their name
		switch (iKeyCode) {
		case SDLK_a:
			lockForegroundForDrawing();
			m_playerName += 'a';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_b:
			lockForegroundForDrawing();
			m_playerName += 'b';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_c:
			lockForegroundForDrawing();
			m_playerName += 'c';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_d:
			lockForegroundForDrawing();
			m_playerName += 'd';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_e:
			lockForegroundForDrawing();
			m_playerName += 'e';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_f:
			lockForegroundForDrawing();
			m_playerName += 'f';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_g:
			lockForegroundForDrawing();
			m_playerName += 'g';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_h:
			lockForegroundForDrawing();
			m_playerName += 'h';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_i:
			lockForegroundForDrawing();
			m_playerName += 'i';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_j:
			lockForegroundForDrawing();
			m_playerName += 'j';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_k:
			lockForegroundForDrawing();
			m_playerName += 'k';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_l:
			lockForegroundForDrawing();
			m_playerName += 'l';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_m:
			lockForegroundForDrawing();
			m_playerName += 'm';
			unlockForegroundForDrawing();
		
			redrawDisplay();
			break;

		case SDLK_n:
			lockForegroundForDrawing();
			m_playerName += 'n';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_o:
			lockForegroundForDrawing();
			m_playerName += 'o';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_p:
			lockForegroundForDrawing();
			m_playerName += 'p';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_q:
			lockForegroundForDrawing();
			m_playerName += 'q';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_r:
			lockForegroundForDrawing();
			m_playerName += 'r';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_s:
			lockForegroundForDrawing();
			m_playerName += 's';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_t:
			lockForegroundForDrawing();
			m_playerName += 't';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_u:
			lockForegroundForDrawing();
			m_playerName += 'u';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_v:
			lockForegroundForDrawing();
			m_playerName += 'v';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_w:
			lockForegroundForDrawing();
			m_playerName += 'w';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_x:
			lockForegroundForDrawing();
			m_playerName += 'x';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_y:
			lockForegroundForDrawing();
			m_playerName += 'y';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;

		case SDLK_z:
			lockForegroundForDrawing();
			m_playerName += 'z';
			unlockForegroundForDrawing();

			redrawDisplay();
			break;


		

		case SDLK_BACKSPACE: // removing the last character

			if (m_playerName.size() > 0) {
				lockForegroundForDrawing();
				m_playerName.pop_back();
				unlockForegroundForDrawing();

				redrawDisplay();
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
						rows.push_back(m_playerName + "," + std::to_string(getObjectOfType<CW3_Player>()->getScore()));
						i++;

						// now push the ones after the player (up to a max of 10 total rows) after
						while (i < 10 && std::getline(infile, input)) {

							//add this row into the vector which will be used to overwrite the file
							rows.push_back(input);

							i++;
						}

					}
					else {
						rows.push_back(m_playerName + "," + std::to_string(getObjectOfType<CW3_Player>()->getScore()));
					}

					infile.close();

					//writing rows to the highscore file
					std::ofstream outfile("./savedData/highscores.csv");
					for (int i = 0; i < rows.size(); i++)
						outfile << rows.at(i) << '\n';

					outfile.close();
				}

				m_playerName = "";
				m_playersHighscorePlace = 0;

				m_state = stateInit;

				deleteAllObjectsInArray();

				lockAndSetupBackground();

				redrawDisplay();
			}

			break;
		}

		

		break;
	}

	
}

int CW3_Game::virtInitialiseObjects() {

	switch (m_state) {
	case stateMain:
		std::vector<std::pair<int, int>> floors;

		//  getting all floor tiles (that the player could spawn on)
		for (int x = 0; x < tmCountXTiles; x++)
			for (int y = 0; y < tmCountYTiles; y++)
				if (m_tm->getMapValue(x, y) >= 0 && m_tm->getMapValue(x, y) < 50)
					floors.push_back((std::make_pair(x, y)));



		// spawn player at random floor
		int floorIndex = rand() % floors.size();
		std::pair<int, int> floor = floors.at(floorIndex);

		drawableObjectsChanged();
		//m_pPlayer = new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, m_vecDisplayableObjects.size(), 100, 1, 3, 7);
		appendObjectToArray(new CW3_Player(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 100, 100, 2, 4, 10, 0));

		//erase this floor so we can't have more than one thing spawn on same floor
		floors.erase(floors.begin() + floorIndex);

/*
		floorIndex = rand() % floors.size();
		floor = floors.at(floorIndex);

		drawableObjectsChanged();
		appendObjectToArray(new CW3_StateEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, 100, 100, 1, 10, 2, 10,0));*/
		// Make everything invisible to start with
		setAllObjectsVisible(false);

		break;
	}

	return 0;
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void CW3_Game::virtDrawStringsOnTop()
{
	char buf[128];

	switch (m_state) {
	case stateInit:
		drawForegroundString(15, getWindowHeight() / 2, "Press h to view highscores!", 0xe3e3e3, NULL);
		drawForegroundString(15, getWindowHeight() / 2 + 30, "Press escp to exit!", 0xe3e3e3, NULL);
		
		{
			// look at the input file (quicksave)
			std::ifstream infile("./savedData/quicksave.csv");
			//if the file exists..
			if (infile.good()) {
				drawForegroundString(15, getWindowHeight() / 2 + 60, "Press enter to start new game! (This will delete your quicksave)", 0xe3e3e3, NULL);
				drawForegroundString(15, getWindowHeight() / 2 + 90, "Press l to load game your quicksave game! (This will delete your quicksave)", 0xe3e3e3, NULL);
			}
			else {
				drawForegroundString(15, getWindowHeight() / 2 + 60, "Press enter to start new game!", 0xe3e3e3, NULL);
			}

			infile.close();
		}
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

		drawForegroundRectangle(400, getWindowHeight() / 2 - 5, 900, getWindowHeight() / 2 + 35, 0x262626);

		drawForegroundString(407, getWindowHeight() / 2, "Press p to unpause or s to save!", 0xe3e3e3, NULL);
		break;
	case stateGameOver:

		drawForegroundString(15, 40, "GameOver!", 0xe3e3e3, NULL);

		sprintf(buf, "You got a score of %d", getObjectOfType<CW3_Player>()->getScore());
		drawForegroundString(15, 100, buf, 0xe3e3e3, NULL);

		drawForegroundString(15, getWindowHeight() / 2, "Press enter to play again!", 0xe3e3e3, NULL);
		break;

	case stateHighscores:

		{
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
					drawForegroundString(350, 90 + i * 30, buf, 0xe3e3e3, NULL);

					i++;
				}


				if (i == 0)
					drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
			}
			else {
				drawForegroundString(350, 90, "No highscores to show! Why not have a go? :)", 0xe3e3e3, NULL);
			}

			infile.close();
		}
		break;

	case stateNewHighscore:
		// write this row
		sprintf(buf, "Name: %s", m_playerName.c_str());
		drawForegroundString(15, 100, buf, 0xe3e3e3, NULL);
		break;
	}
}

void CW3_Game::virtMainLoopDoBeforeUpdate()
{
	//pause();
	//sortObjectsByYAxis();
	//unpause();

	
	switch (m_state) {

	case stateInit:
		unpause();
		lockBackgroundForDrawing();
		virtSetupBackgroundBuffer();
		m_bgAnim->renderCurrentFrame(this, this->getBackgroundSurface(), 10, 10, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
		m_bgAnim->renderCurrentFrame(this, this->getBackgroundSurface(), 10, this->getWindowHeight() - 20, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
		m_bgAnim->renderCurrentFrame(this, this->getBackgroundSurface(), this->getWindowWidth() - 20, 10, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
		m_bgAnim->renderCurrentFrame(this, this->getBackgroundSurface(), this->getWindowWidth()-20, this->getWindowHeight() - 20, 10, 10, 0, 0, m_bgAnim->getCurrentFrame().getWidth(), m_bgAnim->getCurrentFrame().getHeight());
		unlockBackgroundForDrawing();
		redrawDisplay();
		pause();
		break;

	case stateMain:

		if (!isPaused() && getRawTime() > m_enemySpawnNextEnemyTime) {
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
			drawableObjectsChanged();

			int simpleEnemyMaxHealth = 25 + (std::rand() % (100 - 25 + 1));
			int simpleEnemySpeed = 1 + (std::rand() % (3 - 1 + 1));

			int enemyType = rand() % 2;
			if(enemyType==0)
				appendObjectToArray(new CW3_SimpleEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, simpleEnemyMaxHealth, simpleEnemyMaxHealth, 10, 25, simpleEnemySpeed, 10));
			else if(enemyType==1)
				appendObjectToArray(new CW3_StateEnemy(m_tm->getTilesXCoordinates(floor.first), m_tm->getTilesYCoordinates(floor.second), this, m_tmTileDimensions, m_tmTileDimensions, simpleEnemyMaxHealth, simpleEnemyMaxHealth, 10, 25, simpleEnemySpeed, 10, 0));
			m_enemySpawnNextEnemyTime = getRawTime() + m_enemySpawnTimeBetweenSpawns;

			if (m_enemySpawnTimeBetweenSpawns * 0.9 >= m_minEnemySpawnTimeBetweenSpawns)
				m_enemySpawnTimeBetweenSpawns *= 0.9;
			else
				m_enemySpawnTimeBetweenSpawns = m_minEnemySpawnTimeBetweenSpawns;

		}

		break;
	}

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
			delete (m_vecDisplayableObjects.at(i));
			m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin()+i);

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