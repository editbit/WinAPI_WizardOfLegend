#pragma once
#include "bullet.h"

#define FIRE_COUNT_MAX 50

class FirePillar :
	public Bullet
{
	int _activeCount;

public:
	virtual HRESULT init(float radius, float speed, float power, float range, const char* imageName = "");
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	//virtual void render(bool rotate = false);
	virtual void release();

	virtual void fire(Image * pixelMap, float x, float y, float angle);

	bool collide(Actor * a);
	virtual void collide();


	FirePillar() {}
	~FirePillar() {}
};

