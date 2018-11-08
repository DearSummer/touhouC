#pragma once
struct Rect
{
	int x, y, width, height;

	Rect();
	Rect(int width, int height);
	Rect(int x, int y, int width, int height);
};
