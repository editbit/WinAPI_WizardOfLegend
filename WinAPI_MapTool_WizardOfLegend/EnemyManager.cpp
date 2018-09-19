#include "stdafx.h"
#include "EnemyManager.h"


HRESULT EnemyManager::init()
{
	_aStar = ASTAR;
	_routingIndex = 0;
	_currentRoom = 0;
	
	if (_enemys.size() > 0)
		release();

	_enemys.push_back(vector<Enemy *>());

	return S_OK;
}

void EnemyManager::release()
{
	for (int i = 0; i < _enemys.size(); ++i)
	{
		for (int j = 0; j < _enemys[i].size(); ++j)
		{
			_enemys[i][j]->release();
			SAFE_DELETE(_enemys[i][j]);
		}
		_enemys[i].clear();
	}
	_enemys.clear();
}

void EnemyManager::update()
{
	if (_enemys[_currentRoom].size() <= 0)
		return;

	if (_enemys[_currentRoom][_routingIndex]->getIsActive())
	{
		_enemys[_currentRoom][_routingIndex]->setRouting(
			_aStar->startPathFind(
				_enemys[_currentRoom][_routingIndex]->getX() / TILESIZE,
				_enemys[_currentRoom][_routingIndex]->getY() / TILESIZE,
				_player->getX() / TILESIZE,
				_player->getY() / TILESIZE,
				50));
	}
	_routingIndex++;
	if (_routingIndex >= _enemys[_currentRoom].size())
		_routingIndex = 0;


	int camX = CAM->getX(), camY = CAM->getY();

	for (int i = 0; i < _enemys[_currentRoom].size(); ++i)
	{
		if (!_enemys[_currentRoom][i]->getIsActive()) continue;

		_enemys[_currentRoom][i]->update();

		if (_enemys[_currentRoom][i]->getX() > camX - 100 && _enemys[_currentRoom][i]->getX() < camX + WINSIZEX + 100 &&
			_enemys[_currentRoom][i]->getY() > camY - 100 && _enemys[_currentRoom][i]->getY() < camY + WINSIZEY + 100)
		{
			RENDERMANAGER->addRender(_enemys[_currentRoom][i]->getMoveBox().bottom - _enemys[_currentRoom][i]->getZ(), _enemys[_currentRoom][i]);
		}
	}


}

void EnemyManager::render()
{
}


void EnemyManager::setCurrentRoom(int room)
{
	if (_currentRoom == room)
		return;

	_currentRoom = room;
	if (_currentRoom < 0 || _currentRoom >= _enemys.size())
		_currentRoom = 0;

	_routingIndex = 0;
}

void EnemyManager::addEnemy(Enemy * enemy, int room)
{
	if (room < 0 || room >= _enemys.size())
		room = 0;

	enemy->setLinkPlayer(&_player);
	enemy->setLinkTileMap(_tileMap);
	enemy->setPixelMap(_pixelMap);
	_enemys[room].push_back(enemy);
}

