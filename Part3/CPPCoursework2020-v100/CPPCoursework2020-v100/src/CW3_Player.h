#pragma once
#include "CW3_GameObject.h"
class CW3_Player :
	public CW3_GameObject
{
public:
	CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_Player();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void shootGun();
};

