#pragma once
#include "CW3_LivingGameObject.h"
#include "CW3_BaseGun.h"
#include "CW3_AnimatedImage.h"

class CW3_Player :
	public CW3_LivingGameObject
{
protected:
	//member variables
	int m_walkSpeed;
	int m_crawlSpeed;
	int m_runSpeed;
	int m_speed;
	CW3_BaseGun* m_pGun;
	int m_score;
	bool m_invuln=false; // default invuln to false
	int m_invulnTime = 750;
	int m_invulnTimer;

	CW3_AnimatedImage* m_Anim;
	CW3_AnimatedImage* m_LeftAnim;
	CW3_AnimatedImage* m_RightAnim;
	

public:
	//constructor/deconstructor
	CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, int maxHealth, int currentHealth, int crawlSpeed, int walkSpeed, int runSpeed, int score);
	~CW3_Player();

	//player methods
	void shootGun();
	void increaseScore(int points);
	int getScore() {
		return m_score;
	}

	//overriding parent methods
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	void virtDie() override;

	virtual void hurt(int damage) override {
		// if the player isn't invuln
		if (!m_invuln) {
			// call super for damage effect
			CW3_LivingGameObject::hurt(damage);
			m_invuln = true;
			m_invulnTimer = m_pGameEngine->getRawTime() + m_invulnTime;
		}
	}

	virtual std::vector<std::string> getState() override {

		std::vector<std::string> currentState{ "player",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_maxHealth), std::to_string(m_health), std::to_string(m_crawlSpeed), std::to_string(m_walkSpeed), std::to_string(m_runSpeed) };
		return currentState;
	}
};

