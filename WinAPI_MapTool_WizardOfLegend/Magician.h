#pragma once
#include "Enemy.h"
#include "bullet.h"
#include "WaterThrowAttack.h"
#include "StoneThrowAttack.h"

#define MAGICIAN_MAX_STATE 10

class Magician :
	public Enemy
{
	Image *_img[MAGICIAN_MAX_STATE];
	int _delay[MAGICIAN_MAX_STATE];

	float _shootingAngle;

	Skill * _attack;

	Bullet *tempBullet;
public:

	void frameSetting();

	virtual void attack();
	virtual void move();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	float getCenterY() { return _moveBox.bottom - _img[_state]->getFrameHeight() / 2; }

	Magician() {}
	~Magician() {}
};

