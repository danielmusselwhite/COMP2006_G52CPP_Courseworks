#include "header.h"
#include "CW3_TileManager.h"
#include "ImageManager.h"

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
	SimpleImage image;

	switch (getMapValue(iMapX, iMapY)) {
	case 0:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_left.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 1:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_mid.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight()); 
		break;
	case 2:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_right.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 3:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_corner_left.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 4:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Floor\\floor_1.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());

		break;
	case 5:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_corner_right.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 6:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_corner_bottom_left.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 7:
		image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_top_mid.png", true);
		image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
		break;
	case 8:
			image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_corner_bottom_right.png", true);
			image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
			break;
	}

	

}

	
//left of the tilemap + (this tiles x index * width of each tile)
int CW3_TileManager::getTilesXCoordinates(int iMapX) const{
	return m_iBaseScreenX + (iMapX*getTileWidth());
}

//top of the tilemap + (this tiles y index * height of each tile)
int CW3_TileManager::getTilesYCoordinates(int iMapY) const {
	return m_iBaseScreenY + (iMapY*getTileHeight());
}



	