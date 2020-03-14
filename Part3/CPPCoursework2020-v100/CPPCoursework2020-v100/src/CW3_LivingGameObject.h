#pragma once
#include "CW3_GameObject.h"

class CW3_LivingGameObject :
	public CW3_GameObject
{
protected:
	//member variables
	int m_drawableObjectIndex;
	int m_speed;
	int m_maxHealth;
	int m_health;

public:

	//constructor/deconstructor
	CW3_LivingGameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int speed) : CW3_GameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight) {
		m_maxHealth = maxHealth;
		m_speed = speed;
	}
};

