#include "header.h"
#include "CW3_Game.h"

// customisable background
//stars
#define starSizeGap starSize+1 //can be defined as variables i.e. starSize or other MACROs
#define starSizeMin 1
#define starSizeRange 10
#define starChanceDenominator 500 //higher it is, lower the chance of their being a star (and thus frequency of stars)

// Colours
#define clrBgMain 0x000000
#define clrBgStarWhite 0xffffff
#define clrBgStarRed 0xffe0e0
#define clrBgStarBlue 0xe0fffc
#define clrBgStarYellow 0xfeffe0

CW3_Game::CW3_Game() {

}

CW3_Game::~CW3_Game() {

}

void CW3_Game::virtSetupBackgroundBuffer() {
	fillBackground(clrBgMain);
	
	// declared local in this block as nothing inside of it is needed outside of it
	{
		int starSize = 0; // stars can be different sizes

		//for each x coordinate..
		for (int iX = 0; iX < getWindowWidth(); iX += starSizeGap) {

			//.. for each y coordinate..
			for (int iY = 0; iY < this->getWindowHeight(); iY += starSizeGap) {
				
				starSize = (rand() % starSizeRange) + starSizeMin; // get random star size

				//.. generate a random number and modulo it with for example, 100..
				switch (rand() % starChanceDenominator)
				{
					//.. if it results in a 0, 1, 2, or 3, draw a spot with the specified colour; if not don't draw a spot. (1/100 chance of a specific coloured spot, 1/25 chance of their being a spot)
				case 0: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarWhite); break;
				case 1: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarRed); break;
				case 2: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarBlue); break;
				case 3: drawBackgroundOval(iX - starSize, iY - starSize, iX, iY, clrBgStarYellow); break;

				}
			}
		}
			
		
	}

}

void CW3_Game::virtMouseDown(int iButton, int iX, int iY) {
	std::cout << "Mouse clicked at: " << iX << ", " << iY << "\n";
}

void CW3_Game::virtKeyDown(int iKeyCode) {
	std::cout << iKeyCode << " key pressed";

	switch (iKeyCode) {
	case SDLK_SPACE:
		lockBackgroundForDrawing(); //lock background so only 1 thing can draw to it at a time
		virtSetupBackgroundBuffer(); //call the method for setting up the background
		unlockBackgroundForDrawing();  //unlock backgruond so other things can draw to it
		redrawDisplay(); //redraw the background
		break;
	}
}

int CW3_Game::virtInitialiseObjects() {
	return 0;
}