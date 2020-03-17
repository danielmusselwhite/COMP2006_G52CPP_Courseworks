#pragma once
#include "CW3_BaseBullet.h"

class CW3_SimpleBullet:
	public CW3_BaseBullet
{
public:
	CW3_SimpleBullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians) :
		CW3_BaseBullet(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, angleRadians) 
	{
		m_bulletSpeed = 15;
		m_bulletDamage = 10 + (std::rand() % (15 - 10 + 1));	//each simple bullet will deal random damage in range between 10 and 15
		m_bulletMaxDistance = 300;
		//update image for this bullet type here
	}

};
