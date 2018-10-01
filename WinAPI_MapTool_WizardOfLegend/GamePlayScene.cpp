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
	
	_wizard = SAVEDATA->getPlayer();
	_enemyManager = SAVEDATA->getEnemyManager();
	if (_wizard == NULL)
	{

		_wizard = new Wizard;
		_wizard->setLinkTileMap(_tileMap);
		_wizard->setPixelMap(_pixelMapImg);

		_enemyManager = new EnemyManager;
		_enemyManager->setLinkPlayer(_wizard);
		_enemyManager->setLinkTileMap(_tileMap);
		_enemyManager->setPixelMap(_pixelMapImg);


		_inven = new Inventory;
		_inven->setLinkEnemyManager(_enemyManager);
		_inven->setLinkPixelMap(_pixelMapImg);
		_inven->setLinkPlayer(_wizard);
		_inven->init();

		_wizard->setLinkEnemyManager(_enemyManager);
		_wizard->setLinkInven(_inven);
		_wizard->init();

		SAVEDATA->setPlayer(_wizard);
		SAVEDATA->setEnemyManager(_enemyManager);
	}

	_enemyManager->init();
	_wizard->setX(SAVEDATA->getStartPos().x);
	_wizard->setY(SAVEDATA->getStartPos().y);
	_wizard->settingCurrentSkill();

	CAM->setDrawRange(WINSIZEX, WINSIZEY);
	CAM->setMaxRange(TILESIZEX, TILESIZEY);


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

	_currentStage = 0;

	CAM->videoShooting(_wizard->getX(), _wizard->getY());
	EFFECTMANAGER->play("플레이어등장", _wizard->getX(), _wizard->getY() - 231);

	SOUNDMANAGER->playBgm("게임음악", _soundVolume);
	return S_OK;
}

void GamePlayScene::release()
{
}

void GamePlayScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		if (!UIMANAGER->getIsBlockingUI())
			UIMANAGER->openUI(EXIT_MENU);
		else
			UIMANAGER->setIsBlockingUI(false);
	}
	if (UIMANAGER->getIsBlockingUI())
	{
		UIMANAGER->update();
		return;
	}

	if (!_wizard->getIsActive())
	{
		_wizard->setHp(_wizard->getMaxHp());
		_wizard->changeState(WIZARD::IDLE);
		_wizard->setIsActive(true);
		SAVEDATA->setCurrentStage(0);
		SAVEDATA->setMapName("Stage/Stage" + to_string(SAVEDATA->getCurrentStage()) + ".map");
		SCENEMANAGER->loadScene("LoadingScene");
		RENDERMANAGER->clear();
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (!_inven->getIsActive())
		{
			int startX = (int)(_wizard->getX() / TILESIZE) - 1, startY = (int)(_wizard->getY() / TILESIZE) - 1;
			for (int i = startY; i < startY + 2; ++i)
			{
				for (int j = startX; j < startX + 2; ++j)
				{
					if (tiles[i * TILEX + j].objType == OBJECT_STORAGE)
					{
						_wizard->openInven();
						break;
					}
				}
			}
		}
		else
		{
			_inven->setIsActive(false);
			_wizard->settingCurrentSkill();
		}
	}

	_tileMap->update();

	_wizard->update();
	_enemyManager->update();

	RECT temp, roomCollisionBox;
	int i;
	for (i = 0; i < _roomList.rc.size(); ++i)
	{
		if (_enemyManager->isEnemys(i+1) && IntersectRect(&temp, &_wizard->getMoveBox(), &_roomList.rc[i]))
		{
			roomCollisionBox = { _roomList.rc[i].left + TILESIZE * 2, _roomList.rc[i].top + TILESIZE * 2, _roomList.rc[i].right - TILESIZE * 2, _roomList.rc[i].bottom - TILESIZE * 2 };
			//if(temp.right - temp.left >= WIZARD::MOVEBOX_WIDTH && temp.bottom - temp.top >= WIZARD::MOVEBOX_HEIGHT)
			if (IntersectRect(&temp, &_wizard->getMoveBox(), &roomCollisionBox))
			{
				if (_enemyManager->getCurrentRoom() != i + 1)
				{
					_wizard->endDash();

					CAM->setRoomSize(_roomList.rc[i]);
					_enemyManager->setCurrentRoom(i + 1);
				}
			}

			if (_roomList.rc[i].left > _wizard->getMoveBox().left)
				_wizard->setX(_roomList.rc[i].left + WIZARD::MOVEBOX_WIDTH / 2);

			else if (_roomList.rc[i].right < _wizard->getMoveBox().right)
				_wizard->setX(_roomList.rc[i].right - WIZARD::MOVEBOX_WIDTH / 2);


			if (_roomList.rc[i].top > _wizard->getMoveBox().top)
				_wizard->setY(_roomList.rc[i].top + WIZARD::MOVEBOX_HEIGHT / 2);

			else if (_roomList.rc[i].bottom < _wizard->getMoveBox().bottom)
				_wizard->setY(_roomList.rc[i].bottom - WIZARD::MOVEBOX_HEIGHT / 2);

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


	if (tiles[(int)(_wizard->getY() / TILESIZE) * TILEX + (int)(_wizard->getX() / TILESIZE)].objType == OBJECT_EXIT)
	{
		if (!_enemyManager->isEnemys())
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_wizard->endDash();
				SAVEDATA->setCurrentStage(SAVEDATA->getCurrentStage() + 1);
				SAVEDATA->setMapName("Stage/Stage" + to_string(SAVEDATA->getCurrentStage()) + ".map");
				SCENEMANAGER->loadScene("LoadingScene");
				RENDERMANAGER->clear();
				return;
			}

			IMAGEMANAGER->findImage("button_f")->render(UIMANAGER->getUIDC(),
				tiles[(int)(_wizard->getY() / TILESIZE) * TILEX + (int)(_wizard->getX() / TILESIZE)].rc.left + 22 - CAM->getX(),
				tiles[(int)(_wizard->getY() / TILESIZE) * TILEX + (int)(_wizard->getX() / TILESIZE)].rc.top - TILESIZE * 2 - CAM->getY());
		}
	}
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


	bool isSour = false;
	for (int i = 0; i < _enemyList.size(); ++i)
	{
		temp = NULL;
		switch (_enemyList[i].type)
		{
		case SHADOW:
			temp = new ShadowEnemy;
			isSour = false;
			break;
		case MAGE:
			temp = new Magician;
			isSour = false;
			break;
		case ROGUE:
			temp = new Rogue;
			isSour = false;
			break;
		case EARTH_BOSS:
			temp = new EarthBoss;
			isSour = true;
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
				_enemyManager->addEnemy(temp, j + 1, isSour);
				break;
			}
		}
		if(j == _roomList.rc.size())
			_enemyManager->addEnemy(temp, 0, isSour);
	}
}

