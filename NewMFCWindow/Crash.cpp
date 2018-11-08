#include "Crash.h"


Crash::Crash(const std::string & path, int x, int y, int count,Point point)
	:Buff(path,x,y,count)
{
	buffType = BUFF_TYPE_COLLIDER_OFF;
	pos = point;
}

Crash::Crash()
= default;

Crash::~Crash()
= default;

void Crash::draw(CDC * dc, CDC * canvasDC)
{
	if (anim->isTheLastFrame())
		buffState = DIE_OUT_OF_RANGE;

	anim->drawImg(dc, canvasDC, static_cast<int>(pos.x), static_cast<int>(pos.y), 35.0f);
}

State Crash::getState()
{
	return buffState;
}

Buff * Crash::clone()
{
	Crash * crash = new Crash();
	crash->anim = anim;
	crash->buffState = buffState;
	crash->buffType = buffType;
	crash->pos = pos;
	crash->width = width;
	crash->height = height;
	crash->resetAnim();
	return crash;
}
