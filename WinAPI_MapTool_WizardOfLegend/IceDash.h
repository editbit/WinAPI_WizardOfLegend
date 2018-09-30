#pragma once
#include "Dash.h"
#include "Dummy.h"
class IceDash : public Dash
{
	Dummy * _dummy;

public:

	virtual void executeDash(float x, float y);

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em;}
	virtual void setLinkPlayer(Actor* player) { _player = player; }

	virtual bool getIsActive() { return _dummy->getIsActive(); }

	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void endDash();

	IceDash() {}
	IceDash(Actor *p, EnemyManager* em) : Dash(p, em), _dummy(NULL) { init(); }
	~IceDash() {}
};

