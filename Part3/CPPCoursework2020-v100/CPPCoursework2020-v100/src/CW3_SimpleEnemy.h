#pragma once
#include "CW3_BaseEnemy.h"
class CW3_SimpleEnemy :
	public CW3_BaseEnemy
{
public:
	//constructor
	CW3_SimpleEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int minDamage, int maxDamage, int speed, int pointsValue) : CW3_BaseEnemy(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, maxHealth, minDamage, maxDamage, speed, pointsValue){
	}

	// overriding BaseEnemy functions
	void virtAttack() override;
	void virtMove() override;

	// overriding GameObject functions
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

	// overiding LivingGameObject functions
	void virtDie() override;

};

