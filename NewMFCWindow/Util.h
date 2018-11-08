#pragma once
#include "Sprite.h"


inline void __drawImg(CDC * dc,CDC * canvasDC, Sprite * sprite, int posX, int posY)
{
	sprite->draw(dc, canvasDC, posX, posY, sprite->width / 2, sprite->height, sprite->width / 2, 0, SRCAND);
	sprite->draw(dc, canvasDC, posX, posY, sprite->width / 2, sprite->height, 0, 0, SRCPAINT);
}


#define DRAW_IMG(dc,canvasDC,sprite,posX,posY) __drawImg(dc,canvasDC,sprite,posX,posY)