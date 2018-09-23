#pragma once
#include "Skill.h"
#include "WaterThrowBullet.h"

#define STONE_THROW_MAX 4

class WaterThrowAttack :
	public Skill
{

	Image *_motion[2];
	int _index, _count;

	int _attackCount;

	WaterThrowBullet *_bullet[STONE_THROW_MAX];


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual Image * getImage() { return _motion[_attackCount]; }
	virtual int getChangableIndex() { return _motion[_attackCount]->getMaxFrameX() * 0.75f; }
	virtual int getFrameCount() { return 5; }

	virtual Image* attack(float x, float y, float angle);

	virtual void setMotion(int index, Image * img) { if (index >= 2) return; _motion[index] = img; }

	WaterThrowAttack() {}
	~WaterThrowAttack() {}
};

