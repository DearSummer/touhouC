#include "LevelUpEffect.h"
#include "Util.h"
#include "Time.h"


LevelUpEffect::LevelUpEffect(const std::string& path, int x, int y) :
	Buff(path, x, y, 1), timer(0),delayTime(1000)
{
	buffType = BUFF_TYPE_COLLIDER_OFF;
	buffState = DISPLAY;
}

LevelUpEffect::LevelUpEffect():timer(0),delayTime(1000)
{}


LevelUpEffect::~LevelUpEffect()
= default;

void LevelUpEffect::draw(CDC* dc, CDC* canvasDC)
{
	pos.y -= 1;
	if (timer > delayTime)
		buffState = DIE_OUT_OF_RANGE;

	timer += Time.detlaTime;
	DRAW_IMG(dc, canvasDC, sprite, pos.x, pos.y);
}

State LevelUpEffect::getState()
{
	return buffState;
}

Buff* LevelUpEffect::clone()
{
	LevelUpEffect * newBuff = new LevelUpEffect();
	newBuff->anim = anim;
	newBuff->sprite = sprite;
	newBuff->width = width;
	newBuff->buffState = buffState;
	newBuff->buffType = buffType;
	newBuff->playerBuffType = playerBuffType;
	newBuff->height = height;
	return newBuff;
}

void LevelUpEffect::setDelayTime(float t)
{
	this->delayTime = t;
}

