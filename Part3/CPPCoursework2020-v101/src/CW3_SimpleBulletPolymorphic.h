#pragma once
#include "CW3_BaseBulletPolymorphic.h"

class CW3_SimpleBulletPolymorphic :
	public CW3_BaseBulletPolymorphic
{
public:
	CW3_SimpleBulletPolymorphic(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians, int speed, int damage, int maxDistance) :
		CW3_BaseBulletPolymorphic(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, angleRadians, speed, damage, maxDistance)
	{
		m_bulletColour = 0x2bcf57;
	}

};

