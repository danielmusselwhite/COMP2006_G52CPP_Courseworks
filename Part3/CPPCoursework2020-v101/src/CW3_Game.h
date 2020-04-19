#pragma once
#include "BaseEngine.h"
#include "CW3_TileManager.h"
#include "CW3_AnimatedImage.h"

class CW3_Game;
class GameState;
class StateInit;
class LevelState;
class StateLevel1;
class StatePaused;
class StateGameOver;
class StateHighscores;
class StateNewHighscores;

#pragma region States_For_State_Pattern

class GameState {
protected:
	CW3_Game* m_pGameEngine;
	int m_stateID;

public:
	virtual ~GameState() {

	}

	void setContext(CW3_Game* pGameEngine) {
		m_pGameEngine = pGameEngine;
	}

	virtual void setUpBackground() {
		return;
	}

	virtual void handleKeyPresses(int iKeyCode) {
		return;
	}

	virtual void initialiseObjects() {
		return;
	}

	virtual void drawStringsOnTop() {
		return;
	}

	virtual void DoBeforeUpdate() {
		return;
	}

	int getID() {
		return m_stateID;
	}
};

class StateInit : public GameState {
private:
	CW3_AnimatedImage* m_bgAnim;
public:
	StateInit(CW3_Game* pGameEngine);
	virtual ~StateInit() override;

	virtual void setUpBackground() override;

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;

	virtual void DoBeforeUpdate() override;
};


class StatePaused : public GameState {
public:
	StatePaused(CW3_Game* pGameEngine) {
		m_pGameEngine = pGameEngine;
		m_stateID = 1;
	}
	virtual ~StatePaused() override {
		return;
	}

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;

};

class StateGameOver : public GameState {
protected:
	int m_highScore;
public:
	StateGameOver(int playerHighScore, CW3_Game* pGameEngine){
		m_highScore = playerHighScore;
		m_pGameEngine = pGameEngine;
		m_stateID = 2;
	}
	virtual ~StateGameOver() override {
		return;
	}

	virtual void setUpBackground() override;

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;
};

class StateNewHighscores : public GameState {
private:
	std::string m_playerName;
	int m_playersHighscorePlace;
public:
	StateNewHighscores(int playerHighScorePlace, CW3_Game* pGameEngine) {
		m_playersHighscorePlace = playerHighScorePlace;
		m_pGameEngine = pGameEngine;
		m_stateID = 3;
	}
	virtual ~StateNewHighscores() override {
		return;
	}

	virtual void setUpBackground() override;

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;
};

class StateHighscores : public GameState {
public:
	StateHighscores(CW3_Game* pGameEngine) {
		m_pGameEngine = pGameEngine;
		m_stateID = 4;
	}
	virtual ~StateHighscores() override {
		return;
	}

	virtual void setUpBackground() override;

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;

};




class LevelState : public GameState {
protected:
	int m_levelID;

	CW3_TileManager *m_tm;
	std::vector<std::vector<int>> m_dungeonTileMapDesign;
	int m_tmTileDimensions; //member variable to store size of tiles
	int m_tmStartingX; //member variable to store starting x coord to draw from
	int m_tmStartingY; //member variable to store starting y coord to draw from
	int m_playersHighscorePlace; //stores what highscore the player has just got

	int m_minEnemySpawnTimeBetweenSpawns;
	int m_maxEnemySpawnTimeBetweenSpawns;
	int m_enemySpawnNextEnemyTime;
	int m_enemySpawnTimeBetweenSpawns;

public:
	CW3_TileManager* getTileManager() {
		return m_tm;
	}
	void mouseDown(int iButton);

	int getLevelID() {
		return m_levelID;
	}

	int getEnemySpawnNextEnemyTime() {
		return m_enemySpawnNextEnemyTime;
	}

	int getEnemySpawnTimeBetweenSpawns() {
		return m_enemySpawnTimeBetweenSpawns;
	}

	void incrementNextEnemySpawnTime(int addOn) {
		m_enemySpawnNextEnemyTime += addOn;
	}
};

class StateLevel1 : public LevelState {

public:
	StateLevel1(CW3_Game *pGameEngine);
	StateLevel1(std::ifstream* loadGame, CW3_Game *pGameEngine);
	virtual ~StateLevel1() override;

	virtual void setUpBackground() override;

	virtual void initialiseObjects() override;

	virtual void handleKeyPresses(int iKeyCode) override;

	virtual void drawStringsOnTop() override;

	virtual void DoBeforeUpdate() override;

	virtual CW3_TileManager* getTileManager() {
		return m_tm;
	}
};

#pragma endregion States_For_State_Pattern

#pragma region Main_Game_Engine

class CW3_Game : public BaseEngine {

protected:
	GameState *m_gameState;
	LevelState *m_currentLevel;
public:
	CW3_Game();
	~CW3_Game();

#pragma region State_Pattern_Methods
	void transitionToState(GameState *state);
	void setCurrentLevel(LevelState *level);
	void switchToPauseState();
	void switchFromPauseState();
#pragma endregion State_Pattern_Methods

	LevelState * getCurrentLevel() {
		return m_currentLevel;
	}

	std::vector<DisplayableObject *>* get_m_vecDisplayableObjects() {
		return &m_vecDisplayableObjects;
	}

	//deleting object from vector using its id
	void deleteObjectFromArray(int objectID);
	//deleting all objects from the vector
	void deleteAllObjectsInArray();

	// gettomg size of drawableObjectVector
	int getDrawableObjectVectorSize()
	{
		return m_vecDisplayableObjects.size();
	}

	//sorting the objects into the vector so objects are drawn in front of eachother relative to their location in the world
	void sortObjectsByYAxis() {

		std::sort(m_vecDisplayableObjects.begin(), m_vecDisplayableObjects.end(), [](DisplayableObject* object1, DisplayableObject* object2)
		{
			return object1->getYCentre() < object2->getYCentre();
		});
	}

	//getting the tile manager
	CW3_TileManager * getTileManager() {
		return m_currentLevel->getTileManager();
	}

	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	int virtInitialiseObjects() override;
	void virtDrawStringsOnTop() override;
	void virtMainLoopDoBeforeUpdate() override;

	void pauseAllGameObjects();
	void unpauseAllGameObjects();

	// template functions used for getting objects of specific type 

	// function for returning list of all objects of a specific type (i.e. enemy being able to find player(s)
	template <typename objectType> std::vector<objectType*> getObjectsOfType() {

		// vector of object type
		std::vector<objectType*> vecObs;

		// for each object in the game
		for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
			if (dynamic_cast<objectType*>(m_vecDisplayableObjects.at(i)) != nullptr)
				vecObs.push_back((objectType*)m_vecDisplayableObjects.at(i));

		}

		return vecObs;
	}

	// function for returning list of all objects of a specific type (i.e. enemy being able to find player(s)
	template <typename objectType> objectType* getObjectOfType() {

		// for each object in the game
		for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
			// if this object is the type we are looking for..
			if (dynamic_cast<objectType*>(m_vecDisplayableObjects.at(i)) != nullptr) {
				//.. return it
				return (objectType*)m_vecDisplayableObjects.at(i);
			}

		}

		throw - 1;
	}
};

#pragma endregion Main_GameEngine
