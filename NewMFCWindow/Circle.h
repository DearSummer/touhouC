#pragma once
struct Circle
{
	int x, y;
	float r;

	Circle():Circle(0,0,0) {}
	Circle(const int x, const int y) :Circle(x, y, 0) {}
	Circle(const int x, const int y, const float r) { this->x = x; this->y = y; this->r = r; }
};