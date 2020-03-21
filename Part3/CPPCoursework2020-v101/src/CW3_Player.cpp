#include "header.h"
#include "CW3_Player.h"
#include "BaseEngine.h"
#include "CW3_Game.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_DebugHeaders.h"
#include "CW3_SimpleGun.h"

CW3_Player::CW3_Player(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int crawlSpeed, int walkSpeed, int runSpeed) : CW3_LivingGameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, maxHealth) {
	m_walkSpeed = walkSpeed;
	m_runSpeed = runSpeed;
	m_crawlSpeed = crawlSpeed;

	m_pGun = new CW3_SimpleGun(this, iStartXCoord, iStartYCoord, m_pGameEngine, iWidth, iHeight, 2, 2);

	// setting up left anim
	std::vector<std::pair<SimpleImage, int>> leftAnimPairs;
	leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Left\\player_left_idle_anim_f0.png", true), 150));
	leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Left\\player_left_idle_anim_f1.png", true), 150));
	leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Left\\player_left_idle_anim_f2.png", true), 150));
	leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Left\\player_left_idle_anim_f3.png", true), 150));
	m_LeftAnim = new CW3_AnimatedImage(leftAnimPairs);

	// setting up right anim
	std::vector<std::pair<SimpleImage, int>> rightAnimPairs;
	rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Right\\player_right_idle_anim_f0.png", true), 150));
	rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Right\\player_right_idle_anim_f1.png", true), 150));
	rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Right\\player_right_idle_anim_f2.png", true), 150));
	rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Players\\myWizard\\Idle\\Right\\player_right_idle_anim_f3.png", true), 150));

	m_RightAnim = new CW3_AnimatedImage(rightAnimPairs);

	m_Anim = m_LeftAnim;
}

CW3_Player::~CW3_Player() {
	delete m_RightAnim;
	delete m_LeftAnim;
}

void CW3_Player::virtDraw()
{
	
	
#if showCollisionBoxes == 1
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
#endif

	renderHealthbar();

	m_Anim->renderCurrentFrame(m_pGameEngine, m_pGameEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight, 0, 0, m_Anim->getCurrentFrame().getWidth(), m_Anim->getCurrentFrame().getHeight());

	m_pGun->getImage().renderImageApplyingMapping(m_pGameEngine, m_pGameEngine->getForegroundSurface(), m_iCurrentScreenX -m_iDrawWidth /16, m_iCurrentScreenY+m_iDrawHeight/8, m_pGun->getImage().getWidth() * 2, m_pGun->getImage().getHeight() * 2, m_pGun);
}


void CW3_Player::virtDoUpdate(int iCurrentTime)
{

	// handling player movement
	{

		int newTilesValue, newTilesValue1, newTilesValue2; //value of tile we are trying to move to
		int newYCoordinate, newXCoordinate; //coordinate we are trying to move to
		int newTilesBounds; //if we are at a floor tiles edge/boundary to a tile you cannot pass (i.e. physical tile such as wall) this is the index of the tile we cannot pass ( limit we cannot move beyond)

		// if shift key is pressed change to run speed
		if (getEngine()->isKeyPressed(SDLK_LSHIFT)) {
			m_speed = m_runSpeed;
		}
		// else if control key is pressed change to crawl speed
		else if (getEngine()->isKeyPressed(SDLK_LCTRL)) {
			m_speed = m_crawlSpeed;
		}
		// else use default walk speed
		else {
			m_speed = m_walkSpeed;
		}


		// Change position if player presses a key
		if (getEngine()->isKeyPressed(SDLK_UP) || getEngine()->isKeyPressed(SDLK_w)) {

			//new coordinate we want to move to is the current position increased by speed
			newYCoordinate = m_iCurrentScreenY - m_speed;

			// if this is new position is a valid tile position..
			if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, newYCoordinate)) {

				// .. store that tiles value and ..
				newTilesValue1 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate);	//top left
				newTilesValue2 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX + m_iDrawWidth - 1, newYCoordinate); //top right

