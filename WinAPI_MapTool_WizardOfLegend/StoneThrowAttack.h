#pragma once
#include "Skill.h"
#include "bullet.h"

#define STONE_THROW_BULLET_MAX 10

class StoneThrowAttack :
	public Skill
{
	Image *_motion[1];
	int _index, _count;

	Bullet *_bullet[STONE_THROW_BULLET_MAX];


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual Image * getImage() { return _motion[0]; }
	virtual int getChangableIndex() { return _motion[0]->getMaxFrameX() * 0.75f; }
	virtual int getFrameCount() { return 5; }

	virtual Image* attack(float x, float y, float angle);

	virtual void setMotion(int index, Image * img) { if (index >= 2) return; _motion[index] = img; }

	StoneThrowAttack() {}
	~StoneThrowAttack() {}
};

