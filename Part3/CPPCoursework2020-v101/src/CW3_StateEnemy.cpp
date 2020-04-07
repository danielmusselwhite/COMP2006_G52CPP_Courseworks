#include "header.h"
#include "CW3_StateEnemy.h"

CW3_StateEnemy::CW3_StateEnemy(int iStartXCoord, int iStartYCoord, BaseEngine * pEngine, int iWidth, int iHeight, int maxHealth, int currentHealth, int minDamage, int maxDamage, int speed, int pointsValue, int startState) : CW3_BaseEnemy(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, maxHealth, currentHealth, minDamage, maxDamage, speed, pointsValue) {
	//setting up state
	m_state = nullptr;
	switch (startState) {
	case 0:
		transitionToState(new IdleState());
		break;
	case 1:
		transitionToState(new AggressiveState());
		break;
	case 2:
		transitionToState(new PatrollingState());
		break;
	case 3:
		transitionToState(new ScaredState());
		break;
	default:
		transitionToState(new IdleState());
		break;
	}

}

CW3_StateEnemy::~CW3_StateEnemy()
{
}

void CW3_StateEnemy::transitionToState(State *state) {
	state->setContext(this, m_pGameEngine);
	std::cout << "\n" << state->getID() << "\n";
	if (m_state != nullptr)
		delete this->m_state;
	this->m_state = state;
	
}

void CW3_StateEnemy::virtAttack()
{
	// only do this if visible
	if (!isVisible())
		return;

	// for now there is only one player, so get the one at pos 0 in the vector, later maybe make it hostile to the closest if more players/friendlies are added
	CW3_Player* target = m_pGameEngine->getObjectOfType<CW3_Player>();

	int goalX = target->getCurrentXCoordinate();
	int goalY = target->getCurrentYCoordinate();
	double differenceInX = goalX - m_iCurrentScreenX;
	double differenceInY = goalY - m_iCurrentScreenY;
	double distance = sqrt((pow(differenceInX, 2)) + (pow(differenceInY, 2)));
}

void CW3_StateEnemy::virtMove()
{
	// only do this if visible
	if (!isVisible())
		return;


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

	newX = m_state->moveX(differenceInX, m_speed, goalX);
	newY = m_state->moveY(differenceInY, m_speed, goalY);

	checkTileMapCollisions(m_iCurrentScreenX, m_iCurrentScreenY, newX, newY);

	checkTargetCollisions(target);
}

void CW3_StateEnemy::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff0000);

	renderHealthbar();
}

void CW3_StateEnemy::virtDoUpdate(int iCurrentTime)
{
	// only do this if visible and not paused
	if (!isVisible() || m_isPaused)
		return;

	// if dead then die
	if (checkDeath()) {
		virtDie();
		return;
	}

	m_state->checkForStateTransition(m_pGameEngine->getObjectOfType<CW3_Player>());
	virtMove();
	virtAttack();
}

void CW3_StateEnemy::virtDie()
{
	m_pGameEngine->getObjectOfType<CW3_Player>()->increaseScore(m_pointsValue);
	m_pGameEngine->deleteObjectFromArray(m_objectID);
}







// STATE

int State::moveX(double differenceInX, int m_speed, int goalX) {
	return m_context->getCurrentXCoordinate();
}

int State::moveY(double differenceInY, int m_speed, int goalY) {
	return m_context->getCurrentYCoordinate();
}

// IDLE STATE

