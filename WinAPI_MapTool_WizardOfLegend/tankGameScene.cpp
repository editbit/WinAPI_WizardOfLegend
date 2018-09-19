#include "stdafx.h"
#include "tankGameScene.h"

HRESULT tankGameScene::init(void)
{
	//타일이미지
	_tileMap = IMAGEMANAGER->addFrameImage("tilemap", "Texture/pac-man_map_384x128_12x4.bmp.bmp", 348, 128, 12, 4);
	_mapImg = IMAGEMANAGER->addImage("tileMapImage", TILESIZEX, TILESIZEY);

	//탱크맵 클래스 생성
	_tankMap = new tileMap;
	_tankMap->init();

	//탱크 클래스 생성
	_tank = new tank;
	_tank->init();
	_tank->setTankMapLink(_tankMap);
	_tank->setTankPosition(22 * TILEX + 14);

	_enemy = new TankEnemy[ENEMY_NUM];

	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		_enemy[i].init();
		_enemy[i].setTankMapLink(_tankMap);
		_enemy[i].setEnemyPosition(25 *  TILEX + 17);
		_enemy[i].setSpeed(getFromIntTo(15, 39) / 10.0f);
	}

	if (_aStarTest == NULL)
	{
		_aStarTest = ASTAR;
		_aStarTest->setTankMap(_tankMap);
	}


	dirCount[0] = dirCount[1] = dirCount[2] = 0; enemyRoutingIndex = 0;

	RENDERMANAGER->setLinkTileMap(_tankMap);

	CAM->setMaxRange(TILESIZEX, TILESIZEY);
	CAM->setDrawRange(WINSIZEX, WINSIZEY);

	return S_OK;
}

void tankGameScene::release(void)
{
	SAFE_DELETE(_tankMap);
	SAFE_DELETE(_tank);
	SAFE_DELETE_ARRAY(_enemy);
}

void tankGameScene::update(void)
{
	if (KEYMANAGER->isToggleKey('A'))
		return;
	_tankMap->update();
	_tank->update();

	//for (int i = 0; i < 3; ++i)
	{

		int enemyIdX = _enemy[enemyRoutingIndex].getX() / TILESIZE, enemyIdY = _enemy[enemyRoutingIndex].getY() / TILESIZE;
		int tankIdX = _tank->getX() / TILESIZE, tankIdY = _tank->getY() / TILESIZE;

		if (!(enemyIdX == tankIdX && enemyIdY == tankIdY))
		{
			//if (temp.size() <= 0 || dirCount < temp.size() * 2 / 3 || dirCount < 4)		// 길을 결정하는 조건.
			{
				temp[enemyRoutingIndex] = _aStarTest->startPathFind(enemyIdX, enemyIdY, tankIdX, tankIdY, 300);
				dirCount[enemyRoutingIndex] = temp[enemyRoutingIndex].size() - 1;
			}

			//if (dirCount >= 0)
			for (int i = 0; i < ENEMY_NUM; ++i)
			{
				if (temp[i].size() <= 0) continue;
				if (dirCount[i] <= 0) continue;

				int nextIdX = temp[i][dirCount[i]].x,
					nextIdY = temp[i][dirCount[i]].y;
				int enemyIdX = _enemy[i].getX() / TILESIZE, enemyIdY = _enemy[i].getY() / TILESIZE;

				if (enemyIdX == nextIdX && enemyIdY == nextIdY)
				{
					dirCount[i] -= 1;
				}
				else if (enemyIdX - 1 == nextIdX && enemyIdY == nextIdY)  // left
				{
					_enemy[i].setDirection(LEFT);
				}
				else if (enemyIdX + 1 == nextIdX && enemyIdY == nextIdY)  // right
				{
					_enemy[i].setDirection(RIGHT);
				}
				else if (enemyIdX == nextIdX && enemyIdY - 1 == nextIdY)  // up
				{
					_enemy[i].setDirection(UP);
				}
				else if (enemyIdX == nextIdX && enemyIdY + 1 == nextIdY)  // down
				{
					_enemy[i].setDirection(DOWN);
				}
				_enemy[i].update();
			}

		}

		enemyRoutingIndex = (enemyRoutingIndex + 1) % ENEMY_NUM;
	}

	CAM->videoShooting(_tank->getX(), _tank->getY());
}

void tankGameScene::render(void)
{
	//_mapImg->render(getMemDC(), -CAM->getX(), -CAM->getY());
	_mapImg->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), CAM->getCamWidth(), CAM->getCamHeight());
	_tankMap->render();

	//_tank->render();
	RENDERMANAGER->addRender(_tank->getRC().bottom, _tank);

	for (int i = 0; i < ENEMY_NUM; ++i)
		RENDERMANAGER->addRender(_enemy[i].getRC().bottom, &_enemy[i]);


	


	RENDERMANAGER->render(getMemDC());
}

void tankGameScene::exit()
{
	SCENEMANAGER->loadScene("StartScene");
}
