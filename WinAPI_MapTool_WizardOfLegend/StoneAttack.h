#pragma once
#include "Skill.h"
#include "AttackBullet.h"

#define ATTACK_BULLET 3

class StoneAttack :
	public Skill
{
	Image *_motion[2];
	int _index, _count;

	AttackBullet *_bullet[ATTACK_BULLET];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual Image * getImage() { return _motion[_attackCount]; }
	virtual int getChangableIndex() { return _motion[_attackCount]->getMaxFrameX() * 0.75f; }

	virtual Image* attack(float x, float y, float angle);

	virtual void setMotion(int index, Image * img) { if (index >= 2) return; _motion[index] = img; }

	StoneAttack() {}
	~StoneAttack() {}
};

