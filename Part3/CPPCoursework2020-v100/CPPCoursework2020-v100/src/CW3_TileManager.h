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

	void drawFloor1Tile(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawWallTopNorthTile(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawWallTopNorthEastTile(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void CW3_TileManager::drawWallTopNorthWestTile(BaseEngine* pEngine, int iMapX, int iMapY) const;

};

