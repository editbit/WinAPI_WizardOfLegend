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
	int _attackCount;
	int _frameCount, _attackIndex;
	int _attackDistance;

	int _coolTime, _coolTimeCount;

	float _speed;
	float _power;

	bool _isActive;

	vector<Bullet *>* _bulletList;

	string _description;

	Actor *_player;
	EnemyManager *_enemyManager;
	Image *_pixelMap;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool isUsable() { return _coolTime == _coolTimeCount; }

	void setLinkBulletList(vector<Bullet *>* bulletList) { _bulletList = bulletList; }

	virtual Image * getImage() { return NULL; }

	virtual Image* attack(float x, float y, float angle) { return NULL; }
	virtual int getChangableIndex() { return 100; }
	virtual bool getIsActive() { return _isActive; }
	void setFrameCount(int frameCount) { _frameCount = frameCount; }
	int getFrameCount() { return _frameCount; }

	virtual void setLinkEnemyManager(EnemyManager *em) { _enemyManager = em; }
	virtual void setLinkPlayer(Actor* player) { _player = player; }
	virtual void setLinkPixelMap(Image* pixelMap) { _pixelMap = pixelMap; }

	void renderIcon(float x, float y);

	void setPower(float power) { _power = power; }

	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }
	void setAttackDistance(int attackDistance) { _attackDistance = attackDistance; }
	void setAttackIndex(int attackIndex) { _attackIndex = attackIndex; }
	int getAttackIndeX() { return _attackIndex; }
	int getSkillType() { return _skillType; }
	int getAttackCount() { return _attackCount; }
	void setAttackCount(int attackCount) { _attackCount = attackCount; }

	string getDescription() const { return _description; } 

	virtual void setMotion(int index, Image * img) { return; }
	
	Skill() :_player(NULL), _enemyManager(NULL), _isActive(false), _power(10), _description(""), _attackDistance(80), _speed(0){}
	Skill(Actor *p, EnemyManager *em) :_player(p), _enemyManager(em), _isActive(false), _power(10), _description(""), _attackDistance(80), _speed(0){}
	~Skill() {}
};

