#include "Actor.h"
#include "Util.h"

void Actor::drawActor(CDC * dc, CDC * canvasDC) const
{
	if (actor == nullptr)
		return;

	DRAW_IMG(dc, canvasDC, actor, actorPos.x, actorPos.y);
}

Actor::Actor():hp(1),speed(0),damage(0),level(1)
{

	actorPos.x = 0;
	actorPos.y = 0;
}
Actor::~Actor()
= default;

void Actor::setAttributes(const float hp, const float speed, const float damage, const int level)
{
	this->hp = hp;
	this->speed = speed;
	this->damage = damage;
	this->level = level;
}

void Actor::addHeath(const float damage)
{
	this->hp += damage;
}

bool Actor::isDead() const
{
	return this->hp <= 0;
}

Point Actor::getPos() const
{
	return actorPos;
}

void Actor::setCollider(const int width, const int height)
{
	this->width = width;
	this->height = height;
}

Rect Actor::getCollider()
{
	Rect collider;
	collider.x = actorPos.x;
	collider.y = actorPos.y;
	collider.width = width;
	collider.height = height;
	return collider;
}


