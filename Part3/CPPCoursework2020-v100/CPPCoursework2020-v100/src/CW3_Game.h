#pragma once
#include "BaseEngine.h"
#include "CW3_TileManager.h"

class CW3_Game :
	public BaseEngine
{
public:
	CW3_Game();
	~CW3_Game();
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	int virtInitialiseObjects() override;

	CW3_TileManager * getTileManager();

	template <class objectType> std::vector<objectType> getObjectsOfType();
protected:
	CW3_TileManager *tm;

};

