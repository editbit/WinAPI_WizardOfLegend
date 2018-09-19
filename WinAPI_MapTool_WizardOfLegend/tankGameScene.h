#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "tank.h"
#include "TankEnemy.h"
#include "AStarTest.h"

#define ENEMY_NUM 100

class tankGameScene : public GameNode
{
private:
	tileMap * _tankMap;
	tank* _tank;
	TankEnemy* _enemy;
	int enemyRoutingIndex;

	AStarTest * _aStarTest;
	int dirCount[ENEMY_NUM];

	vector<RECT> _routing;
	vector<POINT> temp[ENEMY_NUM];


	Image * _mapImg, *_tileMap;

	int routingCount;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual void exit();

	tankGameScene() : _aStarTest(NULL) {}
	~tankGameScene() {}
};