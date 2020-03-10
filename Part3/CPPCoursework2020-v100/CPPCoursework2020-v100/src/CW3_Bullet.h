#pragma once
#include "CW3_GameObject.h"

class CW3_Bullet :
	public CW3_GameObject
{
public:
	double m_bulletSpeed;
	double m_AngleRadians;
	CW3_Bullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians);
	~CW3_Bullet();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

};

