#pragma once
#include "BaseEngine.h"
#include "MyTileManager.h"

class MyDemoA :
	public BaseEngine
{

public:
	MyDemoA();
	~MyDemoA();
	void virtSetupBackgroundBuffer() override; // overrides virt function of same name in base class
	void virtMouseDown(int iButton, int iX, int iY) override; // overrides virt function of same name in base class
	void virtKeyDown(int iKeyCode) override;
protected:
	MyTileManager tm;
public:
	int virtInitialiseObjects();
};

