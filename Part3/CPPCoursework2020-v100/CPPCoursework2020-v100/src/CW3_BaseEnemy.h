#pragma once
#include "CW3_LivingGameObject.h"

class CW3_BaseEnemy :
	public CW3_LivingGameObject
{
protected:
	//member variables
	int m_maxDamage;
	int m_minDamage;

public:
	//constructor/deconstructor
	CW3_BaseEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int minDamage, int maxDamage, int speed) : CW3_LivingGameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, maxHealth) {
		m_maxDamage = maxDamage;
		m_minDamage = minDamage;
		m_speed = speed;
	}

	void checkTileMapCollisions(int newXCoordinate, int newYCoordinate) {
		int newTilesValueTopLeft = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate);	//top left
		int newTilesValueTopRight = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX + m_iDrawWidth - 1, newYCoordinate); //top right
		int newTilesValueBottomLeft = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate + m_iDrawHeight); //bottom left
		int newTilesValueBottomRight = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX + m_iDrawWidth - 1, newYCoordinate + m_iDrawHeight); //bottom right
		int newTileXBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)
		int newTileYBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)
		
							// if we are moving left
		if (newXCoordinate - m_iCurrentScreenX < 0) {
			if (50 > newTilesValueTopLeft && newTilesValueTopLeft >= 0 && 50 > newTilesValueBottomLeft && newTilesValueBottomLeft >= 0) {
				//.. move to new coordinate
				m_iCurrentScreenX = newXCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the right of the tile
				newTileXBounds = m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(newXCoordinate) + 1;
				// snap to the right of the tile we cannot move past (Coordinate of start of tilemap + width of each tile * index of tile limit
				m_iCurrentScreenX = (m_pGameEngine->getTileManager()->getBaseScreenX()) + ((m_pGameEngine->getTileManager()->getTileWidth())) * newTileXBounds;
			}
		}
		// else if we are moving right
		else {
			if (50 > newTilesValueTopRight && newTilesValueTopRight >= 0 && 50 > newTilesValueBottomRight && newTilesValueBottomRight >= 0) {
				//.. move to new coordinate
				m_iCurrentScreenX = newXCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the left of the tile
				newTileXBounds = m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(newXCoordinate + m_iDrawWidth) - 1;
				// snap to the left of the tile we cannot move past (Coordinate of start of tilemap + width of each tile * index of tile limit
				m_iCurrentScreenX = (m_pGameEngine->getTileManager()->getBaseScreenX()) + ((m_pGameEngine->getTileManager()->getTileWidth())) * newTileXBounds;
			}
		}

		// if we are moving up
		if (newYCoordinate - m_iCurrentScreenY < 0) {
			if (50 > newTilesValueTopLeft && newTilesValueTopLeft >= 0 && 50 > newTilesValueTopRight && newTilesValueTopRight >= 0) {
				//.. move to new coordinate
				m_iCurrentScreenY = newYCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the bottom of the tile
				newTileYBounds = m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(newYCoordinate) + 1;
				// snap to the bottom of the tile we cannot move past (Coordinate of start of tilemap + height of each tile * index of tile limit
				m_iCurrentScreenY = (m_pGameEngine->getTileManager()->getBaseScreenY()) + ((m_pGameEngine->getTileManager()->getTileHeight())) * newTileYBounds;
			}
		}
		// else if we are moving down
		else {
			if (50 > newTilesValueBottomLeft && newTilesValueBottomLeft >= 0 && 50 > newTilesValueBottomRight && newTilesValueBottomRight >= 0) {
				//.. move to new coordinate
				m_iCurrentScreenY = newYCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to -1 as the limit is the top of the tile
				newTileYBounds = m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(newYCoordinate + m_iDrawHeight) - 1;
				// snap to the top of the tile we cannot move past (Coordinate of start of tilemap + height of each tile * index of tile limit
				m_iCurrentScreenY = (m_pGameEngine->getTileManager()->getBaseScreenY()) + ((m_pGameEngine->getTileManager()->getTileHeight())) * newTileYBounds;
			}
		}
	}

	//functions to be overrided:
	virtual void virtAttack() = 0; //enemies attack behaviour
	virtual void virtMove() = 0; //enemies movement behaviour
};