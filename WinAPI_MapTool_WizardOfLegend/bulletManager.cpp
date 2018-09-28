#include "stdafx.h"
#include "bullet.h"
#include "EnemyManager.h"
#include "bulletManager.h"
#include "tileNode.h"
#include "Stuff.h"

HRESULT BulletManager::init()
{
	if (_playerBullets.size() > 0 || _enemyBullets.size() > 0)
		release();

	_playerBullets.reserve(PLAYER_BULLET_MAX);
	_enemyBullets.reserve(ENEMY_BULLET_MAX);

	for (int i = 0; i < PLAYER_BULLET_MAX; ++i)
		_playerBullets.push_back(NULL);

	for (int i = 0; i < ENEMY_BULLET_MAX; ++i)
		_enemyBullets.push_back(NULL);

	//for (int i = 0; i < _playerBullets.size(); ++i)
	//{
	//	_playerBullets[i] = NULL;
	//}
	//
	//for (int i = 0; i < _enemyBullets.size(); ++i)
	//{
	//	_enemyBullets[i] = NULL;
	//}

	return S_OK;
}

void BulletManager::release()
{
	_playerBullets.clear();
	_enemyBullets.clear();
}


bool BulletManager::collidePlayer(Bullet* b)
{
	return b->collide(_player);
}

bool BulletManager::collideEnemy(Bullet* b)
{
	int i;
	vector<Enemy*>& enemys = _enemyManager->getEnemys();
	for (i = 0; i < enemys.size() ; ++i)
	{
		if (!enemys[i]->getIsActive())
			continue;

		b->collide(enemys[i]);

		if (!b->getIsActive())
			break;
	}

	return false;
}


void BulletManager::update()
{
	int x, y;
	for (int i = 0; i < _playerBullets.size(); ++i)
	{
		if (_playerBullets[i] == NULL)
			continue;
		_playerBullets[i]->update();

		collideEnemy(_playerBullets[i]);
		

		x = _playerBullets[i]->getX() / TILESIZE, y = _playerBullets[i]->getY() / TILESIZE;

		if (_tiles[y*TILEX + x].objType != OBJECT_NONE &&
			_tiles[y*TILEX + x].objType != OBJECT_BLOCK1)
		{
			if (_tiles[y*TILEX + x].obj->damaged(_player, _enemyManager->getEnemys()))
			{
				_tiles[y*TILEX + x].objType = OBJECT_NONE;
				_playerBullets[i]->setIsActive(false);
			}
		}

		if (!_playerBullets[i]->getIsActive())
			_playerBullets[i] = NULL;
	}

	for (int i = 0; i < _enemyBullets.size(); ++i)
	{
		if (_enemyBullets[i] == NULL)
			continue;
		_enemyBullets[i]->update();

		collidePlayer(_enemyBullets[i]);
		if (_dummy != NULL && _dummy->getIsActive())
			if (_dummy->collide(_enemyBullets[i]))
				_dummy->damaged(_enemyBullets[i]);

		x = _enemyBullets[i]->getX() / TILESIZE, y = _enemyBullets[i]->getY() / TILESIZE;
		//if (_tiles[y*TILEX + x].objType != OBJECT_NONE &&
		//	_tiles[y*TILEX + x].objType != OBJECT_BLOCK1)
		if (_tiles[y*TILEX + x].obj != NULL)
		{
			if (_tiles[y*TILEX + x].obj->damaged(_player, _enemyManager->getEnemys()))
			{
				_tiles[y*TILEX + x].objType = OBJECT_NONE;
				_enemyBullets[i]->setIsActive(false);
			}
		}

		if (!_enemyBullets[i]->getIsActive())
			_enemyBullets[i] = NULL;
		//RENDERMANAGER->addRender(_enemyBullets[i]->getHitBox().bottom, _enemyBullets[i]);
	}
}

void BulletManager::render()
{
}

