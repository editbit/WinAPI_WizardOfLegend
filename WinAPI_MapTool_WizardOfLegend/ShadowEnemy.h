#pragma once
#include "Enemy.h"

#define SHADOW_MAX_STATE 10

class ShadowEnemy :
	public Enemy
{
	Image *_img[SHADOW_MAX_STATE];
	int _delay[SHADOW_MAX_STATE];

	int _delayCount;
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

	ShadowEnemy() {}
	~ShadowEnemy() {}
};

