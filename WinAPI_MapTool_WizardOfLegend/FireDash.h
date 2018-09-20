#pragma once
#include "Dash.h"
#include "FirePillar.h"

#define FIRE_DASH_PILLAR_MAX 10

class FireDash :
	public Dash
{
	FirePillar *_firePillar[FIRE_DASH_PILLAR_MAX];

public:
	virtual void executeDash(float x, float y);

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em;  }
	virtual void setLinkPlayer(Actor* player) { _player = player;  }

	virtual bool getIsActive() { return _isActive; }

	void fireBullet();

	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();



	FireDash(Actor *p, EnemyManager* em) : Dash(p, em) { init(); }
	FireDash() {}
	~FireDash() {}
};

