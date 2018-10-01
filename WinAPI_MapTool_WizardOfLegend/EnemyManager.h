#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "AStarTest.h"

class EnemyManager :
	public GameNode
{
	int _currentRoom;
	vector<vector<Enemy *>> _enemys;
	vector<bool> _isEnemy;

	Actor *_player, *_playerSour;
	tileMap * _tileMap;
	Image * _pixelMap;

	AStarTest *_aStar;
	int _routingIndex, _enemysCount;
public:
	virtual HRESULT init();	
	virtual void release();
	virtual void update();
	virtual void render();

	void addArea();
	void setCurrentRoom(int room);
	int getCurrentRoom() { return _currentRoom; }
	vector<Enemy *>& getEnemys() { return _enemys[_currentRoom]; }


	void addEnemy(Enemy * enemy, int room = 0, bool isSour = false);

	void setLinkTileMap(tileMap *tile) { _tileMap = tile; }
	void setPixelMap(Image * pixelMap) { _pixelMap = pixelMap; }
	void setLinkPlayer(Actor * player) { _playerSour = _player = player; }

	void changeDummy(Actor * player) { _player = player; }

	bool isEnemys(int roomNum) { return _isEnemy[roomNum]; }
	bool isEnemys();

	EnemyManager() : _aStar(NULL)  {}
	~EnemyManager() {}
};

