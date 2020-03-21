#pragma once
#include "CW3_GameObject.h"
#include "CW3_DebugHeaders.h"
#include "CW3_BaseEnemy.h"
#include "CollisionDetection.h"
#include "CW3_DungeonTileMapCodes.h"

class CW3_BaseBulletPolymorphic :
	public CW3_GameObject
{


protected:

	class BulletState * m_currentState;

	//member variables
	double m_bulletSpeed;
	double m_AngleRadians;
	int m_bulletDamage;
	int m_bulletMaxDistance;
	int m_bulletColour;

public: 
	//constructor
	CW3_BaseBulletPolymorphic(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians, double speed, int damage, int maxDistance)
		: CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight) {
		m_AngleRadians = angleRadians;
		m_bulletSpeed = speed;
		m_bulletDamage = damage;
		m_bulletMaxDistance = maxDistance;

		m_currentState = new Flying(this);
	}

	double getBulletAngle() {
		return m_AngleRadians;
	}
	double getBulletSpeed() {
		return m_bulletSpeed;
	}
	int getBulletDamage() {
		return m_bulletDamage;
	}
	int getBulletMaxDistance() {
		return m_bulletMaxDistance;
	}
	int getBulletColour() {
		return m_bulletColour;
	}


	virtual void virtDraw() override;

	virtual void virtDoUpdate(int iCurrentTime) override;

	void checkEnemyCollisions() {
		//for each enemy check if we have collided
		std::vector<CW3_BaseEnemy *> vecEnemies = m_pGameEngine->getObjectsOfType<CW3_BaseEnemy>();

		for (int i = 0; i < vecEnemies.size(); i++) {
			// if the bullet is colliding with this enemy
			if (CollisionDetection::checkRectangles(
				m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
				m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
				vecEnemies.at(i)->getCurrentXCoordinate(), vecEnemies.at(i)->getCurrentXCoordinate() + vecEnemies.at(i)->getDrawWidth(),
				vecEnemies.at(i)->getCurrentYCoordinate(), vecEnemies.at(i)->getCurrentYCoordinate() + vecEnemies.at(i)->getDrawHeight()))
			{
				vecEnemies.at(i)->hurt(m_bulletDamage);
				m_pGameEngine->deleteObjectFromArray(m_objectID);
			}

		}
	}
};

class BulletState {

protected:
	int m_iDrawWidth;
	int m_iDrawHeight;
	int  m_bulletColour;

	int m_bulletMaxDistance;
	int m_iCurrentScreenX;
	int m_iCurrentScreenY;
	double m_bulletSpeed;
	double m_AngleRadians;
	CW3_Game* m_pGameEngine;
	CW3_BaseBulletPolymorphic* m_bullet;

public:
	BulletState(CW3_BaseBulletPolymorphic* bullet) {
		
		m_bullet = bullet;
		
		m_iCurrentScreenY = bullet->getCurrentYCoordinate();
		m_iCurrentScreenX = bullet->getCurrentXCoordinate();
		m_bulletMaxDistance = bullet->getBulletMaxDistance;
		m_bulletSpeed = bullet->getBulletSpeed;
		m_AngleRadians = bullet->getBulletAngle;
		m_pGameEngine = bullet->getEngine;
		
		m_iDrawWidth = bullet->getDrawWidth();
		m_iDrawHeight = bullet->getDrawHeight();
		m_bulletColour = bullet->getBulletColour();
	}

	virtual void virtDraw() = 0;
	virtual void virtDoUpdate() = 0;
};

class Flying : public BulletState {

public:
	Flying(CW3_BaseBulletPolymorphic* bullet) : BulletState(bullet){}

	virtual void virtDraw() override {
		m_bullet->getEngine()->drawForegroundOval(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			m_bulletColour);
	}

	virtual void virtDoUpdate() override {
		

		int yIncrease = cos(m_AngleRadians) * -m_bulletSpeed;
		int xIncrease = sin(m_AngleRadians) * -m_bulletSpeed;

		m_iCurrentScreenY += yIncrease;
		m_iCurrentScreenX += xIncrease;

		m_bulletMaxDistance - +yIncrease + xIncrease;

		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY)) {
			// .. store that tiles value and ..
			int newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, m_iCurrentScreenY);

			//.. if it has hit a destroyable object, turn it into a floor
			if (200 <= newTilesValue && newTilesValue < 250) {
				m_pGameEngine->getTileManager()->setAndRedrawMapValueAt(m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(m_iCurrentScreenX), m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(m_iCurrentScreenY), tileFloor1, m_pGameEngine, m_pGameEngine->getBackgroundSurface());
			}

			//.. if it has a value not within the 0-50 partition for floor tiles (tiles that don't have collisions) then it has collided
			// or if it has reached its max distance
			if (50 <= newTilesValue || newTilesValue < 0 || m_bulletMaxDistance <= 0) {
				m_pGameEngine->deleteObjectFromArray(m_bullet->getObjectID());
			}

			m_bullet->checkEnemyCollisions();

		}
	}
};