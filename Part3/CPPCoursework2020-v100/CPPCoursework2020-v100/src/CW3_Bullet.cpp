#include "header.h"

#include "CW3_Bullet.h"
#include "Math.h"

CW3_Bullet::CW3_Bullet(int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight, double angleRadians) :
	CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight) {
	m_AngleRadians = angleRadians;
	m_bulletSpeed = 3;
}

CW3_Bullet::~CW3_Bullet()
{
}

void CW3_Bullet::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xffff00);
}

void CW3_Bullet::virtDoUpdate(int iCurrentTime)
{
	 m_iCurrentScreenY += cos(m_AngleRadians) * -m_bulletSpeed;
	 m_iCurrentScreenX += sin(m_AngleRadians) * -m_bulletSpeed;
}
