#include "header.h"
#include "CW3_BaseEnemy.h"
#include "BaseEngine.h"
#include "CW3_Game.h"
#include "Math.h"
/*
int enemySpeed;

CW3_Game* m_pGameEngine;


//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
CW3_BaseEnemy::CW3_BaseEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, true) {
	enemySpeed = 3;
	
	m_pGameEngine = (CW3_Game*)pEngine;
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


/*
void CW3_BaseEnemy::virtDoUpdate(int iCurrentTime)
{
	
	int newTilesValue; //value of tile we are trying to move to
	int newYCoordinate, newXCoordinate; //coordinate we are trying to move to
	int newTilesBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)

	/*int goalX,goalY; //i.e. player coordinate

	//get the angle from here to the goal
	int angle = atan((m_iCurrentScreenX - goalX) / (m_iCurrentScreenY - goalY));

	//if angle is 0 then its just moving in the x
	int newX = m_iCurrentScreenX + (enemySpeed*(abs(1 - angle)));
	int newY = m_iCurrentScreenY + (enemySpeed*angle);

	//if angle is 1 then it is just moving in the y*/

	// Ensure that the objects get redrawn on the display
	/*redrawDisplay();
}*/