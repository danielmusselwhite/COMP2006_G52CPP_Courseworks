#pragma once
#include "CW3_GameObject.h"
#include "CoordinateMapping.h"
#include "ImageManager.h"
class CW3_RotatingImage : public CW3_GameObject
{
public:
	// Constructors
	CW3_RotatingImage(CoordinateMapping* pMapping, BaseEngine* pEngine, std::string strURL, int iStartXCoord, int iStartYCoord, int iWidth, int iHeight, bool useTopLeftFor00 = true, bool bVisible = true)
		: CW3_GameObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight)
		, m_pMapping(pMapping)
		, image(ImageManager::get()->getImagebyURL(strURL, true, true))
	{

	}

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw()
	{
		if (isVisible())
		{
			image.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight,
				m_pMapping);
		}
	}

	// Set the transparency colour
	void setTransparencyColour(int colour) { image.setTransparencyColour(colour); }

	// Retrieve the colour of a pixel - primarily used so we can get pixel 0,0 to set the transparency
	int getPixelColour(int x, int y) { return image.getPixelColour(x, y); }

	// Return the width of the loaded image
	int getImageWidth() { return image.getWidth(); }

	// Return the height of the loaded image
	int getImageHeight() { return image.getHeight(); }

	SimpleImage getImage() {
		return image;
	}

protected:
	CoordinateMapping* m_pMapping;

	// We use an image object just in case it is wanted by a subclass (Image2 is a subclass of SimpleImage), but 
	// we could use a SimpleImage for the purposes of this class itself, so treat this as a SimpleImage object
	// if Image2 confuses you
	SimpleImage image;
};

