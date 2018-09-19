#pragma once
#include "gameNode.h"
#include "bullet.h"

class bulletManager : public GameNode
{
	vector<bullet*> _vBullet;
	vector<bullet*>::iterator _viBullet;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	vector<bullet*> getvBullet() { return _vBullet; }
	bulletManager() {}
	~bulletManager() {}
};

