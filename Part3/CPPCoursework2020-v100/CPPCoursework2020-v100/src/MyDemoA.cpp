#include "header.h"
#include "MyDemoA.h"
#include "ImageManager.h"
#include "MyObjectA.h"

// hex colour: 0xrrggbb
#define turqoise 0x13d4a7
#define duckEgg 0x319dad
#define munsell 0x0093AF
#define royalBlue 0x3747ad
#define sandyYellow 0xadb058
#define seaFoamGreen 0x9FE2BF
#define seaGreen 0x2E8B57
#define teal 0x008080
#define red 0xFF0000

bool returnPressed;

// Constructor
MyDemoA::MyDemoA() {
	
}

// Deconstructor
MyDemoA::~MyDemoA() {

}


// function called whenever program needs to redraw the background
void MyDemoA::virtSetupBackgroundBuffer()
{
	returnPressed = false;

	// function for filling background with a solid colour
	fillBackground(turqoise);

	
	/*
	drawing random dots

	//for each x coordinate..
	for (int iX = 0; iX < getWindowWidth(); iX++)
		//.. for each y coordinate..
		for (int iY = 0; iY < this->getWindowHeight(); iY++)
			//.. generate a random number and modulo it with 100..
			switch (rand() % 100)
			{
			//.. if it results in a 0, 1, 2, or 3, draw a spot with the specified colour; if not don't draw a spot. (1/100 chance of a specific coloured spot, 1/25 chance of their being a spot)
			case 0: setBackgroundPixel(iX, iY, duckEgg); break;
			case 1: setBackgroundPixel(iX, iY, munsell); break;
			case 2: setBackgroundPixel(iX, iY, royalBlue); break;
			case 3: setBackgroundPixel(iX, iY, sandyYellow); break;
			case 4: setBackgroundPixel(iX, iY, seaFoamGreen); break;
			}
	
	*/

	//drawing random circles

	//for each x coordinate..
	for (int iX = 0; iX < getWindowWidth(); iX+=5)
		//.. for each y coordinate..
		for (int iY = 0; iY < this->getWindowHeight(); iY+=5)
			//.. generate a random number and modulo it with 100..
			switch (rand() % 100)
			{
			//.. if it results in a 0, 1, 2, or 3, draw a spot with the specified colour; if not don't draw a spot. (1/100 chance of a specific coloured spot, 1/25 chance of their being a spot)
			case 0: drawBackgroundOval(iX - 4, iY - 4, iX, iY, duckEgg); break;
			case 1: drawBackgroundOval(iX - 4, iY - 4, iX, iY, munsell); break;
			case 2: drawBackgroundOval(iX - 4, iY - 4, iX, iY, royalBlue); break;
			case 3: drawBackgroundOval(iX - 4, iY - 4, iX, iY, sandyYellow); break;
			case 4: drawBackgroundOval(iX - 4, iY - 4, iX, iY, seaFoamGreen); break;
			}

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			tm.setMapValue(i, j, rand());
	tm.setTopLeftPositionOnScreen(50, 50);
	tm.drawAllTiles(this, getBackgroundSurface());
}


