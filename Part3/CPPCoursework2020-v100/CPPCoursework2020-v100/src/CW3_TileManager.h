#pragma once
#include "TileManager.h"

class CW3_TileManager : public TileManager
{
public:
	CW3_TileManager(int iTileHeight, int iTileWidth, int iMapHeight, int iMapWidth);
	~CW3_TileManager();

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

	int getTilesXCoordinates(int iMapX) const;
	int getTilesYCoordinates(int iMapX) const;

	void drawTileFloor1(BaseEngine* pEngine, int iMapX, int iMapY) const;

	void drawTileWallTopNorthMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopNorthEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopNorthWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthWest(BaseEngine* pEngine, int iMapX, int iMapY) const;

	void drawTileWallMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallWest(BaseEngine* pEngine, int iMapX, int iMapY) const;

	//void drawWallTopNorthMidTile(BaseEngine* pEngine, int iMapX, int iMapY) const;
	//void drawWallTopNorthEastTile(BaseEngine* pEngine, int iMapX, int iMapY) const;
	//void CW3_TileManager::drawWallTopNorthWestTile(BaseEngine* pEngine, int iMapX, int iMapY) const;

};

