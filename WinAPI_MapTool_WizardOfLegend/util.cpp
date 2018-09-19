#include "stdafx.h"
#include "util.h"

//두 점 사이의 거리 (직각 삼각형의 빗변길이)
float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x*x + y * y);
}

float MY_UTIL::getDistance(float _x, float _y)
{
	return sqrt(pow(_x, 2) + pow(_y, 2));
}

//두 점 사이의 각도 
float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	return atan2(startY - endY, endX - startX);
}

float MY_UTIL::getAnglef(float startX, float startY, float endX, float endY)
{
	float angle = atan2(startY - endY, endX - startX);
	if (angle < 0)
		angle += 2 * PI;
	return angle;
}
