#pragma once
#include "Buff.h"

class PowerBuff : public Buff
{
	float timer;

public:
	PowerBuff(const std::string path,int x,int y);
	PowerBuff();
	~PowerBuff();

	void draw(CDC* dc, CDC* canvasDC) override;
	State getState() override;
	Buff* clone() override;

	void setPlayerBuffType(PlayerBuffType bt);
};

