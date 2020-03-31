#pragma once
#include "TileManager.h"

class CW3_TileManager :
	public TileManager
{
public:
	SimpleImage m_crate;
	SimpleImage m_wallWest;
	SimpleImage m_wallEast;
	SimpleImage m_wallMid;
	SimpleImage m_wallSideEast;
	SimpleImage m_wallSideWest;
	SimpleImage m_wallTopSouthWest;
	SimpleImage m_wallTopSouthEast;
	SimpleImage m_wallTopSouthMid;

	SimpleImage m_wallTopEast;
	SimpleImage m_wallTopWest;
	SimpleImage m_wallTopNorthWest;
	SimpleImage m_wallTopNorthEast;
	SimpleImage m_wallTopNorthMid;
	SimpleImage m_floor1;
	SimpleImage m_floorPuddleLight;
	SimpleImage m_floorPuddleDark;

public:
	//constructor/deconstructor
	CW3_TileManager(int iTileHeight, int iTileWidth, int iMapHeight, int iMapWidth);
	~CW3_TileManager();

	//helper functions
	int getTilesXCoordinates(int iMapX) const;
	int getTilesYCoordinates(int iMapX) const;

	int getTileValueAtCoordinates(int iX, int iY) const;

	int getTileXMapAtCoordinates(int iX) const;
	int getTileYMapAtCoordinates(int iY) const;

	int getBaseScreenX() const;
	int getBaseScreenY() const;

	//functions for drawing different tiles
	void drawTileFloor1(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTilePuddleLight(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTilepuddleDark(BaseEngine* pEngine, int iMapX, int iMapY) const;


	void drawTileWallTopNorthMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopNorthEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopNorthWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallTopSouthWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallSideWest(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallSideEast(BaseEngine* pEngine, int iMapX, int iMapY) const;

	void drawTileWallMid(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallEast(BaseEngine* pEngine, int iMapX, int iMapY) const;
	void drawTileWallWest(BaseEngine* pEngine, int iMapX, int iMapY) const;

	void drawTileCrate(BaseEngine* pEngine, int iMapX, int iMapY) const;

	//overriding parent virt functions
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;


	std::vector<std::vector<int>> getState() {
		std::vector<std::vector<int>> state;

		for (int y = 0; y < m_iMapHeight; y++) {
			std::vector<int> row;

			for (int x = 0; x < m_iMapWidth; x++) {
				row.push_back(getMapValue(x, y));
			}
			state.push_back(row);
		}

		return state;
	}
};

