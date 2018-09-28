#pragma once
#include "Enemy.h"

#define ROGUE_MAX_STATE 10

class Rogue :
	public Enemy
{
	Image *_img[ROGUE_MAX_STATE];
	int _delay[ROGUE_MAX_STATE];

public:
	void frameSetting();

	virtual void attack();
	virtual void move();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	float getCenterY() { return _moveBox.bottom - _img[_state]->getFrameHeight() / 2; }

	Rogue() {}
	virtual ~Rogue() {}
};

