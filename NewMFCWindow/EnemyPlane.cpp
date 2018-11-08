#include "EnemyPlane.h"
#include <complex>


Point EnemyPlane::circle(float r, float angle) const
{
	return {r * std::cos(angle), r * std::sin(angle)};
}

EnemyPlane::EnemyPlane()
= default;


EnemyPlane::~EnemyPlane()
{
	delete player;
}



State EnemyPlane::getState() const
{
	if (isDead())
		return DIE_BY_SHOOT;

	if (actorPos.x < 0 || actorPos.x > 390 || actorPos.y < 0 || actorPos.y > 560)
		return DIE_OUT_OF_RANGE;

	return state;
}

void EnemyPlane::setState(State s)
{
	state = s;
}

void EnemyPlane::setBirthPos(Point p)
{
	actorPos = p;
}

void EnemyPlane::setStage(Stage s)
{
	this->stage = s;
}

Stage EnemyPlane::getStage() const
{
	return stage;
}

int EnemyPlane::getHp() const
{
	return hp;
}

int EnemyPlane::getMaxHp() const
{
	return maxHp;
}

