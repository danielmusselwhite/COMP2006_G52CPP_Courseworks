#include "header.h"

#include "CW3_Gun.h"
#include "Math.h"
#include "CW3_DebugHeaders.h"
#include "CW3_Bullet.h"

#define differenceInDegrees 22.5

CW3_GameObject* m_pWielder;
int rectangleColour;
int normalHeight, normalWidth;
SimpleImage image;
double shootAngle;

CW3_Gun::CW3_Gun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight) : 
	CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight){
	m_pWielder = wielder;

	rectangleColour = 0xff00ff;

	normalHeight = iHeight;
	normalWidth = iWidth;


	image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_east.png", true); // defaulting to looking in one direction
}

CW3_Gun::~CW3_Gun()
{
}

void CW3_Gun::virtDraw()
{
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY, getDrawWidth(), getDrawHeight(), 0, 0, image.getWidth(), image.getHeight());

}

void CW3_Gun::SnapToWielder() {

	int differenceInX = m_pWielder->getCurrentXCoordinate()+m_pWielder->getDrawWidth()/2 - m_pGameEngine->getCurrentMouseX();
	int differenceInY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight() / 2 - m_pGameEngine->getCurrentMouseY();

	shootAngle = atan2(differenceInX, differenceInY);
	double dAngle = shootAngle *(180.0 / 3.141592653589793238463);

	std::cout << dAngle << "\n";

	m_pGameEngine->lockForegroundForDrawing();

	// if we are looking north
	if (dAngle > -differenceInDegrees && dAngle <= differenceInDegrees) {
		shootAngle = 0;

		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalHeight;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate();// +m_pWielder->getDrawWidth() / 2;
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() - getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_north.png", true);
	}
	// if we are looking north east
	else if (dAngle > -differenceInDegrees * 3 && dAngle <= -differenceInDegrees) {
		//shootAngle = 45;

		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalWidth;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() - getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_northEast.png", true);
	}
	// if we are looking east
	else if (dAngle > -differenceInDegrees * 5 && dAngle <= -differenceInDegrees * 3) {
		//shootAngle = 90;

		m_iDrawWidth = normalWidth;
		m_iDrawHeight = normalHeight;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate();// +m_pWielder->getDrawHeight() / 2;

		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_east.png", true);
	}
	// if we are looking south east
	else if (dAngle > -differenceInDegrees * 7 && dAngle <= -differenceInDegrees * 5) {
		//shootAngle = 135;

		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalWidth;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_southEast.png", true);
	}
	// if we are looking south
	else if (dAngle > differenceInDegrees * 7 || dAngle <= -differenceInDegrees * 7) {
		//shootAngle = 180;

		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalHeight;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate();// +m_pWielder->getDrawWidth() / 2;
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_south.png", true);
	}
	// if we are looking south west
	else if (dAngle > differenceInDegrees * 5 && dAngle <= differenceInDegrees * 7) {
		//shootAngle = -135;


		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalWidth;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() - getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_southWest.png", true);
	}
	// if we are looking west
	else if (dAngle > differenceInDegrees * 3 && dAngle <= differenceInDegrees * 5) {
		//shootAngle = -90;

		m_iDrawWidth = normalWidth;
		m_iDrawHeight = normalHeight;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() - getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate();// +m_pWielder->getDrawHeight() / 2;


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_west.png", true);
	}
	// if we are looking north west
	else if (dAngle > differenceInDegrees && dAngle <= differenceInDegrees* 3) {
		//shootAngle = -45;

		m_iDrawHeight = normalWidth;
		m_iDrawWidth = normalWidth;

		m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate() - getDrawWidth();
		m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate() - getDrawHeight();


		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_northWest.png", true);
	}
	
	m_pGameEngine->unlockForegroundForDrawing();
}

void CW3_Gun::attack()
{
	m_pGameEngine->appendObjectToArray(new CW3_Bullet(m_iCurrentScreenX, m_iCurrentScreenY, m_pGameEngine, 10, 10, shootAngle));
}


void CW3_Gun::virtDoUpdate(int iCurrentTime)
{
	
	

	/*
	int x = m_pGameEngine->getCurrentMouseX() - m_iCurrentScreenX;
	int y = m_pGameEngine->getCurrentMouseY() - m_iCurrentScreenY;
	
	//rotator->setRotation(atan2(m_pGameEngine->getCurrentMouseX()-m_iCurrentScreenX, (m_pGameEngine->getCurrentMouseY() - m_iCurrentScreenY)));
	double dAngle =	atan2(x, y);
	if (x < 0)
		dAngle += M_PI;
	double hyp = sqrt(x*x + y * y);
	
	x = hyp * cos(dAngle);
	y = hyp * sin(dAngle);
	*/
	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}
