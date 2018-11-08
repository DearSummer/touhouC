#pragma once
#include "Sprite.h"

class IGameLoop
{

public:
	IGameLoop();
	virtual ~IGameLoop() = default;

	virtual void onStart() = 0;
	virtual void update(CDC * dc,CDC * canvasDC) = 0;
};

