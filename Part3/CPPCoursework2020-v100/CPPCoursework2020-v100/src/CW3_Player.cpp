#include "header.h"
#include "CW3_Player.h"
#include "BaseEngine.h"
#include "CW3_Game.h"

int playerCurrentSpeed, playerCrawlSpeed, playerWalkSpeed, playerRunSpeed;

//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
CW3_Player::CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : CW3_GameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight) {
	playerCrawlSpeed = 1;
	playerWalkSpeed = 3;
	playerRunSpeed = 5;
	playerCurrentSpeed = playerWalkSpeed;
}

CW3_Player::~CW3_Player() {
	
}

void CW3_Player::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
}



void CW3_Player::virtDoUpdate(int iCurrentTime)
{
	int newTilesValue; //value of tile we are trying to move to
	int newYCoordinate, newXCoordinate; //coordinate we are trying to move to
	int newTilesBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)

	// if shift key is pressed change to run speed
	if (getEngine()->isKeyPressed(SDLK_LSHIFT)) {
		playerCurrentSpeed = playerRunSpeed;
	}
	// else if control key is pressed change to crawl speed
	else if (getEngine()->isKeyPressed(SDLK_LCTRL)) {
		playerCurrentSpeed = playerCrawlSpeed;
	}
	// else use default walk speed
	else {
		playerCurrentSpeed = playerWalkSpeed;
	}


	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP)) {

		//new coordinate we want to move to is the current position increased by speed
		newYCoordinate = m_iCurrentScreenY - playerCurrentSpeed;
		
		// if this is new position is a valid tile position..
		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, newYCoordinate)) {
			
			// .. store that tiles value and ..
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate);
			
			//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
			if (50 > newTilesValue && newTilesValue >=0) {
				//.. move the player to their new coordinate
				m_iCurrentScreenY = newYCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the bottom of the tile
				newTilesBounds = m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(newYCoordinate) + 1;
				// snap to the bottom of the tile we cannot move past (Coordinate of start of tilemap + height of each tile * index of tile limit
				m_iCurrentScreenY = (m_pGameEngine->getTileManager()->getBaseScreenY()) + ((m_pGameEngine->getTileManager()->getTileHeight())) * newTilesBounds;
			}
			
		}

	}
	if (getEngine()->isKeyPressed(SDLK_DOWN)) {

		//new coordinate we want to move to is the current position then increased by speed
		newYCoordinate = m_iCurrentScreenY + playerCurrentSpeed;

		// if this is new position + player height (as the bottom of the player is the limit) is a valid tile position..
		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, newYCoordinate+m_iDrawHeight)) {
			// .. store that tiles value and ..
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate + m_iDrawHeight);

			//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
			if (50 > newTilesValue && newTilesValue >= 0) {
				//.. move the player to their new coordinate
				m_iCurrentScreenY = newYCoordinate;
			}
			//..else this a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to -1 as the limit is the top of the tile
				newTilesBounds = m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(newYCoordinate+m_iDrawHeight)-1;
				// snap to the top of the tile we cannot move past (Coordinate of start of tilemap + height of each tile * index of tile limit
				m_iCurrentScreenY = (m_pGameEngine->getTileManager()->getBaseScreenY()) + ((m_pGameEngine->getTileManager()->getTileHeight())) * newTilesBounds;
			}

		}

	}

	if (getEngine()->isKeyPressed(SDLK_LEFT)) {
		//new coordinate we want to move to is the current position then increased by speed
		newXCoordinate = m_iCurrentScreenX - playerCurrentSpeed;

		// if this is new position is a valid tile position..
		if (m_pGameEngine->getTileManager()->isValidTilePosition(newXCoordinate, m_iCurrentScreenY)) {
			// .. store that tiles value and ..
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate, m_iCurrentScreenY);
			
			//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
			if (50 > newTilesValue && newTilesValue >= 0) {
				//.. move the player to their new coordinate
				m_iCurrentScreenX = newXCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the right of the tile
				newTilesBounds = m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(newXCoordinate) + 1;
				// snap to the right of the tile we cannot move past (Coordinate of start of tilemap + width of each tile * index of tile limit
				m_iCurrentScreenX = (m_pGameEngine->getTileManager()->getBaseScreenX()) + ((m_pGameEngine->getTileManager()->getTileWidth())) * newTilesBounds;
			}

		}
		
	}

	if (getEngine()->isKeyPressed(SDLK_RIGHT)) {
		//new coordinate we want to move to is the current position then increased by speed
		newXCoordinate = m_iCurrentScreenX + playerCurrentSpeed;

		// if this is new position + player width (as the right of the player is the limit) is a valid tile position..
		if (m_pGameEngine->getTileManager()->isValidTilePosition(newXCoordinate+m_iDrawWidth, m_iCurrentScreenY)) {
			// .. store that tiles value and ..
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate+m_iDrawWidth, m_iCurrentScreenY);

			//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
			if (50 > newTilesValue && newTilesValue >= 0) {
				//.. move the player to their new coordinate
				m_iCurrentScreenX = newXCoordinate;
			}
			//..else this is a tile with a physical boundary..
			else {
				// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the left of the tile
				newTilesBounds = m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(newXCoordinate+ m_iDrawWidth) - 1;
				// snap to the left of the tile we cannot move past (Coordinate of start of tilemap + width of each tile * index of tile limit
				m_iCurrentScreenX = (m_pGameEngine->getTileManager()->getBaseScreenX()) + ((m_pGameEngine->getTileManager()->getTileWidth())) * newTilesBounds;
			}

		}
	}


	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}