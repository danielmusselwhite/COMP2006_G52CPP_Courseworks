#include "header.h"

#include "CW3_Sword.h"
#include "Math.h"

CW3_GameObject* m_pWielder;
//CoordinateMappingRotate* rotator;

CW3_Sword::CW3_Sword(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight) : CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight) {
	//rotator = new CoordinateMappingRotate(0.0);
	m_pWielder = wielder;
}

CW3_Sword::~CW3_Sword()
{
}

void CW3_Sword::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xffff00);
}

void CW3_Sword::SnapToWielder() {
	m_iCurrentScreenX = m_pWielder->getCurrentXCoordinate();
	m_iCurrentScreenY = m_pWielder->getCurrentYCoordinate();
}

void CW3_Sword::virtDoUpdate(int iCurrentTime)
{
	//rotator->setRotation(atan2(m_pGameEngine->getCurrentMouseX()-m_iCurrentScreenX, (m_pGameEngine->getCurrentMouseY() - m_iCurrentScreenY)));

	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}
