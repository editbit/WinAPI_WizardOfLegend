#pragma once
#include "gameNode.h"

enum SKILL_TYPE
{
	ATTACK_SKILL, DASH_SKILL
};

class Actor;
class EnemyManager;

class Skill :
	public GameNode
{
protected:
	Image * _iconImg;
	int _skillType;

	float _power;

	bool _isActive;

	vector<Bullet *>* _bulletList;

	Actor *_player;
	EnemyManager *_enemyManager;
	Image *_pixelMap;
public:
	virtual HRESULT init();	
	virtual void release();
	virtual void update();
	virtual void render();

	void setLinkBulletList(vector<Bullet *>* bulletList) { _bulletList = bulletList; }

	virtual Image * getImage() { return NULL; }

	virtual Image* attack(float x, float y, float angle) { return NULL; }
	virtual int getChangableIndex() { return 100; }
	virtual bool getIsActive() { return _isActive; }
	virtual int getFrameCount() { return 5; }

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em; }
	virtual void setLinkPlayer(Actor* player) { _player = player; }
	virtual void setLinkPixelMap(Image* pixelMap) { _pixelMap = pixelMap; }

	void renderIcon(float x, float y);

	int getSkillType() { return _skillType; }


	void setMotion(int index, Image * img) { return; }
	
	Skill() :_player(NULL), _enemyManager(NULL), _isActive(false), _power(10) {}
	Skill(Actor *p, EnemyManager *em) :_player(p), _enemyManager(em), _isActive(false), _power(10) {}
	~Skill() {}
};

