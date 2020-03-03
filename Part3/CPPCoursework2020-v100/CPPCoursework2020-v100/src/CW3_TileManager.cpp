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
	
	unsigned int iColour = 0x319dad + (0x050500 * ((iMapX + iMapY + iMapValue) % 16));

	pSurface->drawRectangle(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		iColour); // Pixel colour
	



}