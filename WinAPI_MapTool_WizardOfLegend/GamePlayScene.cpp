#include "stdafx.h"
#include "GamePlayScene.h"


HRESULT GamePlayScene::init()
{
	_mapImg = IMAGEMANAGER->findImage("tileMapImage");
	_pixelMapImg = IMAGEMANAGER->findImage("tileMapPixel");

	_tileMap = new tileMap;
	_tileMap->init();
	tiles = _tileMap->getTiles();
	attribute = _tileMap->getAttribute();
	
	_roomList = _tileMap->getRoomList();
	_enemyList = _tileMap->getEnemyList();

	_wizard = new Wizard;
	_wizard->init();
	_wizard->setLinkTileMap(_tileMap);
	_wizard->setPixelMap(_pixelMapImg);

	_enemyManager = new EnemyManager;
	_enemyManager->init();
	_enemyManager->setLinkPlayer(_wizard);
	_enemyManager->setLinkTileMap(_tileMap);
	_enemyManager->setPixelMap(_pixelMapImg);


	//_wizard->setLinkTileMap(_tileMap);
	_wizard->setLinkEnemyManager(_enemyManager);

	CAM->setDrawRange(WINSIZEX, WINSIZEY);
	CAM->setMaxRange(TILESIZEX, TILESIZEY);
	//CAM->setRoomSize(RectMake(100, WINSIZEY, WINSIZEX * 2, WINSIZEY * 2));


	_camPos = {WINSIZEX / 2, WINSIZEY / 2 };

	if (_aStarTest == NULL)
	{
		_aStarTest = ASTAR;
		_aStarTest->setTankMap(_tileMap);

	}

	loadEnemy();


	RENDERMANAGER->setLinkTileMap(_tileMap);

	camSpeed = 0;
	stuffIndex = count = 0;


	Bomb::setLinkTileMap(_tileMap->getTiles());
	return S_OK;
}

void GamePlayScene::release()
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);

	_wizard->release();
	SAFE_DELETE(_wizard);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

}

void GamePlayScene::update()
{
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		if (!KEYMANAGER->isOnceKeyDown('P'))
			return;
	}


	_tileMap->update();

	_wizard->update();
	_enemyManager->update();

	{
		RECT temp, roomCollisionBox;
		int i;
		for (i = 0; i < _roomList.rc.size(); ++i)
		{
			if (IntersectRect(&temp, &_wizard->getMoveBox(), &_roomList.rc[i]))
			{
				roomCollisionBox = { _roomList.rc[i].left + TILESIZE * 2, _roomList.rc[i].top + TILESIZE * 2, _roomList.rc[i].right - TILESIZE * 2, _roomList.rc[i].bottom - TILESIZE * 2 };
				//if(temp.right - temp.left >= WIZARD::MOVEBOX_WIDTH && temp.bottom - temp.top >= WIZARD::MOVEBOX_HEIGHT)
				if (IntersectRect(&temp, &_wizard->getMoveBox(), &roomCollisionBox))
				{
					CAM->setRoomSize(_roomList.rc[i]);
					_enemyManager->setCurrentRoom(i + 1);
				}
				break;
			}
		}
		if (i == _roomList.rc.size())
		{
			_enemyManager->setCurrentRoom(0);
			CAM->setRoomSize(RectMake(0, 0, TILESIZEX, TILESIZEY));
		}
	}
	stuffFrameSetting();
	CAM->videoShooting(_wizard->getX(), _wizard->getY());
}

void GamePlayScene::render()
{
	_mapImg->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY);

	RENDERMANAGER->addRender(_wizard->getMoveBox().bottom - _wizard->getZ(), _wizard);

	if (KEYMANAGER->isToggleKey('9'))
	{
		IMAGEMANAGER->findImage("tileMapPixel")->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), CAM->getCamWidth(), CAM->getCamHeight());

		for (int i = 0; i < _roomList.rc.size(); ++i)
		{
			Rectangle(getMemDC(), _roomList.rc[i], CAM->getX(), CAM->getY());
		}
	}
	RENDERMANAGER->render(getMemDC());

}

void GamePlayScene::exit()
{
	SCENEMANAGER->loadScene("StartScene");
}

void GamePlayScene::stuffFrameSetting()
{
	count = (count + 1) % 100;
	if (count == 0)
	{
		stuffIndex = (stuffIndex + 1) % (IMAGEMANAGER->findImage("함정2")->getMaxFrameX() + 1);
		IMAGEMANAGER->findImage("함정2")->setFrameX(stuffIndex);
	}
}

void GamePlayScene::loadEnemy()
{
	Enemy * temp;
	//for (int i = 0; i < 5; ++i)
	//{
	//	temp = new ShadowEnemy;
	//	temp->init();
	//	temp->setX(_wizard->getX() + RND->getInt(100));
	//	temp->setY(_wizard->getY() + RND->getInt(100));
	//	_enemyManager->addEnemy(temp);
	//}

	
	for (int i = 0; i < _roomList.rc.size(); ++i)
		_enemyManager->addArea();

	for (int i = 0; i < _enemyList.size(); ++i)
	{
		temp = NULL;
		switch (_enemyList[i].type)
		{
		case SHADOW:
			temp = new ShadowEnemy;
			break;
		case MAGE:
			temp = new Magician;
			break;
		case ROGUE:
			temp = new Rogue;
			break;
		}

		if (temp == NULL) continue;

		temp->init();
		temp->setX(_enemyList[i].pos.x);
		temp->setY(_enemyList[i].pos.y);

		int j;
		for (j = 0; j < _roomList.rc.size(); ++j)
		{
			if (PtInRect(&_roomList.rc[j], _enemyList[i].pos))
			{
				_enemyManager->addEnemy(temp, j + 1);
				break;
			}
		}
		if(j == _roomList.rc.size())
			_enemyManager->addEnemy(temp, 0);
	}
}

