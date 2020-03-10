#include "header.h"
#include "CW3_BaseEnemy.h"
#include "BaseEngine.h"
#include "CW3_Game.h"
#include "Math.h"
#include "CW3_Player.h"

int enemySpeed;

CW3_Game* m_pGameEngine;


//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
CW3_BaseEnemy::CW3_BaseEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : CW3_GameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight) {
	enemySpeed = 1;
}

CW3_BaseEnemy::~CW3_BaseEnemy() {

}


void CW3_BaseEnemy::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff0000);
}



void CW3_BaseEnemy::virtDoUpdate(int iCurrentTime)
{
	
	int newTilesValue; //value of tile we are trying to move to
	int newYCoordinate, newXCoordinate; //coordinate we are trying to move to
	int newTilesBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)
	double goalX, goalY; //i.e. targets coordinate
	double angle; // angle of the hypotenuse (as the crow flies) to the target
	double newX; // newX position
	double newY; // newY position

	// for now there is only one player, so get the one at pos 0 in the vector, later maybe make it hostile to the closest if more players/friendlies are added
	CW3_Player target = m_pGameEngine->getObjectsOfType<CW3_Player>().at(0);

	// getting the targets coordnates
	goalX = target.getCurrentXCoordinate();
	goalY = target.getCurrentYCoordinate();
	
	/*//Using trig
	if (abs(goalX - m_iCurrentScreenX) + abs(goalY - m_iCurrentScreenY) >= 50) {
		// angle of as the crow flies to player
		angle = atan2(goalX - m_iCurrentScreenX, goalY - m_iCurrentScreenY);

		// moving towards the player
		m_iCurrentScreenY += enemySpeed * cos(angle);
		m_iCurrentScreenX += enemySpeed * sin(angle);

		redrawDisplay();
	}
	*/


	// using Pythag and ratios
	/*
	int differenceInX = goalX - m_iCurrentScreenX;
	int differenceInY = goalY - m_iCurrentScreenY;

	if(differenceInX!=0)
		m_iCurrentScreenX += (differenceInX / (abs(differenceInX) + abs(differenceInY)))*enemySpeed;
	if(differenceInY!=0)
		m_iCurrentScreenY += (differenceInY / (abs(differenceInX) + abs(differenceInY)))*enemySpeed;
		*/


	// using if statements
	if (goalX < m_iCurrentScreenX) {
		m_iCurrentScreenX -= enemySpeed;
	}
	else if (goalX > m_iCurrentScreenX) {
		m_iCurrentScreenX += enemySpeed;
	}

	if (goalY < m_iCurrentScreenY) {
		m_iCurrentScreenY -= enemySpeed;
	}
	else if (goalY > m_iCurrentScreenY) {
		m_iCurrentScreenY += enemySpeed;
	}
}