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


public:
	//constructor/deconstructor
	CW3_Game();
	~CW3_Game();

	//functions relating to m_vecDisplayableObjects
	void CW3_Game::deleteObjectFromArray(int index) {
		delete *(m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + index));
	}

	int CW3_Game::getDrawableObjectVectorSize()
	{
		return m_vecDisplayableObjects.size();
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



	//generic functions

	// function for returning list of all objects of a specific type (i.e. enemy being able to find player(s)
	template <typename objectType> std::vector<objectType> getObjectsOfType() {

		// vector of object type
		std::vector<objectType> vecObs;

		// for each object in the game
		for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
			if (dynamic_cast<objectType*>(m_vecDisplayableObjects.at(i)) != nullptr)
				vecObs.push_back(*((objectType*)m_vecDisplayableObjects.at(i)));

		}

		return vecObs;
	}

	// function for returning list of all objects of a specific type (i.e. enemy being able to find player(s)
	template <typename objectType> objectType getObjectOfType() {

		// for each object in the game
		for (int i = 0; i < m_vecDisplayableObjects.size(); i++) {
			// if this object is the type we are looking for..
			if (dynamic_cast<objectType*>(m_vecDisplayableObjects.at(i)) != nullptr) {
				//.. return it
				return *((objectType*)m_vecDisplayableObjects.at(i));
			}

		}

	}
};

