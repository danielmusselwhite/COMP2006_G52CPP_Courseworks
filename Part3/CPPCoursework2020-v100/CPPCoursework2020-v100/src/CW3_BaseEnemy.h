#pragma once
#include "CW3_GameObject.h"
class CW3_BaseEnemy :
	public CW3_GameObject
{
	
public:
	CW3_BaseEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_BaseEnemy();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	
};

