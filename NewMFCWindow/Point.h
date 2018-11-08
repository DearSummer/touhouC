#pragma once
struct Point
{
	float x, y;

	Point()
	{
		x = 0;
		y = 0;
	};

	Point(float x,float y)
	{
		this->x = x;
		this->y = y;
	}
};