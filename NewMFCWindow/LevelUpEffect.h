#pragma once
#include "Buff.h"
class LevelUpEffect :
	public Buff
{
	float timer,delayTime;
public:
	LevelUpEffect(const std::string& path, int x, int y);
	LevelUpEffect();
	~LevelUpEffect();

	void draw(CDC* dc, CDC* canvasDC) override;
	State getState() override;
	Buff* clone() override;

	void setDelayTime(float t);
};

