#pragma once
#include "CW3_GameObject.h"
#include "CoordinateMapping.h"

extern CW3_GameObject* m_pWielder;
extern int normalHeight, normalWidth;
extern double dAngle;
extern SimpleImage image;

class CW3_Gun :
	public CW3_GameObject,
	public CoordinateMapping
{
public:

	CW3_Gun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, BaseEngine* pGameEngine, int iWidth, int iHeight) :
	CW3_GameObject(iStartXCoord, iStartYCoord, pGameEngine, iWidth, iHeight),
	rotator(0.0){
		m_pWielder = wielder;

		normalHeight = iHeight;
		normalWidth = iWidth;

		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_west.png", true); // defaulting to looking in one direction
	}
	~CW3_Gun();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override;

	// Most implementations will not change this, so just return true, but it allows colour modification if needed.
	virtual bool changePixelColour(int x, int y, int& colour, DrawingSurface* pTarget)
	{
		return colour != 0;
	}

	void SnapToWielder();

	void attack();

protected:
	CoordinateMappingRotate rotator;
};

