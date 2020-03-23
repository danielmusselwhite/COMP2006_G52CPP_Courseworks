#pragma once
#include "BaseEngine.h"
#include "CW3_TileManager.h"



class CW3_Game :
	public BaseEngine
{
protected:
	//member variables
	CW3_TileManager *m_tm;
	int m_tmTileDimensions; //member variable to store size of tiles
	int m_tmStartingX; //member variable to store starting x coord to draw from
	int m_tmStartingY; //member variable to store starting y coord to draw from
	int m_playersHighscorePlace; //stores what highscore the player has just got
	std::string m_playerName;
	int m_minEnemySpawnTimeBetweenSpawns;
	int m_maxEnemySpawnTimeBetweenSpawns;
	int m_enemySpawnNextEnemyTime;
	int m_enemySpawnTimeBetweenSpawns;
	std::vector<std::vector<int>> m_dungeonTileMapDesign;



public:
	//constructor/deconstructor
	CW3_Game();
	~CW3_Game();

	//functions relating to m_vecDisplayableObjects
	void deleteObjectFromArray(int objectID);
	void deleteAllObjectsInArray();

	int getDrawableObjectVectorSize()
	{
		return m_vecDisplayableObjects.size();
	}

	//sorting the objects into the vector so objects are drawn in front of eachother relative to their location in the world
	void sortObjectsByYAxis() {

		std::sort(m_vecDisplayableObjects.begin(), m_vecDisplayableObjects.end(), [ ](DisplayableObject* object1, DisplayableObject* object2)
		{ 
			return object1->getYCentre() < object2->getYCentre();
		});
	}


	//functions relating to getting different useful objects
	CW3_TileManager * getTileManager() {
		return m_tm;
	}

	//overriding parent functions
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	int virtInitialiseObjects() override;
	void virtDrawStringsOnTop() override;
	void virtMainLoopDoBeforeUpdate() override;

	void pauseAllGameObjects();
	void unpauseAllGameObjects();

	void setStateGameOver() {
		m_state = stateGameOver;
		
		// Force screen redraw
		lockAndSetupBackground();

		setAllObjectsVisible(false);

		redrawDisplay();
	}


	//generic functions

	// function for returning list of all objects of a specific type (i.e. enemy being able to find player(s)
	template <typename objectType> std::vector<objectType*> getObjectsOfType() {

		// vector of object type
		std::vector<objectType*> vecObs;

		// for each object in the game
		for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
			if (dynamic_cast<objectType*>(m_vecDisplayableObjects.at(i)) != nullptr)
				vecObs.push_back( (objectType*)m_vecDisplayableObjects.at(i) );

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


public:
	// State number - so we can support different states and demonstrate the basics.
	enum State { stateInit, stateMain, statePaused, stateGameOver, stateHighscores, stateNewHighscore};

private:
	// Current state
	State m_state;
};

