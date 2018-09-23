#pragma once
#include "actor.h"
#include "EnemyManager.h"
#include "Inventory.h"
#include "Dummy.h"
#include "progressBar.h"
#include "IceDash.h"
#include "FireDash.h"
#include "StoneAttack.h"

#define PLAYER_STATE_MAX 10


class Wizard :
	public Actor
{
	float _attackAngle;

	int _axisX, _axisY;
	int tileIndex[4];

	int _attackIndex;

	int _formerInput;
	Image * _aimImg;
	Image * _img[PLAYER_STATE_MAX];
	int _delay[PLAYER_STATE_MAX];

	fPOINT _returnPoint;


	Inventory *_inven;

	IceDash *_iceDash;
	FireDash *_fireDash;

	Dash * _currentDash;
	Skill *_attack;

	EnemyManager *_enemyManager;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void settingReturnPoint();
	void settingDir();
	void settingAngle();
	void inputProcess();
	void frameSetting();
	void changeState(int state);
	void collideTileObject();
	void collidePixelMap();
	
	void setLinkEnemyManager(EnemyManager *enemys) { _enemyManager = enemys; }

	virtual void damaged(Actor *e);
	void attackStuff();
	virtual void attack();
	virtual void move();
	virtual void collide();
	virtual void drawUI() {}


	Wizard() : _enemyManager(NULL), _iceDash(NULL) {}
	~Wizard() {}

};


//virtual bool collide(Actor* a);
//virtual void throwed(float speed, float angle);
//virtual void attack() {}
//virtual void damaged(Actor *e) {}