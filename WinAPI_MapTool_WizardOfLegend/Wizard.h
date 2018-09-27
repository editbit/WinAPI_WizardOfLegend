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

	int _attackCount;
	int _axisX, _axisY;
	int tileIndex[4];

	int _attackIndex;

	int _formerInput;
	Image * _img[PLAYER_STATE_MAX], *_iconImg;
	int _delay[PLAYER_STATE_MAX];

	fPOINT _returnPoint;


	Inventory *_inven;

	IceDash *_iceDash;
	FireDash *_fireDash;

	Dash * _currentDash;
	Skill *_attack[2];
	int _currentAttack;

	EnemyManager *_enemyManager;

	ProgressBar * _hpBar;
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
	virtual void changeState(int state);
	virtual bool checkMovable(COLORREF color);
	void collideTileObject();
	void collidePixelMap();
	
	void setLinkEnemyManager(EnemyManager *enemys) { _enemyManager = enemys; }

	virtual void damaged(Actor *e);
	void attackStuff();
	virtual void attack();
	virtual void move();
	virtual void collide();
	virtual void drawUI() {}

	float getAttackAngle() { return _attackAngle; }

	Wizard() : _enemyManager(NULL), _iceDash(NULL), _hpBar(NULL) {}
	~Wizard() {}

};


//virtual bool collide(Actor* a);
//virtual void throwed(float speed, float angle);
//virtual void attack() {}
//virtual void damaged(Actor *e) {}