void MyDemoA::virtMouseDown(int iButton, int iX, int iY)
{
	std::cout << "Mouse clicked at: " << iX << ", " << iY<< "\n";

	if (tm.isValidTilePosition(iX, iY)) // Clicked within tiles?
	{
		std::cout << "Mouse clicked a tile\n";

		if (iButton == SDL_BUTTON_LEFT) {
			int mapX = tm.getMapXForScreenX(iX); // Which column?
			int mapY = tm.getMapYForScreenY(iY); // Which row?
			int value = tm.getMapValue(mapX, mapY); // Current value?
			tm.setAndRedrawMapValueAt(mapX, mapY, value + rand(), this, getBackgroundSurface()); //change it to a random colour
			redrawDisplay(); // Force background to be redrawn to foreground
		}
		
		if (iButton == SDL_BUTTON_RIGHT) {
			int mapX = tm.getMapXForScreenX(iX); // Which column?
			int mapY = tm.getMapYForScreenY(iY); // Which row?
			tm.setAndRedrawMapValueAt(mapX, mapY, 0x000000, this, getBackgroundSurface()); //change it to black
			redrawDisplay(); // Force background to be redrawn to foreground
		}

		if (iButton == SDL_BUTTON_MIDDLE) {
			int mapX = tm.getMapXForScreenX(iX); // Which column?
			int mapY = tm.getMapYForScreenY(iY); // Which row?
			tm.setAndRedrawMapValueAt(mapX, mapY, 0xFFFFFF, this, getBackgroundSurface()); //change it to black
			redrawDisplay(); // Force background to be redrawn to foreground
		}
	}
	else {
		std::cout << "Mouse has not clicked a tile\n";

		// if the left mouse button has been clicked
		if (iButton == SDL_BUTTON_LEFT) {
			lockBackgroundForDrawing();	//lock background so only 1 thing can draw to it at a time
			drawBackgroundRectangle(iX - 10, iY - 10, iX + 10, iY + 10, seaGreen); // drawing a rectangle of size 20*20 centred around the mouse
			drawBackgroundOval(iX - 7, iY - 7, iX + 7, iY + 7, seaFoamGreen);
			setBackgroundPixel(iX, iY, red);
			unlockBackgroundForDrawing(); //unlock backgruond so other things can draw to it
			redrawDisplay(); // Force backgroudn to be redrawn to foreground
		}

		// if the right mouse button has been clicked
		if (iButton == SDL_BUTTON_RIGHT) {
			lockBackgroundForDrawing();	//lock background so only 1 class can draw to it at a time
			drawBackgroundRectangle(iX - 7, iY - 7, iX + 7, iY + 7, teal); // drawing a rectangle of size 14*14 centred around the mouse
			drawBackgroundOval(iX - 4, iY - 4, iX + 4, iY + 4, royalBlue);
			setBackgroundPixel(iX, iY, munsell);
			unlockBackgroundForDrawing(); //unlock backgruond so other classes can draw to it
			redrawDisplay(); // Force backgroudn to be redrawn to foreground
		}
	}
}


void MyDemoA::virtKeyDown(int iKeyCode)
{
	// do a different thing for each key that was pressed
	switch (iKeyCode) {
	//if spacebar was pressed:
	case SDLK_SPACE:
		std::cout << "Space Key Pressed\n";
		lockBackgroundForDrawing(); //lock background so only 1 thing can draw to it at a time
		virtSetupBackgroundBuffer(); //call the method for setting up the background
		unlockBackgroundForDrawing();  //unlock backgruond so other things can draw to it
		redrawDisplay(); //redraw the background
		break;
	// if return key was pressed..
	case SDLK_RETURN:
		std::cout << "Return Key Pressed\n";

		// only draw this image once
		if (!returnPressed) {
			std::cout << "Drawing image\n";
			lockBackgroundForDrawing();	//lock background so only 1 class can draw to it at a time
			SimpleImage image = ImageManager::loadImage("demo.png", true);
			image.renderImage(getBackgroundSurface(), 0, 0, 10, 10, image.getWidth(), image.getHeight());
			unlockBackgroundForDrawing(); //unlock backgruond so other classes can draw to it
			redrawDisplay(); // Force backgroudn to be redrawn to foreground
			returnPressed = true; // set return pressed to true so it doesn't draw it again
		}
		
	}
	
}

// really important function, need to create all of the objects which will be moving and store pointers to them in the array.
int MyDemoA::virtInitialiseObjects()
{
	// Record the fact that we are about to change the array
	// so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);
	// Creates an array big enough for the number of objects that you want.
	createObjectArray(1);
	// You MUST set the array entry after the last one that you create to NULL,
	// so that the system knows when to stop.
	storeObjectInArray(0, new MyObjectA(this));
	// NOTE: We also need to destroy the objects, but the method at the
	// top of this function will destroy all objects pointed at by the
	// array elements so we can ignore that here.
	setAllObjectsVisible(true);
	return 0;
}
