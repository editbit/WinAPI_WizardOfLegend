#pragma once
#include "bullet.h"
class WaterThrowBullet :
	public Bullet
{
public:
	virtual void render();

	virtual bool collide(Actor * a);

	WaterThrowBullet() {}
	~WaterThrowBullet() {}
};

