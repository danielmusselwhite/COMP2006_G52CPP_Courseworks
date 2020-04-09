#pragma once
#include "CW3_BaseGun.h"
#include "CW3_gunIDs.h"
class CW3_ShotGun :
	public CW3_BaseGun
{
public:
	//constructor
	CW3_ShotGun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int xScale, int yScale);

	virtual void attack() override;

	virtual int getGunType() override {
		return ShotGunID;
	}
};


