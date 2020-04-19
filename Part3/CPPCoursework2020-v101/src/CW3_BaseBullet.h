#pragma once
#include "CW3_GameObject.h"
#include "CW3_DebugHeaders.h"
#include "CW3_BaseEnemy.h"
#include "CollisionDetection.h"
#include "CW3_DungeonTileMapCodes.h"

class CW3_BaseBullet :
	public CW3_GameObject
{


protected:
	//member variables
	double m_bulletSpeed;
	double m_AngleRadians;
	int m_bulletDamage;
	int m_bulletMaxDistance;
	int m_bulletColour;
	SimpleImage m_bulletImage;	// for now just using squares later will be images

public:

	//constructor
	CW3_BaseBullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians)
		: CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight) {
		m_AngleRadians = angleRadians;
	}

	// overriding virtual methods
	void virtDraw() {
		// only do this if visible
		if (!isVisible())
			return;

		getEngine()->drawForegroundOval(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			m_bulletColour);
	}

	// can be overwritten but has general structure of how bullet will act
	virtual void virtDoUpdate(int iCurrentTime) override {
		// only do this if visible and not paused
		if (!isVisible() || m_isPaused)
			return;


		int yIncrease = cos(m_AngleRadians) * -m_bulletSpeed;
		int xIncrease = sin(m_AngleRadians) * -m_bulletSpeed;
		
		m_iCurrentScreenY += yIncrease;
		m_iCurrentScreenX += xIncrease;

		m_bulletMaxDistance -= abs(yIncrease) + abs(xIncrease);

		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY)) {
			// .. store that tiles value and ..
			int newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, m_iCurrentScreenY);

			//.. if it has hit a destroyable object, turn it into a floor
			if (200 <= newTilesValue && newTilesValue < 250) {
				m_pGameEngine->getTileManager()->setAndRedrawMapValueAt(m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(m_iCurrentScreenX), m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(m_iCurrentScreenY), tileFloor1, m_pGameEngine, m_pGameEngine->getBackgroundSurface());
			}

			//.. if it has a value not within the 0-50 partition for floor tiles (tiles that don't have collisions) then it has collided
			// or if it has reached its max distance
			if (50 <= newTilesValue || newTilesValue < 0 || m_bulletMaxDistance<=0) {
				m_pGameEngine->deleteObjectFromArray(m_objectID);
				return;
			}

			checkEnemyCollisions();

		}
	}

	void checkEnemyCollisions() {

		//for each enemy check if we have collided
		std::vector<CW3_BaseEnemy *> vecEnemies = m_pGameEngine->getObjectsOfType<CW3_BaseEnemy>();

		for (int i = 0; i < vecEnemies.size(); i++) {
			// if the bullet is colliding with this enemy
			if(CollisionDetection::checkRectangles(
				m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
				m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
				vecEnemies.at(i)->getCurrentXCoordinate(), vecEnemies.at(i)->getCurrentXCoordinate() + vecEnemies.at(i)->getDrawWidth(),
				vecEnemies.at(i)->getCurrentYCoordinate(), vecEnemies.at(i)->getCurrentYCoordinate() + vecEnemies.at(i)->getDrawHeight()))
			{
				vecEnemies.at(i)->hurt(m_bulletDamage);

				m_pGameEngine->deleteObjectFromArray(m_objectID);
				break;
			}

		}

	}

};