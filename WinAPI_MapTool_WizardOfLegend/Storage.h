#pragma once
#include "Stuff.h"
#include "Skill.h"
#include "IceDash.h"
#include "FireDash.h"
#include "StoneAttack.h"
#include "WaterThrowAttack.h"
#include "StoneThrowAttack.h"
#include "WaterCircleAttack.h"

class Storage :
	public Stuff
{
	float _x, _y;

	Image *_uiImg;

	int _selectIndex;

	vector<Skill*> _skillList;
	vector<POINT> _iconPos;

	bool _isActive;

	IceDash *_iceDash;
	FireDash *_fireDash;

	StoneAttack *_stoneAttack;
	WaterThrowAttack *_waterThrowAttack;
	StoneThrowAttack * _stoneThrowAttack;
	WaterCircleAttack *_waterCircleAttack;

	Actor *_player;
	EnemyManager *_enemyManager;

	Image * _pixelMap;
	Image * _iconBoxImg[2];

public:
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();

	virtual bool checkAttack() { return false; }

	virtual bool damaged(Actor * a, vector<Enemy*>& em) { return false; }
	virtual bool collide(Actor * actor) { return false; }
	virtual bool collide(Actor * actor, vector<Enemy*>& em) { return false; }



	/////////// 인벤
	void initSkillRECT();

	bool getIsActive() { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }

	void changeSkill();
	void selectSkill();

	void setLinkPixelMap(Image * pixelMap) { _pixelMap = pixelMap; }
	void setLinkPlayer(Actor * player) { _player = player; }
	void setLinkEnemyManager(EnemyManager *enemys) { _enemyManager = enemys; }


	void openInven() { _isActive = true; _selectIndex = -1; }

	Storage() : Stuff() { _state = 1; }
	Storage(Image * img, POINT renderPos);
	~Storage() {}

};

