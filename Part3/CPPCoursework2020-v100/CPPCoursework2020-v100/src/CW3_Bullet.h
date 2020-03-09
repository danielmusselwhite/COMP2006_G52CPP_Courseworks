#pragma once
#include "CW3_GameObject.h"

extern double m_bulletSpeed;
extern double m_AngleRadians;

class CW3_Bullet :
	public CW3_GameObject
{
public:
	CW3_Bullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians);
	~CW3_Bullet();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

};

