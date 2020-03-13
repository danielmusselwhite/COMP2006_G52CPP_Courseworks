#pragma once
#include "CW3_GameObject.h"

class CW3_BaseBullet :
	public CW3_GameObject
{


protected:
	//member variables
	double m_bulletSpeed;
	double m_AngleRadians;
	int m_bulletDamage;
	int m_bulletMaxDistance;
	SimpleImage m_bulletImage;	// for now just using squares later will be images

public:

	//constructor
	CW3_BaseBullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, int drawableObjectIndex, double angleRadians)
		: CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, drawableObjectIndex) {
		m_AngleRadians = angleRadians;
	}

	// overriding virtual methods
	void virtDraw() {
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xffff00);
	}

	// can be overwritten but has general structure of how bullet will act
	virtual void virtDoUpdate(int iCurrentTime) override {
		
		int yIncrease = cos(m_AngleRadians) * -m_bulletSpeed;
		int xIncrease = sin(m_AngleRadians) * -m_bulletSpeed;
		
		m_iCurrentScreenY += yIncrease;
		m_iCurrentScreenX += xIncrease;

		m_bulletMaxDistance - +yIncrease + xIncrease;

		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY)) {
			// .. store that tiles value and ..
			int newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, m_iCurrentScreenY);

			//.. if it has a value not within the 0-50 partition for floor tiles (tiles that don't have collisions) then it has collided
			// or if it has reached its max distance
			if (50 <= newTilesValue || newTilesValue < 0 || m_bulletMaxDistance<=0) {
				//m_pGameEngine->deleteObjectFromArray(m_drawableObjectIndex);
			}
		}
	}

};