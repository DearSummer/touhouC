#pragma once
#include "Sprite.h"

class Animation
{
	int count;
	int frame;

	float animTime;

public:
	Sprite** spriteList;

	Animation(const std::string& path, int x, int y, int count);
	~Animation();

	Sprite * getCurrentSprite() const;

	void reset();
	int getCurrentFrame() const;
	bool isTheLastFrame() const;

	void draw(CDC & dc);
	void draw(CDC & dc, float time);
	void draw(CDC * dc, CDC * canvasDC, int x, int y, float time);

	void drawImg(CDC * dc, CDC * canvasDC, int x, int y,float time);
};

