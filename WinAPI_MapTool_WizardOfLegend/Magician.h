#pragma once
#include "Enemy.h"
#include "bullet.h"

#define MAGICIAN_MAX_STATE 10

class Magician :
	public Enemy
{
	Image *_img[MAGICIAN_MAX_STATE];
	int _delay[MAGICIAN_MAX_STATE];

	int _delayCount;

	float _shootingAngle;

	Bullet *tempBullet;
public:

	void frameSetting();

	virtual void attack();
	virtual void damaged(Actor *e);
	virtual void move();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	float getCenterY() { return _moveBox.bottom - _img[_state]->getFrameHeight() / 2; }

	Magician() {}
	~Magician() {}
};

