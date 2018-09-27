#pragma once
#include "actor.h"

class EnemyManager;
class Enemy;

class Dummy :
	public Actor
{
	Image *_img;
	Image *_effectImg;

	RECT _attackBox;

	Actor *_player;
	EnemyManager* _enemyManager;

	vector<Enemy *> _enemys;
	vector<POINT> _enemysPos;

	bool _isCrash;
public:
	virtual void damaged(Actor *e);
	void generate(float x, float y, int index, int dir);
	void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em; }
	void setLinkPlayer(Actor* player) { _player = player; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Dummy() { _isActive = false; }
	~Dummy() {}
};

