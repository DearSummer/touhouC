#include "Input.h"


Input & Input::getInstance()
{
	// TODO: insert return statement here
	static Input instance;
	return instance;
}

void Input::update()
{
	timer++;
	if (timer > 30)
	{
		reset();
	}
		
}

void Input::reset()
{
	keyADown = false;
	keyDDown = false;
	keySDown = false;
	keyWDown = false;

	keyLeftDown = false;
	keyRightDown = false;
	keyUpDown = false;
	keyDownDown = false;

	lButtonDown = false;
	rButtonDown = false;

	keyZDown = false;
	keyXDown = false;

	timer = 0.0f;
}



