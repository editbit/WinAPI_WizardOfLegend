#pragma once
#include "Skill.h"
#include "IceDash.h"
#include "FireDash.h"
#include "StoneAttack.h"
#include "WaterThrowAttack.h"
#include "StoneThrowAttack.h"
#include "WaterCircleAttack.h"

#define EQUIP_MAX 3

class Inventory :
	public GameNode
{
	float _x, _y;

	Image *_img;

	int _selectIndex;

	Skill *_currentSkill[EQUIP_MAX];
	POINT _currentSkillPos[EQUIP_MAX];
	POINT _equipkillPos[EQUIP_MAX];

	vector<Skill*> _skillList;
	vector<POINT> _iconPos;

	Dash * _currentDash;

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
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void renderEquipSkill();

	void initSkillRECT();

	bool getIsActive() { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }

	Skill* getCurrentDash() { return _currentSkill[1]; }
	Skill* getAttackSkill(int index) { if (index == 1) return _currentSkill[0];  return _currentSkill[index]; }

	void changeSkill();
	void selectSkill();

	void setLinkPixelMap(Image * pixelMap) { _pixelMap = pixelMap; }
	void setLinkPlayer(Actor * player) { _player = player; }
	void setLinkEnemyManager(EnemyManager *enemys) { _enemyManager = enemys;	}


	void openInven() { _isActive = true; _selectIndex = -1; }

	Inventory() {}
	~Inventory() {}
};

