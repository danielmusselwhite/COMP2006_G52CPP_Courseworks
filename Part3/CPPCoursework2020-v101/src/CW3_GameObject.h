#pragma once
#include "DisplayableObject.h"
#include "CW3_Game.h"
#include "CW3_DebugHeaders.h"

static int maxObjectID = 0;

class CW3_GameObject :
	public DisplayableObject
{
public:
	CW3_Game* m_pGameEngine;
	const int m_objectID = maxObjectID;

	CW3_GameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, true) {
		//(CW3_Game*)pEngine;
		m_pGameEngine = dynamic_cast<CW3_Game*>(pEngine); //checks its a subclass first
		maxObjectID++;
#if showDebugPrintObjectCreationDeletion == 1
		std::cout << "\nCreated new object with ID: " << m_objectID << " and at memory address: "<<this<<"\n";
#endif
	}

	int getCurrentXCoordinate() {
		return m_iCurrentScreenX;
	}
	int getCurrentYCoordinate() {
		return m_iCurrentScreenY;
	}

	int getObjectID() {
		return m_objectID;
	}

	// made virtual as, whilst most will be drawn from their bottom i.e. player/enemies who will be drawn from their 'feet'
	// things like bullets may want to override and draw by some offset underneath their bottom as they aren't on the ground but are 'in the air'
	// so if there was a z axis, player would be theoretically at 0, whilst bullet may be at 10; by allowing things to override this they can account for that offset
	virtual int getYCoordinateToBeSortedBy() {
		return m_iCurrentScreenY + m_iDrawHeight;
	}
};