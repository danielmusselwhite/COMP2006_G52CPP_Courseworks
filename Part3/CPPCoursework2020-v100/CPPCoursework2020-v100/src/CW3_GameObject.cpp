#include "header.h"
#include "CW3_GameObject.h"
#include "BaseEngine.h"
#include "CW3_Game.h"

//DisplayableObject(xCoord, yCoord, pointerToMainClass, width, height, true: draw at top left ? draw at centre)
CW3_GameObject::CW3_GameObject(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight) : DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, true) {
	//(CW3_Game*)pEngine;
	m_pGameEngine = dynamic_cast<CW3_Game*>(pEngine); //checks its a subclass first
	m_drawableObjectIndex = m_pGameEngine->getDrawableObjectVectorSize(); // this is the most recently added one so this will be its index, if index is changed this will be updated
}

CW3_GameObject::~CW3_GameObject() {

}

double CW3_GameObject::getCurrentXCoordinate() {
	return m_iCurrentScreenX;
}

double CW3_GameObject::getCurrentYCoordinate() {
	return m_iCurrentScreenY;
}