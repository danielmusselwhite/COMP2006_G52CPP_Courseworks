#pragma once
#include "CW3_BaseEnemy.h"
#include "CW3_AnimatedImage.h"

class CW3_SimpleEnemy :
	public CW3_BaseEnemy
{
protected:
	CW3_AnimatedImage* m_Anim;
	CW3_AnimatedImage* m_LeftWalkAnim;
	CW3_AnimatedImage* m_RightWalkAnim;

public:
	//constructor
	CW3_SimpleEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int minDamage, int maxDamage, int speed, int pointsValue);
	//deconstructor
	~CW3_SimpleEnemy();

	// overriding BaseEnemy functions
	void virtAttack() override;
	void virtMove() override;

	// overriding GameObject functions
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

	// overiding LivingGameObject functions
	void virtDie() override;

};

