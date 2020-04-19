#include "header.h"
#include "CW3_SimpleGun.h"
#include "CW3_SimpleBullet.h"
//#include "CW3_SimpleBulletPolymorphic.h"

CW3_SimpleGun::CW3_SimpleGun(int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int xScale, int yScale)
	: CW3_BaseGun(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, xScale, yScale) {
	m_bulletDamage = 10;
	m_bulletSpeed = 15;
	m_bulletSpread = 0.1;
	m_image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Staffs\\weapon_green_magic_staff_west.png", true);
}

void CW3_SimpleGun::attack() {

	int differenceInX = m_xCentre - m_pGameEngine->getCurrentMouseX();
	int differenceInY = m_yCentre - m_pGameEngine->getCurrentMouseY();

	double shootAngle = atan2(differenceInX, differenceInY);

	m_pGameEngine->drawableObjectsChanged();
	m_pGameEngine->appendObjectToArray(new CW3_SimpleBullet(m_xCentre, m_yCentre, m_pGameEngine, 10, 10, shootAngle));
}