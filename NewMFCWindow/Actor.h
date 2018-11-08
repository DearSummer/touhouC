#pragma once
#include "IGameLoop.h"
#include "Point.h"
#include "Shooter.h"

class Actor : public IGameLoop
{
protected:
	Sprite * actor = nullptr;
	Shooter * shooter = nullptr;

	float hp, speed, damage;
	int level,width,height;

	Point actorPos;

	void drawActor(CDC * dc,CDC * canvasDC) const;
public:
	Actor();
	~Actor();

	virtual void move() = 0;
	virtual void shoot() = 0;
	virtual void setAttributes(float hp, float speed, float damage, int level);

	void addHeath(float damage);
	bool isDead() const;

	Point getPos() const;

	void setCollider(int width, int height);
	virtual Rect getCollider();
};

