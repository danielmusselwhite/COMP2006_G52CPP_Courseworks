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
	CW3_GameObject target = m_pGameEngine->getObjectOfType<CW3_Player>();
	
	
	// getting the targets coordnates
	goalX = target.getCurrentXCoordinate();
	goalY = target.getCurrentYCoordinate();

	// angle of as the crow flies to player
	angle = atan2(goalX - m_iCurrentScreenX, goalY - m_iCurrentScreenY);

	// moving towards the player
	m_iCurrentScreenX = cos(angle)*enemySpeed;
	m_iCurrentScreenY = cos(angle)*enemySpeed;
	
	redrawDisplay();
}