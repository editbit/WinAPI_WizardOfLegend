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

	Image * getImage() { return _image; }

	virtual void fire(Image * pixelMap, float x, float y, float angle);

	bool collide(Actor * a);
	virtual void collide();

	void setLinkPixelMap(Image* pixelMap) { _pixelMap = pixelMap; }
	float getRange() { return _range; }
	//bool getIsActive() { return _isActive; }

	float getEffectAngle() { return getAnglef(_x, _y, _fireX, _fireY); }

	void setIsActive(bool isActive) { _isActive = isActive; }
	void setFireCenter(float fireX, float fireY) { _fireX = fireX; _fireY = fireY; _x = fireX; _y = fireY; }


	FirePillar() {}
	~FirePillar() {}
};

