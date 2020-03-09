#pragma once
#include "CW3_GameObject.h"

extern CW3_GameObject* m_pWielder;

class CW3_Sword :
	public CW3_GameObject
{
public:
	CW3_Sword(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight);
	~CW3_Sword();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	void CW3_Sword::SnapToWielder();

};

