#pragma once
#include "bullet.h"
class AttackBullet :
	public Bullet
{
public:
	virtual HRESULT init(float radius, float speed, float power, float range, const char* imageName = "");
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	//virtual void render(bool rotate = false);
	virtual void release();

	virtual void fire(Image * pixelMap, float x, float y, float angle);

	virtual bool collide(Actor * a);

	AttackBullet() {}
	~AttackBullet() {}
};

