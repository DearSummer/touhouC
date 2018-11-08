#include "PowerBuff.h"
#include "Util.h"
#include "Time.h"


PowerBuff::PowerBuff(const std::string path, int x, int y)
	:Buff(path,x,y,1),timer(0)
{
	playerBuffType = ADD_DAMAGE;
	buffType = BUFF_TYPE_COLLIDER_ON;
	buffState = DISPLAY;
}

PowerBuff::PowerBuff()
= default;

PowerBuff::~PowerBuff()
= default;

void PowerBuff::draw(CDC * dc, CDC * canvasDC)
{
	pos.y += (-3 + timer > 5 ? timer : 5) ;
	timer += Time.detlaTime / 1000;
	if (pos.y < 0)
		buffState = DIE_OUT_OF_RANGE;

	DRAW_IMG(dc, canvasDC, sprite, pos.x, pos.y);
}

State PowerBuff::getState()
{
	return buffState;
}

Buff * PowerBuff::clone()
{
	PowerBuff * newBuff = new PowerBuff();
	newBuff->anim = anim;
	newBuff->sprite = sprite;
	newBuff->width = width;
	newBuff->buffState = buffState;
	newBuff->buffType = buffType;
	newBuff->playerBuffType = playerBuffType;
	newBuff->height = height;
	return newBuff;
}

void PowerBuff::setPlayerBuffType(const PlayerBuffType pbt)
{
	this->playerBuffType = pbt;
}
