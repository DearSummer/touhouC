#include "InputSignal.h"
#include "Input.h"


InputSignal::InputSignal():x(0),y(0),targetX(0),targetY(0)
{
}


InputSignal::~InputSignal()
= default;

float InputSignal::lerp(const float a, const float b, const float t)
{
	return a * (1 - t) + b * t;
}

InputSignal& InputSignal::getInstance()
{
	static InputSignal instance;
	return instance;
}

void InputSignal::tick()
{

	targetX = (Input::getInstance().keyRightDown ? 1 : 0) - (Input::getInstance().keyLeftDown ? 1 : 0 );
	targetY = (Input::getInstance().keyDownDown ? 1 : 0) - (Input::getInstance().keyUpDown ? 1 : 0);

	x = lerp(x, targetX, 0.3);
	y = lerp(y, targetY, 0.3);
	
}

float InputSignal::getXSignal() const
{
	return this->x;
}

float InputSignal::getYSignal() const
{
	return this->y;
}
