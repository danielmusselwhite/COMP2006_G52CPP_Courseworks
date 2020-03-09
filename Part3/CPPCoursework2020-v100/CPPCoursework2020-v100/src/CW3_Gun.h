#pragma once
#include "CW3_GameObject.h"

extern CW3_GameObject* m_pWielder;

class CW3_Gun :
	public CW3_GameObject
{
public:
	CW3_Gun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_Gun();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	void SnapToWielder();

	void attack();
};

