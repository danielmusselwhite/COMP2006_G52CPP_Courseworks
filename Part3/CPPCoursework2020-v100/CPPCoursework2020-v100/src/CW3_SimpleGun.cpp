#include "header.h"
#include "CW3_SimpleGun.h"
#include "CW3_SimpleBullet.h"

CW3_SimpleGun:: CW3_SimpleGun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int xScale, int yScale)
	: CW3_BaseGun(wielder, iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, xScale, yScale) {
	m_bulletDamage = 10;
	m_bulletSpeed = 15;
	m_bulletSpread = 0.1;
	m_image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Staffs\\weapon_green_magic_staff_west.png", true); // defaulting to looking in one direction
}

void CW3_SimpleGun::attack() {

	int differenceInX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth() / 2 - m_pGameEngine->getCurrentMouseX();
	int differenceInY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight() / 2 - m_pGameEngine->getCurrentMouseY();

	double shootAngle = atan2(differenceInX, differenceInY);


	int endOfStaffX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth() / 2;
	//endOfStaffX += cos(shootAngle) * m_normalWidth / 2;
	int endOfStaffY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight() / 2;
	//endOfStaffY += sin(shootAngle) * m_normalHeight / 2;

	m_pGameEngine->drawableObjectsChanged();
	m_pGameEngine->appendObjectToArray(new CW3_SimpleBullet(endOfStaffX, endOfStaffY, m_pGameEngine, 10, 10, shootAngle));
}