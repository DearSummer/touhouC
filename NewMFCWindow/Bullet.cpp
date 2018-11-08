#include "Bullet.h"
#include "Util.h"


Bullet::Bullet(const std::string & path,int width,int height,float aliveTime)
	:bulletPos(Point()),aliveTime(aliveTime),timer(0),speed(0),damage(1)
{
	bullet = new Sprite(path, width, height);
}

Bullet::Bullet()
	:bulletPos(Point()), aliveTime(BULLET_NEVER_DIE_WITH_TIME), timer(0), speed(0)
{
}

Bullet::~Bullet()
= default;

void Bullet::setSpeed(float speed)
{
	this->speed = speed;
}

float Bullet::getSpeed() const
{
	return speed;
}

void Bullet::setDamage(int damage)
{
	this->damage = damage;
}

int Bullet::getDamage() const
{
	return damage;
}

void Bullet::setState(const State state)
{
	this->state = state;
}

State Bullet::getState() const
{
	return state;
}



Point Bullet::getPos() const
{
	return bulletPos;
}

void Bullet::setPos(Point pos)
{
	this->bulletPos = pos;
}

Rect Bullet::getCollider() const
{
	Rect rect;
	rect.x = bulletPos.x;
	rect.y = bulletPos.y;
	rect.width = bullet->width / 2;
	rect.height = bullet->height;
	return rect;
}



bool Bullet::isDead() const
{	
	if (aliveTime == BULLET_NEVER_DIE_WITH_TIME)
		return false;

	return timer > aliveTime;
}

bool Bullet::operator==(const Bullet & bullet)
{
	return this == &bullet;
}
