#include "header.h"
#include "MyObjectA.h"
#include "BaseEngine.h"

#define cardinal 0xC41E3A
#define carmine 0x960018

int currentSpeed, walkSpeed, runSpeed;

//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
MyObjectA::MyObjectA(BaseEngine* pEngine) : DisplayableObject(0, 0, pEngine, 100, 200, true) {
	/* not needed as being passed to alternative form of base class constructor instead
	// starting coordinates on screen
	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = 0;

	// defining drawing area
	m_iDrawWidth = 100;
	m_iDrawHeight = 200;

	*/

	// setting different speeds
	walkSpeed = 5;
	runSpeed = 10;
}

MyObjectA::~MyObjectA() {

}

void MyObjectA::virtDraw()
{
	//getEngine() retrieves pointer to base engine object
	//drawForegroundRectanle() draws a rectangle to the foreground

	// draw rectangle with this x coordinate, and this y coordinate
	// with this width
	// and this length
	// -1 is needed for example if you have rectangle at coord 0, with proportions 100x100, it will fill pixels 0-99 aka 100 pixels (0-100 would be 101 pixels)
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		carmine);
}


void MyObjectA::virtDoUpdate(int iCurrentTime)
{
	// if shift key is pressed change players speed
	if (getEngine()->isKeyPressed(SDLK_LSHIFT)) {
		m_iColour = cardinal;
		currentSpeed = runSpeed;
	}
	else {
		m_iColour = carmine;
		currentSpeed = walkSpeed;
	}
		

	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP)) {
		// checking top of object is within upper bounds of world before moving up
		if (m_iCurrentScreenY - currentSpeed >= 0) {
			m_iCurrentScreenY -= currentSpeed;
		}
		// if we're before the bounds, jump to the bound
		else {
			m_iCurrentScreenY = 0;
		}
	}
	if (getEngine()->isKeyPressed(SDLK_DOWN)) {
		// checking bottom of object is within bottom bounds of world before moving down
		if ((m_iCurrentScreenY+m_iDrawHeight) + currentSpeed <= getEngine()->getWindowHeight()) {
			m_iCurrentScreenY += currentSpeed;
		}
		// if we're before the bounds, jump to the bound
		else {
			// current Y position of object (top left corner) = bottom y pos of window - the height of this object ( so that we aren't jumping top of object to that coord but bottom of it)
			m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
		}
	}
		
	if (getEngine()->isKeyPressed(SDLK_LEFT)) {
		// check if left side of object is within leftmost bounds of world before moving left
		if (m_iCurrentScreenX - currentSpeed >= 0) {
			m_iCurrentScreenX -= currentSpeed;
		}
		// if we're before the bounds, jump to the bound
		else {
			m_iCurrentScreenX = 0;
		}
	}
		
	if (getEngine()->isKeyPressed(SDLK_RIGHT)) {
		// check if right side of object is within rightmost bounds of world before moving right
		if ((m_iCurrentScreenX+m_iDrawWidth) + currentSpeed <= getEngine()->getWindowWidth()) {
			m_iCurrentScreenX += currentSpeed;
		}
		// if we're before the bounds, jump to the bound
		else {
			// current X position of object (top left corner) = right most x pos of window - the width of this object ( so that we aren't jumping top of object to that coord but bottom of it)
			m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
		}
	}
		

	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}
