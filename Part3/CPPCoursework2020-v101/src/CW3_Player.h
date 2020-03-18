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
	int m_score = 0;

	CW3_AnimatedImage* m_idleAnim;
	CW3_AnimatedImage* m_idleLeftAnim;
	CW3_AnimatedImage* m_idleRightAnim;
	

public:
	//constructor/deconstructor
	CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, int maxHealth, int crawlSpeed, int walkSpeed, int runSpeed);
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
};