//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
if (50 > newTilesValue1 && newTilesValue1 >= 0 && 50 > newTilesValue2 && newTilesValue2 >= 0) {
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
		if (getEngine()->isKeyPressed(SDLK_DOWN) || getEngine()->isKeyPressed(SDLK_s)) {

			//new coordinate we want to move to is the current position then increased by speed
			newYCoordinate = m_iCurrentScreenY + m_speed;

			// if this is new position + player height (as the bottom of the player is the limit) is a valid tile position..
			if (m_pGameEngine->getTileManager()->isValidTilePosition(m_iCurrentScreenX, newYCoordinate + m_iDrawHeight)) {
				// .. store that tiles value and ..
				newTilesValue1 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX, newYCoordinate + m_iDrawHeight); //bottom left
				newTilesValue2 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(m_iCurrentScreenX + m_iDrawWidth - 1, newYCoordinate + m_iDrawHeight); //bottom right

				//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
				if (50 > newTilesValue1 && newTilesValue1 >= 0 && 50 > newTilesValue2 && newTilesValue2 >= 0) {
					//.. move the player to their new coordinate
					m_iCurrentScreenY = newYCoordinate;
				}
				//..else this a tile with a physical boundary..
				else {
					// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to -1 as the limit is the top of the tile
					newTilesBounds = m_pGameEngine->getTileManager()->getTileYMapAtCoordinates(newYCoordinate + m_iDrawHeight) - 1;
					// snap to the top of the tile we cannot move past (Coordinate of start of tilemap + height of each tile * index of tile limit
					m_iCurrentScreenY = (m_pGameEngine->getTileManager()->getBaseScreenY()) + ((m_pGameEngine->getTileManager()->getTileHeight())) * newTilesBounds;
				}

			}

		}

		if (getEngine()->isKeyPressed(SDLK_LEFT) || getEngine()->isKeyPressed(SDLK_a)) {
			//new coordinate we want to move to is the current position then increased by speed
			newXCoordinate = m_iCurrentScreenX - m_speed;

			// if this is new position is a valid tile position..
			if (m_pGameEngine->getTileManager()->isValidTilePosition(newXCoordinate, m_iCurrentScreenY)) {
				// .. store that tiles value and ..
				newTilesValue1 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate, m_iCurrentScreenY); //top left
				newTilesValue2 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate, m_iCurrentScreenY + m_iDrawHeight - 1); //bottom left

				//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
				if (50 > newTilesValue1 && newTilesValue1 >= 0 && 50 > newTilesValue2 && newTilesValue2 >= 0) {
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

		if (getEngine()->isKeyPressed(SDLK_RIGHT) || getEngine()->isKeyPressed(SDLK_d)) {
			//new coordinate we want to move to is the current position then increased by speed
			newXCoordinate = m_iCurrentScreenX + m_speed;

			// if this is new position + player width (as the right of the player is the limit) is a valid tile position..
			if (m_pGameEngine->getTileManager()->isValidTilePosition(newXCoordinate + m_iDrawWidth, m_iCurrentScreenY)) {
				// .. store that tiles value and ..
				newTilesValue1 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate + m_iDrawWidth, m_iCurrentScreenY); // top right
				newTilesValue2 = m_pGameEngine->getTileManager()->getTileValueAtCoordinates(newXCoordinate + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight - 1); // bottom right

				//.. if it has a value within the 0-50 partition for floor tiles (tiles player can walk on)..
				if (50 > newTilesValue1 && newTilesValue1 >= 0 && 50 > newTilesValue2 && newTilesValue2 >= 0) {
					//.. move the player to their new coordinate
					m_iCurrentScreenX = newXCoordinate;
				}
				//..else this is a tile with a physical boundary..
				else {
					// index of the tile we do not want to move past = the index of tile at coordinate we cannot move to +1 as the limit is the left of the tile
					newTilesBounds = m_pGameEngine->getTileManager()->getTileXMapAtCoordinates(newXCoordinate + m_iDrawWidth) - 1;
					// snap to the left of the tile we cannot move past (Coordinate of start of tilemap + width of each tile * index of tile limit
					m_iCurrentScreenX = (m_pGameEngine->getTileManager()->getBaseScreenX()) + ((m_pGameEngine->getTileManager()->getTileWidth())) * newTilesBounds;
				}

			}
		}
	}

	// handling players looking direction
	{
		m_pGameEngine->getCurrentMouseX() < m_iCurrentScreenX + m_iDrawWidth / 2 ? m_Anim = m_LeftAnim : m_Anim = m_RightAnim;
	}

	// handling invulnerablity
	{
		// if the player is invulnerable
		if (m_invuln) {
			// if the invulnerable timer has been exceeded make player damageable again
			if (m_pGameEngine->getRawTime() > m_invulnTimer)
				m_invuln = false;
		}
	}
	
		


	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}

void CW3_Player::shootGun()
{
	m_pGun->attack();
}

void CW3_Player::virtDie() {
	std::cout << "Player is dead\n";
	//m_pGameEngine->deleteObjectFromArray(m_objectID);
}

void CW3_Player::increaseScore(int points) {
	m_score += points;
}
