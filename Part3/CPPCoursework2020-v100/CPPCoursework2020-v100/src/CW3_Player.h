#pragma once
#include "CW3_LivingGameObject.h"
#include "CW3_BaseGun.h"

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
	

public:
	//constructor/deconstructor
	CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, int drawableObjectIndex, int maxHealth, int crawlSpeed, int walkSpeed, int runSpeed);
	~CW3_Player();

	//player methods
	void shootGun();

	//overriding parent methods
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
};

