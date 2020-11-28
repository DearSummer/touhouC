#include "Buff.h"





Buff::Buff(const std::string & path, int x, int y, int count)
	:width(x / 2), height(y), buffState(State::DISPLAY), playerBuffType(NONE)
{
	if (count == 1)
		sprite = new Sprite(path, x, y);
	else
		anim = new Animation(path, x, y, count);
}

Buff::~Buff()
= default;

BuffType Buff::getBuffType() const
{
	return buffType;
}

PlayerBuffType Buff::getPlayerBuffType() const
{
	return playerBuffType;
}

Rect Buff::getCollider() const
{
	return { static_cast<int>(pos.x), static_cast<int>(pos.y), width, height };
}

void Buff::resetAnim() const
{
	anim->reset();
}

void Buff::setPos(Point p)
{
	this->pos = p;
}
