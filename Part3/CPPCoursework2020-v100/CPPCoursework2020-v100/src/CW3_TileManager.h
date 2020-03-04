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
	

};

