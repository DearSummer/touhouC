#pragma once
#include "Buff.h"

class Crash : public Buff
{
	std::string path;
	int x, y, count;
public:
	Crash(const std::string & path,int x,int y,int count,Point point);
	Crash();
	~Crash();


	void draw(CDC* dc, CDC* canvasDC) override;
	State getState() override;
	Buff* clone() override;
};

