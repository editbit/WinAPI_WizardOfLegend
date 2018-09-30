#pragma once
#include "actor.h"
#include "tileMap.h"
#include "progressBar.h"

#define ENEMY_HPBAR_WIDTH 50
#define ENEMY_HPBAR_HEIGHT 5

#define APPEAR_COUNT 60

class Enemy :
	public Actor
{
protected:
	int _hitCount;
	int _routingIndex;
	vector<POINT> _routing;

	int tileIndex[4];

	Actor **_player;

	int _delayCount;

	ProgressBar * _hpBar;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void damaged(Actor *e);

	virtual void collide();
	void collisionPixel();

	void moveToPlayer();
	void setLinkPlayer(Actor ** player) { _player = player; }
	void setRouting(vector<POINT> routing) { _routing = routing; _routingIndex = _routing.size() - 1; }

	virtual void changeState(int state);

	virtual void freeze(float x, float y);

	Enemy() : _routingIndex(0), _player(NULL), _hpBar(NULL) {}
	virtual ~Enemy() {}
};

