#pragma once
#include "CW3_Game.h"
#include "CW3_GameObject.h"
#include "CoordinateMapping.h"

class CW3_BaseGun :
	public CoordinateMapping
{
protected:
	//member variables
	CW3_GameObject* m_pWielder;
	int m_normalHeight, m_normalWidth;
	double m_dAngle;
	SimpleImage m_image;
	CoordinateMappingRotate m_rotator;
	int m_bulletDamage;
	int m_bulletSpeed;
	double m_bulletSpread;
	int m_xScale;
	int m_yScale;
	CW3_Game* m_pGameEngine;

public:
	//constructor
	CW3_BaseGun(CW3_GameObject* wielder, int iStartXCoord, int iStartYCoord, CW3_Game* pGameEngine, int iWidth, int iHeight, int xScale, int yScale) :
		m_rotator(0.0) {
		m_pWielder = wielder;

		m_normalHeight = iHeight;
		m_normalWidth = iWidth;

		m_xScale = xScale;
		m_yScale = yScale;

		m_pGameEngine = pGameEngine;
	}

	// virtual methods that must be overwritten
	virtual void attack() = 0;

	// overriding forced virtual function
	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {

		//doubling its size
		x /= m_xScale;
		y /= m_yScale;

		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;

		// Shift offset to the centre of the image, so we can rotate around centre
		x -= image.getWidth() / 2;
		y -= image.getHeight() / 2;


		int differenceInX = m_pWielder->getCurrentXCoordinate() - m_pGameEngine->getCurrentMouseX();
		int differenceInY = m_pWielder->getCurrentYCoordinate() - m_pGameEngine->getCurrentMouseY();

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

	SimpleImage& getImage() {
		return m_image;
	}
};

