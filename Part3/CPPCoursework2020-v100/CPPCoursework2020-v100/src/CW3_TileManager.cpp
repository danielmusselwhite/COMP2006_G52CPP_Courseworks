#include "header.h"
#include "CW3_TileManager.h"

// constructor
CW3_TileManager::CW3_TileManager(int iTileHeight, int iTileWidth, int iMapHeight, int iMapWidth) : TileManager(iTileHeight, iTileWidth, iMapHeight, iMapWidth) {

}

// deconstructor
CW3_TileManager::~CW3_TileManager() {

}

// overriding function for drawing the tile map
void CW3_TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	
	int iMapValue = getMapValue(iMapX, iMapY);	// coordinate of the tile on the map
	
	unsigned int iColour = 0x319dad + (0x010100 * ((iMapX + iMapY + iMapValue) % 16));
	/*
	pSurface->drawRectangle(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		iColour); // Pixel colour
	*/

	switch (getMapValue(iMapX, iMapY)) {
	case 0:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0x319dad); // Pixel colour
		break;
	case 1:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0xff0000); // Pixel colour
		break;
	case 2:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0x00ff00); // Pixel colour
		break;
	case 3:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0x0000ff); // Pixel colour
		break;
	case 4:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0xffff00); // Pixel colour
		break;
	case 5:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0xffffff); // Pixel colour
		break;
	case 6:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0x00ffff); // Pixel colour
		break;
	case 7:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0xff00ff); // Pixel colour
		break;
	case 8:
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0x000000); // Pixel colour
		break;
	}



}