void IdleState::checkForStateTransition(CW3_Player* target) {

	int drawWidth = m_context->getDrawWidth();
	int drawHeight = m_context->getDrawHeight();

	int xCentre = m_context->getCurrentXCoordinate() + drawWidth / 2;
	int yCentre = m_context->getCurrentYCoordinate() + drawHeight / 2;

	int xLeftBound = xCentre - drawWidth * 2;
	int xRightBound = xCentre + drawWidth * 2;
	int yTopBound = yCentre - drawHeight * 2;
	int yBottomBound = yCentre + drawHeight * 2;

	int targetXLeft = target->getCurrentXCoordinate();
	int targetYTop = target->getCurrentYCoordinate();
	int targetXRight = target->getCurrentXCoordinate() + target->getDrawWidth();
	int targetYBottom = target->getCurrentYCoordinate() + target->getDrawHeight();

	// if target is within the x and y bounds
	if (targetXLeft <xRightBound && targetXRight > xLeftBound && targetYTop <yBottomBound && targetYBottom > yTopBound) {
		//if enemy is above 50% health be aggressive
		if (m_context->getHealthRatio() > 0.5) {
			m_context->transitionToState(new AggressiveState());
			return;
		}	
		//else get scared
		else {
			m_context->transitionToState(new ScaredState());
			return;
		}
	}

}

// AGGRESSIVE STATE

int AggressiveState::moveX(double differenceInX, int m_speed, int goalX) {
	int currentX = m_context->getCurrentXCoordinate();
	int newX = currentX; // newX position (defaulted to current)

	if (abs(differenceInX) > m_speed) {
		if (goalX < currentX) {
			newX = currentX - m_speed;
		}
		else if (goalX > currentX) {
			newX = currentX + m_speed;
		}
	}
	else {
		newX = goalX;
	}

	return newX;
}

int AggressiveState::moveY(double differenceInY, int m_speed, int goalY) {
	int currentY = m_context->getCurrentYCoordinate();
	int newY = currentY; // newY position (defaulted to current)

	//less intelligent way just utilising if statements
	if (abs(differenceInY) > m_speed) {
		if (goalY < currentY) {
			newY = currentY - m_speed;
		}
		else if (goalY > currentY) {
			newY = currentY + m_speed;
		}
	}
	else {
		newY = goalY;
	}

	return newY;
}

void AggressiveState::checkForStateTransition(CW3_Player* target) {
	int drawWidth = m_context->getDrawWidth();
	int drawHeight = m_context->getDrawHeight();

	int xCentre = m_context->getCurrentXCoordinate() + drawWidth / 2;
	int yCentre = m_context->getCurrentYCoordinate() + drawHeight / 2;

	int xLeftBound = xCentre - drawWidth * 3;
	int xRightBound = xCentre + drawWidth * 3;
	int yTopBound = yCentre - drawHeight * 3;
	int yBottomBound = yCentre + drawHeight * 3;

	int targetXLeft = target->getCurrentXCoordinate();
	int targetYTop = target->getCurrentYCoordinate();
	int targetXRight = target->getCurrentXCoordinate() + target->getDrawWidth();
	int targetYBottom = target->getCurrentYCoordinate() + target->getDrawHeight();

	// if target is not within the x and y bounds, start patroling making sure player doesn't re-enter
	if (!(targetXLeft <xRightBound && targetXRight > xLeftBound && targetYTop <yBottomBound && targetYBottom > yTopBound)) {
		//if enemy is above 50% health start patrolling
		if (m_context->getHealthRatio() > 0.5) {
			m_context->transitionToState(new PatrollingState());
			return;
		}
	}

	//if enemy is below 50% health get scared
	if (m_context->getHealthRatio() <= 0.5) {
		m_context->transitionToState(new ScaredState());
		return;
	}
		
}

// PATROLLING STATE

int PatrollingState::moveX(double differenceInX, int m_speed, int goalX) {
	int currentX = m_context->getCurrentXCoordinate();

	return currentX + (m_speed / 2)*m_xDirection;
}

int PatrollingState::moveY(double differenceInY, int m_speed, int goalY) {
	int currentY = m_context->getCurrentYCoordinate();
	
	return currentY + (m_speed / 2)*m_yDirection;
}

