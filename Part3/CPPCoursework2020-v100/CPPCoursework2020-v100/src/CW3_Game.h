#pragma once
#include "BaseEngine.h"
#include "CW3_TileManager.h"

class CW3_Game :
	public BaseEngine
{
public:
	CW3_Game();
	~CW3_Game();
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	int virtInitialiseObjects() override;

	CW3_TileManager * getTileManager();

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



protected:
	CW3_TileManager *tm;

};

