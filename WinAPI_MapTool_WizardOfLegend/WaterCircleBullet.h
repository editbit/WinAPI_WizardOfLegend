#pragma once
#include "bullet.h"
class WaterCircleBullet :
	public Bullet
{
public:
	virtual void update();
	virtual void render();

	virtual bool collide(Actor * a);
	WaterCircleBullet() {}
	~WaterCircleBullet() {}

};

