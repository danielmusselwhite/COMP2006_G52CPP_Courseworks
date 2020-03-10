#pragma once
#include "DisplayableObject.h"
#include "CW3_Game.h"
//extern CW3_Game* m_pGameEngine;


class CW3_GameObject :
	public DisplayableObject
{
public:
	CW3_Game* m_pGameEngine;
	int m_drawableObjectIndex;

	CW3_GameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_GameObject();

	double getCurrentXCoordinate();
	double getCurrentYCoordinate();
};