void PatrollingState::checkForStateTransition(CW3_Player* target) {
	if (m_timeLimit == -1)
		m_timeLimit = m_pGameEngine->getRawTime() + 5000;

	//if player reenters circle check whether to get aggressive or scared
	int drawWidth = m_context->getDrawWidth();
	int drawHeight = m_context->getDrawHeight();

	int xCentre = m_context->getCurrentXCoordinate() + drawWidth / 2;
	int yCentre = m_context->getCurrentYCoordinate() + drawHeight / 2;

	int xLeftBound = xCentre - drawWidth * 2;
	int xRightBound = xCentre + drawWidth * 2;
	int yTopBound = yCentre - drawHeight * 2;
	int yBottomBound = yCentre + drawHeight * 2;

	int targetXLeft = target->getCurrentXCoordinate();
	int targetYTop = target->getCurrentYCoordinate();
	int targetXRight = target->getCurrentXCoordinate() + target->getDrawWidth();
	int targetYBottom = target->getCurrentYCoordinate() + target->getDrawHeight();

	// if target is within the x and y bounds
	if (targetXLeft <xRightBound && targetXRight > xLeftBound && targetYTop <yBottomBound && targetYBottom > yTopBound) {
		//if enemy is above 50% health be aggressive
		if (m_context->getHealthRatio() > 0.5) {
			m_context->transitionToState(new AggressiveState());
			return;
		}

		// get scared if has less than 50% health
		else {
			m_context->transitionToState(new ScaredState());
			return;
		}


	}

	
	//if time limit has been exceeded go back to idle'
	if (m_pGameEngine->getRawTime() >= m_timeLimit) {
		m_context->transitionToState(new IdleState());
		return;
	}

	if (m_movingTime < m_pGameEngine->getRawTime()) {
		m_movingTime = m_pGameEngine->getRawTime() + (rand() % 900) + 100;
		m_xDirection = rand() % 3 - 1;
		m_yDirection = rand() % 3 - 1;
	}
		
		
}

// SCARED STATE

int ScaredState::moveX(double differenceInX, int m_speed, int goalX) {
	int currentX = m_context->getCurrentXCoordinate();
	int newX = currentX; // newX position (defaulted to current)

	// move in opposite direction to the player
	if (abs(differenceInX) > m_speed) {
		if (goalX < currentX) {
			newX = currentX + m_speed;
		}
		else if (goalX > currentX) {
			newX = currentX - m_speed;
		}
	}
	else {
		newX = goalX;
	}
	
	return newX;
}

int ScaredState::moveY(double differenceInY, int m_speed, int goalY) {
	int currentY = m_context->getCurrentYCoordinate();
	int newY = currentY; // newY position (defaulted to current)

	//move in opposite direction to the player
	if (abs(differenceInY) > m_speed) {
		if (goalY < currentY) {
			newY = currentY + m_speed;
		}
		else if (goalY > currentY) {
			newY = currentY - m_speed;
		}
	}
	else {
		newY = goalY;
	}

	return newY;
}

void ScaredState::checkForStateTransition(CW3_Player* target) {

	int drawWidth = m_context->getDrawWidth();
	int drawHeight = m_context->getDrawHeight();

	int xCentre = m_context->getCurrentXCoordinate() + drawWidth / 2;
	int yCentre = m_context->getCurrentYCoordinate() + drawHeight / 2;

	int xLeftBound = xCentre - drawWidth * 5;
	int xRightBound = xCentre + drawWidth * 5;
	int yTopBound = yCentre - drawHeight * 5;
	int yBottomBound = yCentre + drawHeight * 5;

	int targetXLeft = target->getCurrentXCoordinate();
	int targetYTop = target->getCurrentYCoordinate();
	int targetXRight = target->getCurrentXCoordinate() + target->getDrawWidth();
	int targetYBottom = target->getCurrentYCoordinate() + target->getDrawHeight();

	// if target is not within the x and y bounds, start patroling making sure player doesn't re-enter
	if (!(targetXLeft <xRightBound && targetXRight > xLeftBound && targetYTop <yBottomBound && targetYBottom > yTopBound)) {
		m_context->transitionToState(new PatrollingState());
		return;
	}

}