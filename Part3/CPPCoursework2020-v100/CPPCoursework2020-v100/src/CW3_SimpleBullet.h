#pragma once
#include "CW3_BaseBullet.h"

class CW3_SimpleBullet:
	CW3_BaseBullet
{
public:
	CW3_SimpleBullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, int drawableObjectIndex, double angleRadians, int bulletSpeed, int bulletDamage, int bulletMaxDistance) :
		CW3_BaseBullet(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, drawableObjectIndex, angleRadians, bulletSpeed, bulletDamage, bulletMaxDistance) 
	{
		//update image for this bullet type here
	}

};

