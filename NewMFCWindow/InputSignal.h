#pragma once
#include "IGameLoop.h"

class InputSignal
{
	float x, y;
	int targetX, targetY;

	InputSignal();
	static float lerp(float a, float b, float t);

public:

	

	~InputSignal();
	static InputSignal& getInstance();

	void tick();

	float getXSignal() const;
	float getYSignal() const;

};

