#include "stdafx.h"
#include "GamePlayScene.h"


HRESULT GamePlayScene::init()
{
	_miniMap = IMAGEMANAGER->findImage("miniMapImage");	
	_mapImg = IMAGEMANAGER->findImage("tileMapImage");
	_pixelMapImg = IMAGEMANAGER->findImage("tileMapPixel");
	_playerIcon = IMAGEMANAGER->findImage("playerIcon");

	_aimImg = IMAGEMANAGER->findImage("aim");

	_tileMap = SAVEDATA->getTileMap();
	//_tileMap = new tileMap;
	//_tileMap->init();
	tiles = _tileMap->getTiles();
	attribute = _tileMap->getAttribute();
	
	_roomList = _tileMap->getRoomList();
	_enemyList = _tileMap->getEnemyList();

	_wizard = new Wizard;
	_wizard->setLinkTileMap(_tileMap);
	_wizard->setPixelMap(_pixelMapImg);

	_enemyManager = new EnemyManager;
	_enemyManager->setLinkPlayer(_wizard);
	_enemyManager->setLinkTileMap(_tileMap);
	_enemyManager->setPixelMap(_pixelMapImg);
	_enemyManager->init();


	//_wizard->setLinkTileMap(_tileMap);
	_wizard->setLinkEnemyManager(_enemyManager);
	_wizard->init();

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


	BULLETMANAGER->init();
	BULLETMANAGER->setLinkEnemyManaer(_enemyManager);
	BULLETMANAGER->setLinkPlayer(_wizard);
	BULLETMANAGER->setLinkTileMap(_tileMap->getTiles());
	Bomb::setLinkTileMap(_tileMap->getTiles());
	return S_OK;
}

void GamePlayScene::release()
{
	//_tileMap->release();
	//SAFE_DELETE(_tileMap);

	_wizard->release();
	SAFE_DELETE(_wizard);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

}

void GamePlayScene::update()
{
	_tileMap->update();

	_wizard->update();
	_enemyManager->update();

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

	BULLETMANAGER->update();

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
	}


	if (_wizard->getState() != WIZARD::FALL)
		_aimImg->rotateRender(getMemDC(), _wizard->getX() - CAM->getX(), _wizard->getY() - CAM->getY(), _wizard->getAttackAngle());
	RENDERMANAGER->render(getMemDC());

	if (KEYMANAGER->isToggleKey('M'))
	{
		//_miniMap->render(getMemDC(), (WINSIZEX - _miniMap->getWidth())*0.5f, (WINSIZEY - _miniMap->getHeight()) *0.5f);
		_miniMap->alphaRender(getMemDC(),
			(WINSIZEX)*0.5f - (_wizard->getX() / MINIMAP_RATE - 15), (WINSIZEY) *0.5f - (_wizard->getY() / MINIMAP_RATE - 15), 200);
		_playerIcon->render(getMemDC(), (WINSIZEX)*0.5f, (WINSIZEY) *0.5f);
	}
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
		case EARTH_BOSS:
			temp = new EarthBoss;
			break;
		}

		if (temp == NULL) continue;

		//temp->init();
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

