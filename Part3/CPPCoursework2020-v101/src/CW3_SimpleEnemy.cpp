#include "header.h"
#include "CW3_SimpleEnemy.h"
#include "CW3_Player.h"

#define UseMovementType 1

void CW3_SimpleEnemy::virtAttack()
{
	// for now there is only one player, so get the one at pos 0 in the vector, later maybe make it hostile to the closest if more players/friendlies are added
	CW3_Player* target = m_pGameEngine->getObjectOfType<CW3_Player>();

	int goalX = target->getCurrentXCoordinate();
	int goalY = target->getCurrentYCoordinate();
	double differenceInX = goalX - m_iCurrentScreenX;
	double differenceInY = goalY - m_iCurrentScreenY;
	double distance = sqrt((pow(differenceInX, 2)) + (pow(differenceInY, 2)));

	// if player is within certain distance, do the attack
		// maybe make a hitbox class and instantiate that at the end of the attack and if player is within coordinate of the hitbox then damage
}

void CW3_SimpleEnemy::virtMove()
{
	int newTilesValue; //value of tile we are trying to move to
	int newYCoordinate, newXCoordinate; //coordinate we are trying to move to
	int newTilesBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)
	double goalX, goalY; //i.e. targets coordinate
	double angle; // angle of the hypotenuse (as the crow flies) to the target
	double newX = m_iCurrentScreenX; // newX position (defaulted to current)
	double newY = m_iCurrentScreenY; // newY position (defaulted to current)

	// for now there is only one player, so get the one at pos 0 in the vector, later maybe make it hostile to the closest if more players/friendlies are added
	CW3_Player* target = m_pGameEngine->getObjectOfType<CW3_Player>();

	goalX = target->getCurrentXCoordinate();
	goalY = target->getCurrentYCoordinate();

	double differenceInX = goalX - m_iCurrentScreenX;
	double differenceInY = goalY - m_iCurrentScreenY;
	double distance = sqrt((pow(differenceInX, 2)) + (pow(differenceInY, 2)));

	// if the distance is greater than the total speed, move towards the target
	if (distance > m_speed) {
		
#if UseMovementType == 0
		// smarter way using ratio of x to y to get smoother travel
		// only suitable for faster speeds as engine only allows for integer coordinates so will drop everything after the decimal point
		// will result in doubles under 1 to have no movement and doubles with decimal point to less 1 coordinate in movement
		// i.e. if speed is 5, 0.8x + 4.2y = total change of 4 (as you drop dp's)
		double ratio = m_speed / distance;

		newX = m_iCurrentScreenX + ratio * differenceInX;
		newY = m_iCurrentScreenY + ratio * differenceInY;
#endif

#if UseMovementType == 1
		//less intelligent way just utilising if statements
		if (abs(differenceInX) > m_speed) {
			if (goalX < m_iCurrentScreenX) {
				newX = m_iCurrentScreenX - m_speed;
			}
			else if (goalX > m_iCurrentScreenX) {
				newX = m_iCurrentScreenX + m_speed;
			}
		}
		else {
			newX = goalX;
		}
			
		if (abs(differenceInY) > m_speed) {
			if (goalY < m_iCurrentScreenY) {
				newY = m_iCurrentScreenY - m_speed;
			}
			else if (goalY > m_iCurrentScreenY) {
				newY = m_iCurrentScreenY + m_speed;
			}
		}
		else {
			newY = goalY;
		}
#endif

		// correcting coordinates if colliding
		checkTileMapCollisions(m_iCurrentScreenX, m_iCurrentScreenY, newX, newY);
	}

	// if distance is less than or equal to total speed, just jump to coords
	else {
		m_iCurrentScreenX = goalX;
		m_iCurrentScreenY = goalY;
	}
	
}

void CW3_SimpleEnemy::virtDraw()
{
#if showCollisionBoxes == 1
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff0000);
#endif

	renderHealthbar();
}

void CW3_SimpleEnemy::virtDoUpdate(int iCurrentTime)
{
	virtMove();
	virtAttack();
}

void CW3_SimpleEnemy::virtDie() {
	m_pGameEngine->deleteObjectFromArray(m_objectID);
	m_pGameEngine->getObjectOfType<CW3_Player>()->increaseScore(m_pointsValue);
}