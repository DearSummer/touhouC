#include "Animation.h"
#include "Time.h"
#include "Util.h"

Animation::Animation(const std::string& path, const int x, const int y, const int count) :
	count(count),frame(0),animTime(0)
{
	spriteList = new Sprite * [count];
	for(int i = 0;i < count;i++)
	{
		std::string imgPath = path + "_";
		imgPath += std::to_string(i);
		imgPath += ".bmp";

		spriteList[i] = new Sprite(imgPath, x, y);
	}
}

Animation::~Animation()
{
	delete[] spriteList;
}

Sprite * Animation::getCurrentSprite() const
{
	return spriteList[frame];
}

void Animation::reset()
{
	frame = 0;
}

int Animation::getCurrentFrame() const
{
	return frame;
}

bool Animation::isTheLastFrame() const
{
	return frame == (count - 1);
}

void Animation::draw(CDC & dc)
{
	frame %= count;
	dc.SelectObject(spriteList[frame]->getBitmap());
}

void Animation::draw(CDC & dc, const float time)
{
	animTime += Time.detlaTime;
	if(animTime > time)
	{
		animTime = 0;
		frame++;
	}
	draw(dc);
}

void Animation::draw(CDC * dc, CDC * canvasDC, int x, int y, float time)
{
	animTime += Time.detlaTime;
	if (animTime > time)
	{
		animTime = 0;
		frame++;
	}

	frame %= count;
	dc->SelectObject(spriteList[frame]->getBitmap());
	canvasDC->BitBlt(x, y, spriteList[frame]->width, spriteList[frame]->height, dc, 0, 0, SRCCOPY);
}

void Animation::drawImg(CDC * dc, CDC * canvasDC, int x, int y,float time)
{
	animTime += Time.detlaTime;
	if (animTime > time)
	{
		animTime = 0;
		frame++;
	}

	frame %= count;
	dc->SelectObject(spriteList[frame]->getBitmap());
	DRAW_IMG(dc, canvasDC, spriteList[frame], x, y);
}


