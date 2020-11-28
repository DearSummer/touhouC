#pragma once
#include "Point.h"
#include "Sprite.h"

#define BULLET_NEVER_DIE_WITH_TIME -1

enum class State
{
	DISPLAY,
	DIE_OUT_OF_RANGE,
	DIE_BY_SHOOT
};

enum class BulletType
{
	BULLET_TYPE_RECT,
	BULLET_TYPE_CIRCLE
};

class Bullet
{
protected:
	Point bulletPos;
	Sprite * bullet;

	float aliveTime, timer;
	float speed;

	int damage;

	State state = State::DISPLAY;
	
public:
	explicit Bullet(const std::string& path,int width,int height,float aliveTime);
	Bullet();
	Bullet(const Bullet&) = default;
	virtual ~Bullet();

	void setSpeed(float speed);
	float getSpeed() const;

	void setDamage(int damage);
	int getDamage() const;

	void setState(State state);
	State getState() const;

	Point getPos() const;
	void setPos(Point pos);

	Rect getCollider() const;

	virtual void draw(CDC * dc, CDC * canvasDC) = 0;
	virtual Bullet * clone() = 0;
	
	virtual BulletType getBulletType() = 0;

	bool isDead() const;

	bool operator==(const Bullet& bullet);
};

