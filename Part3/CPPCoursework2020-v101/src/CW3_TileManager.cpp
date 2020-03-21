#include "header.h"
#include "CW3_TileManager.h"
#include "ImageManager.h"
#include "CW3_DungeonTileMapCodes.h"
#include "CW3_DebugHeaders.h"
#include "CW3_Game.h"

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

	CW3_Game* pGameEngine = dynamic_cast<CW3_Game*>(pEngine); //checks its a subclass first

	int iMapValue = getMapValue(iMapX, iMapY);	// coordinate of the tile on the map

#if showCollisionBoxes is 1
//just kept to be useful in debugging collision boxes

	pSurface->drawRectangle(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		0x0093AF); // Pixel colour

#endif


	switch (getMapValue(iMapX, iMapY)) {

		//empty
#ifdef tileEmpty
	case tileEmpty:
		break;
#endif

		//playerSpawn
#ifdef tilePlayerSpawn
	case tilePlayerSpawn:
		CW3_TileManager::drawTileFloor1(pEngine, iMapX, iMapY);
		break;
#endif

		//enemySpawn
#ifdef tileBaseEnemySpawn
	case tileBaseEnemySpawn:
		CW3_TileManager::drawTileFloor1(pEngine, iMapX, iMapY);
		break;
#endif

		//floors
#ifdef tileFloor1
	case tileFloor1:

#if showCollisionBoxes is 1
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			0xFFFF00); // Pixel colour
#endif

		CW3_TileManager::drawTileFloor1(pEngine, iMapX, iMapY);

		break;
#endif

