#pragma once
#include "CW3_BaseEnemy.h"
#include "CW3_AnimatedImage.h"
#include "CW3_Player.h"


class CW3_StateEnemy;
class State;
class ScaredState;
class IdleState;
class AggressiveState;
class PatrollingState;

// Base state class declares methods that concrete states should implement
// and provides backreference to the context (the enemy itself) associated with the state
// this backreference can be used by states to transition the context to another state
class State {
protected:
	CW3_StateEnemy* m_context;
	int m_stateID;
	CW3_Game* m_pGameEngine;
	CW3_AnimatedImage* m_Anim;

public:

	virtual ~State() {

	}

	void setContext(CW3_StateEnemy* context, CW3_Game* pGameEngine) {
		m_context = context;
		m_pGameEngine = pGameEngine;
	}
	int getID() {
		return m_stateID;
	}

	virtual void checkForStateTransition(CW3_Player* target) = 0;
	virtual int moveX(double differenceInX, int m_speed, int goalX);
	virtual int moveY(double differenceInY, int m_speed, int goalY);

	void draw();

	virtual void update() {
		return;
	}
};








// if in idle don't move and don't attack but if the player gets too close, change state to aggressive
class IdleState : public State {
public:
	

	IdleState() {
		this->m_stateID = 0;

		// setting up left anim
		std::vector<std::pair<SimpleImage, int>> animPairs;
		animPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\skelet_idle_anim_f0.png", true), 150));
		animPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\skelet_idle_anim_f1.png", true), 150));
		animPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\skelet_idle_anim_f2.png", true), 150));
		animPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\skelet_idle_anim_f3.png", true), 150));
		m_Anim = new CW3_AnimatedImage(animPairs);

	}

	~IdleState();


	// if the player is within a small circle to the player change to either aggressive or scared depending on health
	void checkForStateTransition(CW3_Player* target) override;

};

//if in idle move towards the player and attack/damage the player if touching them
class AggressiveState : public State {
protected:
	CW3_AnimatedImage* m_leftAnim;
	CW3_AnimatedImage* m_rightAnim;
public:
	AggressiveState() {
		this->m_stateID = 1;

		// setting up left anim
		std::vector<std::pair<SimpleImage, int>> leftAnimPairs;
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f0.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f1.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f2.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f3.png", true), 150));
		m_leftAnim = new CW3_AnimatedImage(leftAnimPairs);

		// setting up right anim
		std::vector<std::pair<SimpleImage, int>> rightAnimPairs;
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f0.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f1.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f2.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f3.png", true), 150));
		m_rightAnim = new CW3_AnimatedImage(rightAnimPairs);

		m_Anim = m_leftAnim;
	}

	~AggressiveState() override;

	int moveX(double differenceInX, int m_speed, int goalX) override;

	int moveY(double differenceInY, int m_speed, int goalY) override;

	void checkForStateTransition(CW3_Player* target) override;

	void update() override;
};


class PatrollingState : public State {
private:
	int m_timeLimit;
	int m_xDirection;
	int m_yDirection;
	int m_movingTime;

protected:
	CW3_AnimatedImage* m_leftAnim;
	CW3_AnimatedImage* m_rightAnim;

public:
	PatrollingState() {
		this->m_stateID = 2;

		m_xDirection = 0;
		m_yDirection = 0;

		m_timeLimit = -1;
		m_movingTime = -1;

		// setting up left anim
		std::vector<std::pair<SimpleImage, int>> leftAnimPairs;
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f0.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f1.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f2.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f3.png", true), 150));
		m_leftAnim = new CW3_AnimatedImage(leftAnimPairs);

		// setting up right anim
		std::vector<std::pair<SimpleImage, int>> rightAnimPairs;
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f0.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f1.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f2.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f3.png", true), 150));
		m_rightAnim = new CW3_AnimatedImage(rightAnimPairs);

		m_Anim = m_leftAnim;
	}

	~PatrollingState() override;

	int moveX(double differenceInX, int m_speed, int goalX) override;

	int moveY(double differenceInY, int m_speed, int goalY) override;

	void checkForStateTransition(CW3_Player* target) override;

	void update() override;
};

class ScaredState : public State {
protected:
	CW3_AnimatedImage* m_leftAnim;
	CW3_AnimatedImage* m_rightAnim;

public:
	ScaredState() {
		this->m_stateID = 3;

		// setting up left anim
		std::vector<std::pair<SimpleImage, int>> leftAnimPairs;
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f0.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f1.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f2.png", true), 150));
		leftAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Left\\skelet_run_anim_f3.png", true), 150));
		m_leftAnim = new CW3_AnimatedImage(leftAnimPairs);

		// setting up right anim
		std::vector<std::pair<SimpleImage, int>> rightAnimPairs;
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f0.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f1.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f2.png", true), 150));
		rightAnimPairs.push_back(std::make_pair(ImageManager::loadImage("images\\DungeonFrames\\Enemies\\_myEnemies\\Skeleton\\Right\\skelet_run_anim_f3.png", true), 150));
		m_rightAnim = new CW3_AnimatedImage(rightAnimPairs);

		m_Anim = m_leftAnim;
	}

	~ScaredState() override;

	int moveX(double differenceInX, int m_speed, int goalX) override;

	int moveY(double differenceInY, int m_speed, int goalY) override;
	void checkForStateTransition(CW3_Player* target) override;

	void update() override;
};




class CW3_StateEnemy : public CW3_BaseEnemy {
public:
	State *m_state;

public:
	CW3_StateEnemy(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int maxHealth, int currentHealth, int minDamage, int maxDamage, int speed, int pointsValue, int  startState);

	//deconstructor
	~CW3_StateEnemy() override;

	//transitioning between the different states
	void transitionToState(State *state);

	double getHealthRatio() {
		return  (double)m_health / (double)m_maxHealth;
	}

	// overriding BaseEnemy functions
	void virtAttack() override;
	void virtMove() override;

	// overriding GameObject functions
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

	// overiding LivingGameObject functions
	void virtDie() override;

	virtual std::vector<std::string> getState() override {
		std::vector<std::string> currentState{ "stateEnemy",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_maxHealth), std::to_string(m_health), std::to_string(m_minDamage), std::to_string(m_maxDamage), std::to_string(m_speed), std::to_string(m_pointsValue), std::to_string(m_state->getID()) };
		return currentState;
	}

};









