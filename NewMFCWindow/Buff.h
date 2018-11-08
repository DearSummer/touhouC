#pragma once
#include "Animation.h"
#include "Point.h"
#include "Bullet.h"

enum BuffType
{
	BUFF_TYPE_COLLIDER_ON,
	BUFF_TYPE_COLLIDER_OFF
};

enum PlayerBuffType
{
	ADD_DAMAGE,
	ADD_HEATH,
	ADD_SKILL,
	ADD_EXP,
	NONE
};

class Buff
{
protected:
	Animation * anim;
	Sprite * sprite;
	Point pos;
	int width, height;

	State buffState;
	BuffType buffType = BUFF_TYPE_COLLIDER_OFF;
	PlayerBuffType playerBuffType;

public:
	Buff(const std::string& path,int x,int y,int count);
	Buff() = default;
	virtual ~Buff();

	virtual void draw(CDC * dc, CDC * canvasDC) = 0;
	virtual State getState() = 0;

	virtual Buff * clone() = 0;

	BuffType getBuffType() const;
	PlayerBuffType getPlayerBuffType() const;
	Rect getCollider() const;

	void resetAnim() const;
	void setPos(Point p);
};

