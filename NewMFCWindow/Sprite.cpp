#include "Sprite.h"




void Sprite::updateSprite(int x, int y, int width, int height)
{
	rect.x = x;
	rect.y = y;
	rect.width = width;
	rect.height = height;
}

Sprite::Sprite(const Sprite & s)
{
	bitmap = s.bitmap;
	rect = s.rect;
}

Sprite::Sprite(const std::string& path, const int x, const int y):rect(Rect(x,y)),width(x),height(y)
{
	init(path, x, y);
}

Sprite::~Sprite()
{
	delete bitmap;
}

void Sprite::init(const std::string & path, const int x, const int y)
{
	bitmap = new CBitmap();
	bitmap->m_hObject = LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, x, y, LR_LOADFROMFILE);
}


void Sprite::draw(CDC * dc, CDC * canvasDc, int x, int y, int width, int height, int xSrc, int ySrc,DWORD dwRop)
{
	dc->SelectObject(getBitmap());
	canvasDc->BitBlt(x, y, width, height, dc, xSrc, ySrc, dwRop);

	updateSprite(x, y, width, height);
}

CBitmap * Sprite::getBitmap() const
{
	return bitmap;
}

Rect Sprite::getRect() const
{
	return rect;
}
