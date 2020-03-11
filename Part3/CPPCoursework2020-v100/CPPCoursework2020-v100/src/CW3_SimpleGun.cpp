#include "header.h"
#include "CW3_SimpleGun.h"


CW3_SimpleGun:: CW3_SimpleGun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int xScale, int yScale)
	: CW3_BaseGun(wielder, iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight, xScale, yScale) {
	m_bulletDamage = 10;
	m_bulletSpeed = 15;
	m_bulletSpread = 0.1;

	m_image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_west.png", true); // defaulting to looking in one direction
}

void CW3_SimpleGun::attack() {

}