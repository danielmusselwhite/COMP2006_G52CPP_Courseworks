#include "header.h"
#include "CW3_Game.h"

// customisable tilemap
#define tmCountXTiles 10
#define tmCountYTiles 10

// customisable background
#define starSizeGap starSize //can be defined as variables i.e. starSize or other MACROs
#define starSizeMin 1
#define starSizeRange 10
#define starChanceDenominator 500 //higher it is, lower the chance of their being a star (and thus frequency of stars)

// Colours
#define clrBgMain 0x3d2f30
#define clrBgStarWhite 0xffffff
#define clrBgStarRed 0xffe0e0
#define clrBgStarBlue 0xe0fffc
#define clrBgStarYellow 0xfeffe0

int tmTileDimensions; //global variable to store size of tiles
int tmStartingX; //global variable to store starting x coord to draw from
int tmStartingY; //global variable to store starting y coord to draw from

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
			for (int iY = 0; iY < getWindowHeight(); iY += starSizeGap) {
			
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

	// char array used to create tilemap from
	/*std::string dungeonTileMapDesign[[]] = {
		{"wallCornerTopLeft","wallTop","wallTop","wallTop","wallTop","wallTop","wallTop","wallTop","wallCornerTopRight"}
	};*/

	/*
	0 = wall corner top left
	1 = wall top middle
	2 = wall corner top right
	3 = wall left
	4 = floor
	5 = wall right
	6 = wall corner bottom left
	7 = wall bottom middle
	8 = wall corner bottom right
	9 = player spawn
	*/
	int dungeonTileMapDesign[tmCountYTiles][tmCountXTiles] = {
		{0,1,1,1,1,1,1,1,1,2},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{3,4,4,4,4,4,4,4,4,5},
		{6,7,7,7,7,7,7,7,7,8}
	};

	// base the tiles dimensions on the windows height and the number of tiles in the x plane
	tmTileDimensions = (getWindowHeight()*.75) / tmCountYTiles;

	//start drawing from the remaining space divided by 2, so it is centered
	tmStartingX = (getWindowWidth() - tmTileDimensions * tmCountXTiles) / 2;
	tmStartingY = (getWindowHeight() - tmTileDimensions * tmCountYTiles) / 2;

	std::cout << "Tile Dimensions: " << tmTileDimensions << " Window Height: " << getWindowHeight() << "\n";

	CW3_Game::tm = new CW3_TileManager(tmTileDimensions, tmTileDimensions, tmCountYTiles, tmCountXTiles);
	/*
	// setting all tiles
	for (int i = 0; i < tmCountXTiles; i++)
		for (int j = 0; j < tmCountYTiles; j++)
			tm->setMapValue(i, j, rand());
	tm->setTopLeftPositionOnScreen(tmStartingX, tmStartingY);
	tm->drawAllTiles(this, getBackgroundSurface());
	*/


	// setting all tiles to tile map int 2D array
	for (int i = 0; i < tmCountXTiles; i++)
		for (int j = 0; j < tmCountYTiles; j++)
			tm->setMapValue(i, j, dungeonTileMapDesign[i][j]);
	tm->setTopLeftPositionOnScreen(tmStartingX, tmStartingY);
	tm->drawAllTiles(this, getBackgroundSurface());

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