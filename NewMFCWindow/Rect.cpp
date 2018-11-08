#include "Rect.h"

Rect::Rect():Rect(0,0)
{
}

Rect::Rect(const int width, const int height):Rect(0,0,width,height)
{
}

Rect::Rect(const int x, const int y, const int width, const int height):x(x),y(y),width(width),height(height)
{
}


