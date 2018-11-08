#pragma once
#include <afxwin.h>
#include <string>
#include "Rect.h"

class Sprite
{
	CBitmap * bitmap;
	Rect rect;

	

	void updateSprite(int x, int y, int width, int height);
public:
	Sprite() = default;
	Sprite(const Sprite& s);
	Sprite(const std::string& path,int x,int y);
	~Sprite();

	int width = 0, height = 0;

	void init(const std::string& path, int x, int y);

	void draw(CDC * dc, CDC * canvasDc,int x,int y, int width, int height,int xSrc,int ySrc, DWORD dwRop);
	CBitmap * getBitmap() const;
	Rect getRect() const;


};

