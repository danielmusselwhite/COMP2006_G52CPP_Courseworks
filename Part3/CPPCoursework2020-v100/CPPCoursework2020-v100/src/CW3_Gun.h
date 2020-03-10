#pragma once
#include "CW3_GameObject.h"
#include "CoordinateMapping.h"
#include "MappableImageObject.h"
#include "CW3_RotatingImage.h"

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

		//image = new CW3_RotatingImage(this, m_pGameEngine, "images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_east.png", getXCentre(), getYCentre(), getDrawWidth(), getDrawHeight());
		image = ImageManager::loadImage("images\\DungeonFrames\\Weapons\\Green Staff\\weapon_green_magic_staff_east.png", true); // defaulting to looking in one direction
	}
	~CW3_Gun();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override;

	void SnapToWielder();

	void attack();

protected:
	CoordinateMappingRotate rotator;
};

