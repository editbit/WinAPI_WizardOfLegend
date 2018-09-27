#pragma once
#include "Enemy.h"
#include "StoneThrowAttack.h"
#include "StoneAttack.h"
#include "WaterThrowAttack.h"
#include "Skill.h"

#define EARTH_BOSS_MAX_STATE 10
#define EARTH_BOSS_ATTACK_MAX 3

class EarthBoss :
	public Enemy
{
	Image *_img[EARTH_BOSS_MAX_STATE];
	int _delay[EARTH_BOSS_MAX_STATE];

	float _shootingAngle;

	Skill * _attack[EARTH_BOSS_ATTACK_MAX];
	int _currentAttack;

public:

	void frameSetting();

	virtual void attack();
	virtual void move();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	float getCenterY() { return _moveBox.bottom - _img[_state]->getFrameHeight() / 2; }

	virtual void changeState(int state);
	virtual void damaged(Actor *e);
	void settingDir();

	EarthBoss() {}
	~EarthBoss() {}
};

