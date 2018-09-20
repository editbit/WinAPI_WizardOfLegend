#pragma once
#include "actor.h"

class EnemyManager;

class Dash
	: public GameNode
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

	virtual HRESULT init();				//void�� �ᵵ�Ǵµ� �ʱ�ȭ�� ������ ����� �ٷ� �˷���
	virtual void release();
	virtual void update();
	virtual void render();

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	Dash() {}
	Dash(Actor *p, EnemyManager* em) : _player(p), _enemyManager(em), _isActive(true) { init(); }
	~Dash() {}
};

