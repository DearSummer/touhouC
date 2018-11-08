#include "Math.h"

float Math::lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}
