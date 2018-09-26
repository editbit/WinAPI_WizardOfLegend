#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "AStarTest.h"
#include "Wizard.h"
#include "ShadowEnemy.h"
#include "Magician.h"
#include "Rogue.h"
#include "EnemyManager.h"
#include "Bomb.h"


class GamePlayScene :
	public GameNode
{
	Wizard * _wizard;

	EnemyManager * _enemyManager;

	RoomList _roomList;
	vector<EnemyInfo> _enemyList;

	Image *_mapImg, *_pixelMapImg, *_miniMap, *_playerIcon;
	tileMap * _tileMap;
	tagTile *tiles;		//타일
	DWORD *attribute;	//속성

	POINT _camPos;
	RECT _camRect;
	int camSpeed;

	AStarTest * _aStarTest;


	Image * _aimImg;
	int count, stuffIndex;
public:
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void exit();

	void stuffFrameSetting();

	void loadEnemy();

	GamePlayScene() : _aStarTest(NULL) {}
	~GamePlayScene() {}
};

