#pragma once
#include "actor.h"

class EnemyManager;

class Dash
	: public GameNode
{
protected:
	Actor *_player;
	EnemyManager *_enemyManager;

	bool _isActive;
public:

	virtual void executeDash(float x, float y);

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em; }
	virtual void setLinkPlayer(Actor* player) { _player = player; }

	virtual bool getIsActive() { return _isActive; }

	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();


	Dash() {}
	Dash(Actor *p, EnemyManager* em) : _player(p), _enemyManager(em), _isActive(true) {}
	~Dash() {}
};

