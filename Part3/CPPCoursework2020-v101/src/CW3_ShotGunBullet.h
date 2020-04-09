#pragma once
#include "CW3_BaseBullet.h"

class CW3_ShotGunBullet :
	public CW3_BaseBullet
{
public:
	CW3_ShotGunBullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians) :
		CW3_BaseBullet(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, angleRadians)
	{
		m_bulletColour = 0xf007aa;
		m_bulletSpeed = 20;
		m_bulletDamage = 5 + (std::rand() % (10 - 5 + 1));	//each simple bullet will deal random damage in range between 10 and 15
		m_bulletMaxDistance = 300;
		//update image for this bullet type here
	}

	virtual std::vector<std::string> getState() override {
		std::vector<std::string> currentState{ "shotGunBullet",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_AngleRadians) };
		return currentState;
	}
};

