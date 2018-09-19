#pragma once

//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

//=============================================================
//	## 자주 사용하는 상수 ##
//=============================================================
#define MAGENTA		RGB(255,0,255)
#define PI		    3.14159265358979323846

#define PI_2		PI/2
#define PI_4		PI/4
#define PI_8		PI/8

namespace MY_UTIL
{
	// 두 점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	float getDistance(float _x, float _y);
	// 두 점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);

	float getAnglef(float startX, float startY, float endX, float endY);
};

namespace utl = MY_UTIL;

