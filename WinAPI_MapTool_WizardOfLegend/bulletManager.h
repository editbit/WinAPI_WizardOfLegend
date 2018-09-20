#pragma once
#include "singletonBase.h"

#define PLAYER_BULLET_MAX 20
#define ENEMY_BULLET_MAX 50

class Bullet;
class Actor;
class EnemyManager;
class tagTile;

class BulletManager : public SingletonBase<BulletManager>
{
	vector<Bullet*> _playerBullets;
	vector<Bullet*> _enemyBullets;

	vector<Bullet*>::iterator _viBullet;


	tagTile *_tiles;
	EnemyManager *_enemyManager;
	Actor *_player;

	RECT temp;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	bool collideEnemy(Bullet* b);
	bool collidePlayer(Bullet* b);

	vector<Bullet*>& getPlayerBullets() { return _playerBullets; }
	vector<Bullet*>& getEnemyBullets() { return _enemyBullets; }

	void setLinkTileMap(tagTile* tiles) { _tiles = tiles; }
	void setLinkPlayer(Actor * p) { _player = p; }
	void setLinkEnemyManaer(EnemyManager * em) { _enemyManager = em; }

	BulletManager() : _enemyManager(NULL), _player(NULL) {}
	~BulletManager() {}
};

