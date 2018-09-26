#pragma once
#include "actor.h"
#include "tileMap.h"

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

	Enemy() : _routingIndex(0), _player(NULL) {}
	~Enemy() {}
};

