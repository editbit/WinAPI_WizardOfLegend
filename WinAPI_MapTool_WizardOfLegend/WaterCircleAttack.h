#pragma once
#include "Skill.h"
#include "WaterCircleBullet.h"

#define WATER_CIRCLE_BAX 8

class WaterCircleAttack :
	public Skill
{
	Image *_motion[3];
	int _index, _count;

	int _attackCount;

	WaterCircleBullet *_bullet[WATER_CIRCLE_BAX];
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


	WaterCircleAttack() {}
	~WaterCircleAttack() {}
};

