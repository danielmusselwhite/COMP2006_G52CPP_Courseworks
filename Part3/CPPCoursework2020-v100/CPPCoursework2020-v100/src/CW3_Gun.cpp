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
double dAngle;

CW3_Gun::~CW3_Gun()
{
}

void CW3_Gun::virtDraw()
{
	image.setTransparencyColour(0x000000);
	//image.renderImageBlit(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY, getDrawWidth(), getDrawHeight(), 0, 0, image.getWidth(), image.getHeight());
	image.renderImageApplyingMapping(m_pGameEngine, m_pGameEngine->getForegroundSurface(), getXCentre(), getYCentre(), image.getWidth(), image.getHeight(), this);
}

void CW3_Gun::SnapToWielder() {


	m_iCurrentScreenX = m_pWielder->getXCentre();
	m_iCurrentScreenY = m_pWielder->getYCentre();

}

void CW3_Gun::attack()
{
	m_pGameEngine->appendObjectToArray(new CW3_Bullet(m_iCurrentScreenX, m_iCurrentScreenY, m_pGameEngine, 10, 10, dAngle));
}


void CW3_Gun::virtDoUpdate(int iCurrentTime)
{
	//m_pGameEngine->lockForegroundForDrawing();
	//image.renderImageApplyingMapping(m_pGameEngine, m_pGameEngine->getForegroundSurface(), getXCentre(), getYCentre(), image.getWidth(), image.getHeight(), this);
	//m_pGameEngine->unlockForegroundForDrawing();
}

bool CW3_Gun::mapCoordinates(double & x, double & y, const SimpleImage & image)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	// Shift offset to the centre of the image, so we can rotate around centre
	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;


	int differenceInX = getXCentre() - m_pGameEngine->getCurrentMouseX();
	int differenceInY = getYCentre() - m_pGameEngine->getCurrentMouseY();

	// Rotate it
	double dAngle = atan(y / (x + 0.0001));
	if (x < 0)
		dAngle += M_PI;

	double hyp = ::sqrt(x*x + y * y);
	dAngle -= atan2(differenceInY, differenceInX);	// THIS IS THE IMPORTANT LINE, DECREASE THE DANGLE 

	std::cout << "Test" << dAngle << "\n";

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
