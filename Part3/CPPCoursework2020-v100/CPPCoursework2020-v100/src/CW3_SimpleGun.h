#pragma once
#include "CW3_BaseGun.h"
class CW3_SimpleGun :
	public CW3_BaseGun
{
public:
	//constructor
	CW3_SimpleGun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int drawableObjectIndex, int xScale, int yScale);

	virtual void attack() override;
};

