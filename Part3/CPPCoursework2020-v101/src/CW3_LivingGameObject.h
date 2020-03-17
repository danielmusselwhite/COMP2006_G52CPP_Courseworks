#pragma once
#include "CW3_GameObject.h"

class CW3_LivingGameObject :
	public CW3_GameObject
{
protected:
	//member variables
	int m_speed;
	int m_maxHealth;
	int m_health;

public:

	//constructor/deconstructor
	CW3_LivingGameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth) : CW3_GameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight) {
		m_maxHealth = maxHealth;
		m_health = m_maxHealth;
	}

	// living object must provide implementation
	virtual void virtDie() = 0; //living objects dying behaviour

	//function for taking damage (should be the same for all instances)
	void hurt(int damage) {
		m_health -= damage;
		if (checkDeath())
			virtDie();
	}

	//function for checking if the living object has died
	bool checkDeath() {
		return m_health <= 0;
	}
};

