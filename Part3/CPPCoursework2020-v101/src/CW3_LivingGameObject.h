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

	void renderHealthbar() {

		//drawing the red behind
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY-m_iDrawHeight/5,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY - m_iDrawHeight/10,
			0xa83232);

		double ratio = (double) m_health / (double)m_maxHealth;
		
		//drawing the green infront
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 5,
			m_iCurrentScreenX + (m_iDrawWidth) * (ratio),
			m_iCurrentScreenY - m_iDrawHeight / 10,
			0x3ca331);

		// Build the string to print displaying the living objects current health
		char buf [128];
		sprintf(buf, "%i/%i",m_health,m_maxHealth);
		m_pGameEngine->drawForegroundString(m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight/2, buf, 0xe3e3e3, m_pGameEngine->getFont(m_pGameEngine->getDefaultFont()->getName(), 12));
	}
};

