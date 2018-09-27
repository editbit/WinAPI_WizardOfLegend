#pragma once
#include "bullet.h"
class WaterCircleBullet :
	public Bullet
{
	float _circleAngle;
	float x, y;
	int _dir;

public:
	virtual HRESULT init(float radius, float speed, float power, float range, const char* imageName = "");
	virtual void update();
	virtual void render();

	virtual bool collide(Actor * a);
	virtual void fire(Image * pixelMap, float x, float y, float angle, int dir = 1);
	WaterCircleBullet() {}
	~WaterCircleBullet() {}

};

