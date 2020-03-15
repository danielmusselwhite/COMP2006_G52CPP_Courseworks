#pragma once
#include "CW3_LivingGameObject.h"

class CW3_BaseEnemy :
	public CW3_LivingGameObject
{
protected:
	//member variables
	int m_maxDamage;
	int m_minDamage;

public:
	//constructor/deconstructor
	CW3_BaseEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int minDamage, int maxDamage, int speed) : CW3_LivingGameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, maxHealth) {
		m_maxDamage = maxDamage;
		m_minDamage = minDamage;
		m_speed = speed;
	}

	//functions to be overrided:
	virtual void virtAttack() = 0; //enemies attack behaviour
	virtual void virtMove() = 0; //enemies movement behaviour
};