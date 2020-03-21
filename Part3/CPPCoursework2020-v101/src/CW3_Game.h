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
	void deleteObjectFromArray(int objectID);

	int getDrawableObjectVectorSize()
	{
		return m_vecDisplayableObjects.size();
	}

	//sorting the objects into the vector so objects are drawn in front of eachother relative to their location in the world
	void sortObjectsByYAxis() {

		std::sort(m_vecDisplayableObjects.begin(), m_vecDisplayableObjects.end(), [ ](DisplayableObject* object1, DisplayableObject* object2)
		{ 
			
			//if (dynamic_cast<CW3_GameObject*>(object1) != nullptr){// && dynamic_cast<CW3_GameObject*>(object2)) {
				//CW3_GameObject * gameObject1 = (CW3_GameObject *)object1;
				//CW3_GameObject * gameObject2= (CW3_GameObject *)object2;

				//return gameObject1->getYCoordinateToBeSortedBy() > gameObject2->getYCoordinateToBeSortedBy();
			//}

			// if one or more isn't a game object, don't change their positions
			//return false;
			
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
	enum State { stateInit, stateMain, statePaused, stateGameOver };

private:
	// Current state
	State m_state;
};

