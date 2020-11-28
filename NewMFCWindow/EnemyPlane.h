#pragma once
#include "Actor.h"
#include "Animation.h"
#include <vector>

enum Stage
{
	E_STAGE_1,
	E_STAGE_2,
	E_STAGE_3,
	E_STAGE_4,
	E_STAGE_5
};

class EnemyPlane : 
	public Actor
{

protected:
	Animation * player = nullptr;
	Point circle(float r,float angle) const;

	int maxHp = 0;

	Stage stage = E_STAGE_1;

	State state = State::DISPLAY;

public:
	EnemyPlane();
	~EnemyPlane();

	virtual EnemyPlane * clone() = 0;
	virtual void getHurt(int damage) = 0;

	State getState() const;
	void setState(State s);

	void setBirthPos(Point p);

	void setStage(Stage s);
	Stage getStage() const;



	int getHp() const;
	int getMaxHp() const;

	bool isBoss = false;
};

