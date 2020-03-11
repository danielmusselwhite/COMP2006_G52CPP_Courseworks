#include "header.h"

#include "CW3_Gun.h"
#include "Math.h"
#include "CW3_DebugHeaders.h"
#include "CW3_Bullet.h"

#include "CW3_DebugHeaders.h"

#define differenceInDegrees 22.5

CW3_Gun::~CW3_Gun()
{ 
}

void CW3_Gun::virtDraw()
{
#if showCollisionBoxes == 1
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - 1, m_iCurrentScreenY - 1,
		m_iCurrentScreenX + m_iDrawWidth +1 ,
		m_iCurrentScreenY + m_iDrawHeight + 1,
		0xAA22AA);
#endif

	image.setTransparencyColour(0x000000);

	image.renderImageApplyingMapping(m_pGameEngine, m_pGameEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth()*2, image.getHeight()*2, this);

}

void CW3_Gun::SnapToWielder() {

	m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate();
	m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate();

}

void CW3_Gun::attack()
{
	m_pGameEngine->drawableObjectsChanged();
	m_pGameEngine->appendObjectToArray(new CW3_Bullet(getXCentre(), getYCentre(), m_pGameEngine, 10, 10, shootAngle));


}


void CW3_Gun::virtDoUpdate(int iCurrentTime)
{
	int differenceInX = m_pWielder->getCurrentXCoordinate() + m_pWielder->getDrawWidth() / 2 - m_pGameEngine->getCurrentMouseX();
	int differenceInY = m_pWielder->getCurrentYCoordinate() + m_pWielder->getDrawHeight() / 2 - m_pGameEngine->getCurrentMouseY();

	shootAngle = atan2(differenceInX, differenceInY);
}

bool CW3_Gun::mapCoordinates(double & x, double & y, const SimpleImage & image)
{

	//doubling its size
	x /= 2;
	y /= 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	// Shift offset to the centre of the image, so we can rotate around centre
	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;


	int differenceInX = m_iCurrentScreenX - m_pGameEngine->getCurrentMouseX();
	int differenceInY = m_iCurrentScreenY - m_pGameEngine->getCurrentMouseY();

	// Rotate it
	double dAngle = atan(y / (x + 0.0001));
	if (x < 0)
		dAngle += M_PI;

	double hyp = ::sqrt(x*x + y * y);
	dAngle -= atan2(differenceInY, differenceInX);	// THIS IS THE IMPORTANT LINE, DECREASE THE DANGLE 

	//std::cout << "Test" << dAngle << "\n";

	x = hyp * ::cos(dAngle);
	y = hyp * ::sin(dAngle);

	// Shift offset back to the corner
	x += image.getWidth() / 2;
	y += image.getHeight() / 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	return true;

}