#ifdef puddleLight
	case puddleLight:
		CW3_TileManager::drawTilePuddleLight(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef puddleDark
	case puddleDark:
		CW3_TileManager::drawTilepuddleDark(pEngine, iMapX, iMapY);
		break;
#endif

		// wall tops


#ifdef tileWallTopNorthMid
	case tileWallTopNorthMid:
		CW3_TileManager::drawTileWallTopNorthMid(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopNorthEast
	case tileWallTopNorthEast:
		CW3_TileManager::drawTileWallTopNorthEast(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopNorthWest
	case tileWallTopNorthWest:
		CW3_TileManager::drawTileWallTopNorthWest(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopWest
	case tileWallTopWest:
		CW3_TileManager::drawTileWallTopWest(pEngine, iMapX, iMapY);
		break;
#endif


#ifdef tileWallTopEast
	case tileWallTopEast:
		CW3_TileManager::drawTileWallTopEast(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopSouthMid
	case tileWallTopSouthMid:
		CW3_TileManager::drawTileWallTopSouthMid(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopSouthEast
	case tileWallTopSouthEast:
		CW3_TileManager::drawTileWallSideEast(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileWallTopSouthEast(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallTopSouthWest
	case tileWallTopSouthWest:
		CW3_TileManager::drawTileWallSideWest(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileWallTopSouthWest(pEngine, iMapX, iMapY);
		break;
#endif




		// walls
#ifdef tileWallNorthMid
	case tileWallNorthMid:
		CW3_TileManager::drawTileWallMid(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallNorthEast
	case tileWallNorthEast:
		CW3_TileManager::drawTileWallEast(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallNorthWest
	case tileWallNorthWest:
		CW3_TileManager::drawTileWallWest(pEngine, iMapX, iMapY);
		break;
#endif


#ifdef tileWallSouthMid
	case tileWallSouthMid:
		CW3_TileManager::drawTileWallMid(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileWallTopSouthMid(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallSouthEast
	case tileWallSouthEast:
		CW3_TileManager::drawTileWallEast(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileWallTopSouthMid(pEngine, iMapX, iMapY);
		break;
#endif

#ifdef tileWallSouthWest
	case tileWallSouthWest:
		CW3_TileManager::drawTileWallWest(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileWallTopSouthMid(pEngine, iMapX, iMapY);
		break;
#endif





		//destroyables
#ifdef tileFloorWithCrate
	case tileFloorWithCrate:
		CW3_TileManager::drawTileFloor1(pEngine, iMapX, iMapY);
		CW3_TileManager::drawTileCrate(pEngine, iMapX, iMapY);
	}
#endif

}








//floor
void CW3_TileManager::drawTileFloor1(BaseEngine* pEngine, int iMapX, int iMapY) const {

	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Floor\\floor_1.png", true);
	image.setTransparencyColour(0x000000);

	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
	//image.renderImage(pEngine->getBackgroundSurface(), getTilesXCoordinates(iMapX), getTilesYCoordinates(iMapY), getTilesXCoordinates(iMapX), getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight());
}







void CW3_TileManager::drawTilePuddleLight(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Floor\\Puddle\\puddle_empty.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());

}

void CW3_TileManager::drawTilepuddleDark(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Floor\\Puddle\\puddle_full.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());

}

//wall edge
void CW3_TileManager::drawTileWallTopNorthMid(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_top_mid.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopNorthEast(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_top_right.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopNorthWest(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_top_left.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopWest(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_mid_left.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopEast(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_mid_right.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopSouthMid(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_bottom_mid.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopSouthEast(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_bottom_right.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallTopSouthWest(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_bottom_left.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallSideWest(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_bottom_left_corner.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallSideEast(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\Edges\\wall_side_bottom_right_corner.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

//walls
void CW3_TileManager::drawTileWallMid(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_mid.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());

}

void CW3_TileManager::drawTileWallEast(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_right.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

void CW3_TileManager::drawTileWallWest(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Tiles\\Wall\\wall_left.png", true);
	image.setTransparencyColour(0x000000);
	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());
}

//destroyable tiles
void CW3_TileManager::drawTileCrate(BaseEngine* pEngine, int iMapX, int iMapY) const {
	SimpleImage image;
	image = ImageManager::loadImage("images\\DungeonFrames\\Interactables\\Destroyables\\crate.png", true);
	image.setTransparencyColour(0x000000);

	image.renderImageBlit(pEngine, pEngine->getBackgroundSurface(), CW3_TileManager::getTilesXCoordinates(iMapX), CW3_TileManager::getTilesYCoordinates(iMapY), getTileWidth(), getTileHeight(), 0, 0, image.getWidth(), image.getHeight());

}



//left of the tilemap + (this tiles x index * width of each tile)
int CW3_TileManager::getTilesXCoordinates(int iMapX) const {
	return m_iBaseScreenX + (iMapX*getTileWidth());
}

//top of the tilemap + (this tiles y index * height of each tile)
int CW3_TileManager::getTilesYCoordinates(int iMapY) const {
	return m_iBaseScreenY + (iMapY*getTileHeight());
}

// works out the iMapX and iMapY based on the actual coordinates then gets value of tile at that index
int CW3_TileManager::getTileValueAtCoordinates(int iX, int iY) const {
	//tile index = x coordinate - the base position of the table, divided by size of each tile
	int iMapX = getTileXMapAtCoordinates(iX);
	//tile index = y coordinate - the base position of the table, divided by size of each tile
	int iMapY = getTileYMapAtCoordinates(iY);

	return getMapValue(iMapX, iMapY);
}

// works out the iMapX and iMapY based on the actual coordinates then gets value of tile at that index
int CW3_TileManager::getTileXMapAtCoordinates(int iX) const {
	//tile index = x coordinate - the base position of the table, divided by size of each tile
	return (iX - m_iBaseScreenX) / getTileWidth();
}

// works out the iMapX and iMapY based on the actual coordinates then gets value of tile at that index
int CW3_TileManager::getTileYMapAtCoordinates(int iY) const {
	//tile index = y coordinate - the base position of the table, divided by size of each tile
	return (iY - m_iBaseScreenY) / getTileHeight();
}

int CW3_TileManager::getBaseScreenX() const {
	return m_iBaseScreenX;
}

int CW3_TileManager::getBaseScreenY() const {
	return m_iBaseScreenY;
}