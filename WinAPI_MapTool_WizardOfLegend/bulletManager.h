#pragma once
#include "gameNode.h"
#include "bullet.h"

class BulletManager : public GameNode
{
	vector<Bullet*> _vBullet;
	vector<Bullet*>::iterator _viBullet;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	vector<Bullet*> getvBullet() { return _vBullet; }
	BulletManager() {}
	~BulletManager() {}
};

