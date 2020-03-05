#pragma once
#include "DisplayableObject.h"
class CW3_Player :
	public DisplayableObject
{
public:
	CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_Player();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
};

