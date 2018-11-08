#include "Screen.h"


Screen screen;

Screen::Screen():width(0),height(0)
{
}


void Screen::setScreenSize(const int width, const int height)
{
	this->width = width;
	this->height = height;
}

int Screen::getWidth() const
{
	return width;
}

int Screen::getHeight() const
{
	return height;
}
