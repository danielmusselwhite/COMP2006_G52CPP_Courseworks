#include "header.h"
#include "CW3_Player.h"
#include "BaseEngine.h"
#include "CW3_Game.h"

int playerCurrentSpeed, playerWalkSpeed, playerRunSpeed;

CW3_Game* m_pGameEngine;


//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
CW3_Player::CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, true) {
	playerWalkSpeed = 3;
	playerRunSpeed = 7;
	playerCurrentSpeed = playerWalkSpeed;

	CW3_Game* test;
	BaseEngine* test2;


	m_pGameEngine = (CW3_Game*)pEngine;
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
	int newTilesValue;

	// if shift key is pressed change players speed
	if (getEngine()->isKeyPressed(SDLK_LSHIFT)) {
		playerCurrentSpeed = playerRunSpeed;
	}
	else {
		playerCurrentSpeed = playerWalkSpeed;
	}


	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP)) {

		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY - playerCurrentSpeed)) {
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, m_iCurrentScreenY - playerCurrentSpeed);
			if (50 > newTilesValue && newTilesValue >=0) {
				m_iCurrentScreenY -= playerCurrentSpeed;
			}
			
		}

	}
	if (getEngine()->isKeyPressed(SDLK_DOWN)) {

		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight + playerCurrentSpeed)) {
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight + playerCurrentSpeed);
			if (50 > newTilesValue && newTilesValue >= 0) {
				m_iCurrentScreenY += playerCurrentSpeed;
			}

		}

	}

	if (getEngine()->isKeyPressed(SDLK_LEFT)) {
		
		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX - playerCurrentSpeed, m_iCurrentScreenY)) {
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX - playerCurrentSpeed, m_iCurrentScreenY);
			if (50 > newTilesValue && newTilesValue >= 0) {
				m_iCurrentScreenX -= playerCurrentSpeed;
			}

		}
		
	}

	if (getEngine()->isKeyPressed(SDLK_RIGHT)) {
		if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX + m_iDrawWidth + playerCurrentSpeed, m_iCurrentScreenY)) {
			newTilesValue = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX + m_iDrawWidth + playerCurrentSpeed, m_iCurrentScreenY);
			if (50 > newTilesValue && newTilesValue >= 0) {
				m_iCurrentScreenX += playerCurrentSpeed;
			}

		}
	}


	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}