#pragma once
#include "DisplayableObject.h"
#include "CW3_Game.h"

static int maxObjectID = 0;

class CW3_GameObject :
	public DisplayableObject
{
public:
	CW3_Game* m_pGameEngine;
	int m_drawableObjectIndex;
	const int m_objectID = maxObjectID;

	CW3_GameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int drawableObjectIndex) : DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, true) {
		//(CW3_Game*)pEngine;
		m_pGameEngine = dynamic_cast<CW3_Game*>(pEngine); //checks its a subclass first
		m_drawableObjectIndex = drawableObjectIndex;
		maxObjectID++;
		std::cout << "Created new object with ID: " << m_objectID << " and at memory address: "<<this<<"\n";
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
};