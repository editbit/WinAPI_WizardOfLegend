#pragma once
#include "Skill.h"

class EnemyManager;

class Dash
	: public Skill
{
protected:
	float _x, _y;

	Actor *_player;
	EnemyManager *_enemyManager;
	Image *_pixelMap;

	int _timer, _count;
	bool _isActive;
public:

	virtual void executeDash(float x, float y);

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em; }
	virtual void setLinkPlayer(Actor* player) { _player = player; }
	virtual void setLinkPixelMap(Image* pixelMap) { _pixelMap = pixelMap; }

	virtual bool getIsActive() { return _isActive; }

	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPosition(float x, float y) { _x = x; _y = y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	Dash() { init(); }
	Dash(Actor *p, EnemyManager* em) : _player(p), _enemyManager(em), _isActive(true) { init(); }
	~Dash() {}
};

