#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init(void)
{
	//타일맵 이미지 초기화
	//_sampleTileImg = IMAGEMANAGER->addFrameImage("sampletilemap", "Texture/Tile/Wizard_Of_Legend_tile_672x288_21x9.bmp", 672, 288, SAMPLETILEX, SAMPLETILEY);
	//_tileImg = IMAGEMANAGER->addFrameImage("tilemap", "Texture/Tile/Wizard_Of_Legend_tile_1344x576_21x9.bmp", 1344, 576, SAMPLETILEX, SAMPLETILEY);
	_sampleTileImg = IMAGEMANAGER->findImage("sampletilemap");
	_tileImg = IMAGEMANAGER->findImage("tilemap");
	_cardDeck = IMAGEMANAGER->findImage("card_deck");

	//맵툴셋팅
	this->maptoolSetup();
	_selectStage = 0;
	_currentStage = -1;

	//지형그리기 버튼으로 초기화
	_ctrlSelect = CTRL_TERRAINDRAW;

	//load();

	_clickPos = _mouseFromCard = { 0, 0 };
	_camPos = {TILESIZE * TILE_RENDER_RANGE_X/2, TILESIZE * TILE_RENDER_RANGE_Y / 2 };

	CAM->setMaxRange(TILESIZEX, TILESIZEY);
	CAM->setDrawRange(TILE_RENDER_RANGE_X * TILESIZE, TILE_RENDER_RANGE_Y * TILESIZE);
	CAM->setPosition(_camPos.x, _camPos.y);
	_rightBoard = {CAM->getDrawRange().x, 0, WINSIZEX, WINSIZEY };


	_currentSampleTile = 0;


	_cardPos = { _cardDeckRect.left, _cardDeckRect.bottom };
	_terrainCard.init(_cardPos.x, _cardPos.y);
	_objectCard.init(_cardPos.x, _cardPos.y);
	_enemyCard.init(_cardPos.x, _cardPos.y);

	_currentCard = &_terrainCard;
	_currentDrawNum = _currentCard->getDrawNum();

	memset(&_draggedInfo, 0, sizeof(DragInfo) * TILEX*TILEY);

	_isSelect = _checkActive = false;


	_totalMap = IMAGEMANAGER->findImage("tileMapImage");

	_drawMiniMap = false;
	_miniMapCamPos = { WINSIZEX / 2, WINSIZEY / 2 };


	brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	_moveCount = 0;

	_roomList.numOfRoom = 0;
	_roomList.rc.clear();

	SetTextAlign(getMemDC(), TA_LEFT); //텍스트 중앙정렬

	_enemyCount = 0;

	clearMapImg();
	return S_OK;
}

void maptoolScene::release(void)
{
	SelectObject(getMemDC(), oBrush);
	DeleteObject(brush);


	brush = CreateSolidBrush(RGB(255, 255, 255));
	oBrush = (HBRUSH)SelectObject(getMemDC(), brush);
}

void maptoolScene::update(void)
{

	_isDrag = false;

	if (_currentCard->isActive)
	{
		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_currentCard->changePage(-1);
			_currentCard->changeCard();
		}
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_currentCard->changePage(1);
			_currentCard->changeCard();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		switch (_ctrlSelect)
		{
		case CTRL_TERRAINDRAW:
			_isDrag = true;
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		if (_currentCard->isActive)
		{
			_mouseFromCard = { (int)(_ptMouse.x - _currentCard->x), (int)(_ptMouse.y - _currentCard->y) };
			_clickPos = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };
			switch (_ctrlSelect)
			{
			case CTRL_TERRAINDRAW:
				_isSelect = selectTerrain();
				break;
			case CTRL_OBJDRAW:
				_isSelect = selectObject();;
				break;
			case CTRL_ENEMYDRAW:
				_isSelect = selectEnemy();
				break;
			}
		}
		else if(PtInRect(&_cardDeckRect, _ptMouse))
		{
			_currentCard->isActive = true;
			_checkActive = true;
		}
		if (!_isSelect)
		{
			if (_currentCard->isActive && PtInRect(&_currentCard->rc, _ptMouse))
			{
				_currentCard->setIsDragged(true);
				if (_ctrlSelect == CTRL_ERASER)
					_ctrlSelect = _currentCard->cardType;
			}
			else
			{
				settingControl();
				if (_ctrlSelect == CTRL_ENEMYDRAW)
				{
					locateEnemy();
				}
			}
		}
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_currentCard->isActive)
		{
			if (_currentCard->getIsDragged())
			{
				moveCard();
			}
		}
		
		if(!_isSelect && !_currentCard->getIsDragged() && _ctrlSelect != CTRL_ENEMYDRAW)
			setMap();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_currentCard->getIsDragged() && !_checkActive)
		{
			if (PtInRect(&_cardDeckRect, _ptMouse))
			{
				_currentCard->isActive = false;
			}
		}

		if (_ctrlSelect ==CTRL_TERRAINDRAW && _isDrag)
		{
			for (int i = 0; i < TILEX * TILEY; ++i)
			{
				if (_draggedInfo[i].isDragged)
				{
					_tiles[i].terrainFrameX = _draggedInfo[i].tile.x;
					_tiles[i].terrainFrameY = _draggedInfo[i].tile.y;
					_tiles[i].terrain = getTerrainType(_draggedInfo[i].tile.x, _draggedInfo[i].tile.y);

					// miniMapRender
					//if (_tiles[i].terrain == TR_GROUND)
					//	_tileImg->frameRender(_miniMap->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 7, (_tiles[i].terrainFrameY) / _currentDrawNum * _currentDrawNum + 1);
					//else
					_tileImg->frameRender(_totalMap->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				}
			}
			memset(_draggedInfo, 0, sizeof(DragInfo) * TILEX * TILEY);
		}
		_currentCard->setIsDragged(false);
		_isSelect = _checkActive = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		switch (_ctrlSelect)
		{
		case CTRL_TERRAINDRAW:
			
			roomX = (_ptMouse.x + CAM->getX()) / TILESIZE;
			roomY = (_ptMouse.y + CAM->getY()) / TILESIZE;

			_room.left = _tiles[roomY * TILEX +roomX].rc.left;
			_room.top = _tiles[roomY * TILEX + roomX].rc.top;
			break;

		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		switch (_ctrlSelect)
		{
		case CTRL_OBJDRAW:
			setBlock();
			break;
		case CTRL_TERRAINDRAW:
			roomX = (_ptMouse.x + CAM->getX()) / TILESIZE;
			roomY = (_ptMouse.y + CAM->getY()) / TILESIZE;

			_room.right = _tiles[roomY * TILEX + roomX].rc.right;
			_room.bottom = _tiles[roomY * TILEX + roomX].rc.bottom;
			break;
		
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		createRoom();
		_room = { 0, 0, 0, 0 };
	}

	if (_currentCard->isActive)
	{
		_currentCard->x = _cardPos.x;
		_currentCard->y = _cardPos.y;
		_currentCard->update();
	}

	settingDrawTypeKey();

	cameraMove();
	if(!_drawMiniMap)
		CAM->videoShooting(_camPos.x, _camPos.y);
	else
		CAM->videoShooting(_miniMapCamPos.x, _miniMapCamPos.y);
}

void maptoolScene::render(void)
{
	//타일맵 이미지 렌더
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		_drawMiniMap = !_drawMiniMap;
		_angleWheel = 0;
	}
	if (_drawMiniMap)
	{
		_totalMap->stretchRender(getMemDC(), 100-CAM->getX() *  (0.5f + _angleWheel), 100 -CAM->getY() *  (0.5f + _angleWheel), 0.5f + _angleWheel);

		char str[100];

		sprintf_s(str, "%d %d", _miniMapCamPos.x, _miniMapCamPos.y);
		TextOut(getMemDC(), WINSIZEX - 100, 20, str, strlen(str));
		return;
	}


	
	_totalMap->render(getMemDC(), 0, 0, CAM->getSourX(), CAM->getSourY(), CAM->getCamWidth(), CAM->getCamHeight());

	//전체화면 왼쪽에 지형을 그린다

	renderTileRect();
	renderRoomRange();
	renderControl();

	_cardDeck->render(getMemDC(), _cardDeckRect.left, _cardDeckRect.top);
	if (_currentCard->isActive)
	{
		_currentCard->render();
	}
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[100];
		sprintf_s(str, "%d", _angleWheel);
		TextOut(getMemDC(), WINSIZEX - 100, 20, str, strlen(str));
	}
}

void maptoolScene::exit()
{
	SCENEMANAGER->loadScene("StartScene");
}

void maptoolScene::maptoolSetup(void)
{
	//렉트위치 초기화
	_rcSave   = RectMake(1200, 300, 100, 50);
	_rcLoad   = RectMake(1200, 380, 100, 50);
	_rcEraser = RectMake(1200, 460, 100, 50);

	_stageSelectImg[0] = IMAGEMANAGER->findImage("button_left");
	_stageSelectImg[1] = IMAGEMANAGER->findImage("button_right");
	_stageSelectRect[0] = RectMake(1175, 600, _stageSelectImg[0]->getWidth(), _stageSelectImg[0]->getHeight());
	_stageSelectRect[1] = RectMake(1320, 600, _stageSelectImg[0]->getWidth(), _stageSelectImg[0]->getHeight());


	_cardDeckRect = RectMake(1100 + 120, 50, _cardDeck->getWidth(), _cardDeck->getHeight());

	clearTiles();
}

bool maptoolScene::selectTerrain()
{
	POINT ptMouseSample = { _ptMouse.x - _currentCard->rc.left - 55, _ptMouse.y - 90 - _currentCard->rc.top + _terrainCard._sampleTiles[_currentSampleTile * _currentDrawNum * SAMPLETILEX].rc.top };
	//for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	for (int i = _currentCard->getCurrentPage() * _currentDrawNum * SAMPLETILEX; i < _currentCard->getCurrentPage() * _currentDrawNum * SAMPLETILEX + _currentDrawNum * SAMPLETILEX; i++)
	{
		if (PtInRect(&_terrainCard._sampleTiles[i].rc, ptMouseSample))
		{
			_currentTile.x = _terrainCard._sampleTiles[i].terrainFrameX;
			_currentTile.y = _terrainCard._sampleTiles[i].terrainFrameY;
			if (_currentTile.x == 1 && _currentTile.y == 1)
				cout << "test";
			return true;
		}
	}
	return false;
}

bool maptoolScene::selectObject()
{
	POINT ptMouseSample = { _ptMouse.x - _currentCard->rc.left - 55, _ptMouse.y - 90 - _currentCard->rc.top + _terrainCard._sampleTiles[_currentSampleTile * _currentDrawNum * SAMPLETILEX].rc.top };
	////for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	for (int i = _currentCard->getCurrentPage() * _currentDrawNum * 3; i < _currentCard->getCurrentPage() * _currentDrawNum * 3 + _currentDrawNum * 3 && i < SAMPLE_OBJECT_MAX; i++)
	{
		if (PtInRect(&_objectCard._sampleObject[i].rc, ptMouseSample))
		{
			_currentTile.x = i;
			//_currentTile.y = _terrainCard._sampleTiles[i].terrainFrameY;
			return true;
		}
	}

	return false;
}

bool maptoolScene::selectEnemy()
{
	POINT ptMouseSample = { _ptMouse.x - _currentCard->rc.left - 55, _ptMouse.y - 90 - _currentCard->rc.top + _terrainCard._sampleTiles[_currentSampleTile * _currentDrawNum * SAMPLETILEX].rc.top };
	////for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	for (int i = _currentCard->getCurrentPage() * _currentDrawNum * 3; i < _currentCard->getCurrentPage() * _currentDrawNum * 3 + _currentDrawNum * 3 && i <_enemyCard._sampleEnemy.size(); i++)
	{
		if (PtInRect(&_enemyCard._sampleEnemy[i].rc, ptMouseSample))
		{
			_currentTile.x = i;
			//_currentTile.y = _terrainCard._sampleTiles[i].terrainFrameY;
			return true;
		}
	}

	return false;
}

void maptoolScene::drawTile()
{
	int startX = CAM->getX() / TILESIZE, startY = CAM->getY() / TILESIZE;

	POINT ptMouseMap = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };

	for (int i = startY; i < startY + TILE_RENDER_RANGE_Y; i++)
	{
		for (int j = startX; j < startX + TILE_RENDER_RANGE_X; j++)
		{
			if (PtInRect(&_tiles[i*TILEX + j].rc, ptMouseMap))
			{
				//현재버튼이 지형이냐?
				if (_ctrlSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i*TILEX + j].terrainFrameX = _currentTile.x;
					_tiles[i*TILEX + j].terrainFrameY = _currentTile.y;
					_tiles[i*TILEX + j].terrain = getTerrainType(_currentTile.x, _currentTile.y);

					//miniMapRender
					//if (_tiles[i*TILEX + j].terrain == TR_GROUND)
					//	_tileImg->frameRender(_miniMap->getMemDC(), _tiles[i*TILEX + j].rc.left, _tiles[i*TILEX + j].rc.top, 7, (_tiles[i*TILEX + j].terrainFrameY) / _currentDrawNum * _currentDrawNum + 1);
					//else
					_tileImg->frameRender(_totalMap->getMemDC(), _tiles[i*TILEX + j].rc.left, _tiles[i*TILEX + j].rc.top, _tiles[i*TILEX + j].terrainFrameX, _tiles[i*TILEX + j].terrainFrameY);
				}
				//현재버튼이 오브젝트냐?
				else if (_ctrlSelect == CTRL_OBJDRAW)
				{
					if (_tiles[i*TILEX + j].terrain == TR_WALL && getObjectType(_currentTile.x) != OBJECT_DECO) continue;

					_tiles[i*TILEX + j].objIndex = _currentTile.x;
					_tiles[i*TILEX + j].objType = getObjectType(_currentTile.x);

					if (_objectCard.getFrameImageIndex() <= _currentTile.x)
					{
						_objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->frameRender(_totalMap->getMemDC(),
							_tiles[i*TILEX + j].rc.left,
							_tiles[i*TILEX + j].rc.bottom - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getFrameHeight(),
							0, 0);
					}
					else
					{
						if (getObjectType(_currentTile.x) == OBJECT_ENTRANCE || getObjectType(_currentTile.x) == OBJECT_EXIT || getObjectType(_currentTile.x) == OBJECT_DECO || getObjectType(_currentTile.x) == OBJECT_STORAGE)
						{
							_objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->render(_totalMap->getMemDC(),
								(_tiles[i*TILEX + j].rc.left + _tiles[i*TILEX + j].rc.right - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getWidth()) * 0.5f,
								(_tiles[i*TILEX + j].rc.top + _tiles[i*TILEX + j].rc.bottom - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getHeight()) * 0.5f);
						}
						else
						{
							_objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->render(_totalMap->getMemDC(),
								_tiles[i*TILEX + j].rc.left,
								_tiles[i*TILEX + j].rc.bottom - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getHeight());
						}
					}
				}
				//현재버튼이 지우개냐?
				else if (_ctrlSelect == CTRL_ERASER)
				{
					_tiles[i*TILEX + j].objIndex = 0;
					//_tiles[i*TILEX + j].objFrameY = 0;
					_tiles[i*TILEX + j].objType = OBJECT_NONE;

					if (_enemyList[i* TILEX + j].type != ENEMY_NONE)
					{
						_enemyList[i * TILEX + j].type = ENEMY_NONE;
						_enemyCount--;
					}

					//miniMapRender
					//if (_tiles[i*TILEX + j].terrain == TR_GROUND)
					//	_tileImg->frameRender(_miniMap->getMemDC(), _tiles[i*TILEX + j].rc.left, _tiles[i*TILEX + j].rc.top, 7, (_tiles[i*TILEX + j].terrainFrameY) / _currentDrawNum * _currentDrawNum + 1);
					//else
					_tileImg->frameRender(_totalMap->getMemDC(), _tiles[i*TILEX + j].rc.left, _tiles[i*TILEX + j].rc.top, _tiles[i*TILEX + j].terrainFrameX, _tiles[i*TILEX + j].terrainFrameY);
				}
				
				return;
			}
		}
	}
}

void maptoolScene::dragTile()
{
	POINT ptMouseMap = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };
	
	if (ptMouseMap.x < 0)
		ptMouseMap.x = 0;
	if (ptMouseMap.y < 0)
		ptMouseMap.y = 0;

	if (ptMouseMap.x >= TILESIZEX)
		ptMouseMap.x = TILESIZEX - 1;
	if (ptMouseMap.y >= TILESIZEY)
		ptMouseMap.y = TILESIZEY - 1;

	int left = _clickPos.x, top = _clickPos.y, right = ptMouseMap.x, bottom = ptMouseMap.y;
	int temp;
	if (left > right)
	{
		temp = left;
		left = right;
		right = temp;
	}
	if (top > bottom)
	{
		temp = top;
		top = bottom;
		bottom = temp;
	}

	RECT draggedRange = { left, top, right, bottom};
	left /= TILESIZE;
	right /= TILESIZE;
	bottom /= TILESIZE;
	top /= TILESIZE;

	enum DRAG_TYPe { EDGE, EDGE_UPDOWN, RANDOM , NONE};
	
	int type = NONE;

	bool isEdge = false, isEdgeUpDwon = false, isRnd = false;
	int rndStart = 0;
	if ((_currentTile.x == 1 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1) ||
		(_currentTile.x == 4 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1) ||
		(_currentTile.x == 7 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1))
	{
		type = EDGE;
	}
	else if ((_currentTile.x == 16 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1) ||
		(_currentTile.x == 19 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1))
	{
		type = RANDOM;
		rndStart = _currentCard->getCurrentPage() * _currentDrawNum;
	}
	else if ((_currentTile.x == 10 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1) ||
		(_currentTile.x == 13 && _currentTile.y == _currentCard->getCurrentPage() * _currentDrawNum + 1))
	{
		type = EDGE_UPDOWN;
	}

	memset(_draggedInfo, 0, sizeof(DragInfo) * TILEX * TILEY);
	//for (int i = 0; i < TILEX * TILEY; i++)
	
	RECT rcTemp;
	for (int i = top; i < bottom + 1; i++)
	{
		for (int j = left; j < right + 1; ++j)
		{
			if (IntersectRect(&rcTemp, &_tiles[i * TILEX + j].rc, &draggedRange))
			{
				_draggedInfo[i * TILEX + j].isDragged = true;

				/*_draggedInfo[i * TILEX + j].tile.x = _currentTile.x;
				_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;*/

				switch (type)
				{
				case RANDOM:
					{
						_draggedInfo[i * TILEX + j].tile.x = getFromIntTo(_currentTile.x - 1, _currentTile.x + 1);
						_draggedInfo[i * TILEX + j].tile.y = getFromIntTo(_currentTile.y - 1, _currentTile.y + 1);
					}
					break;
				case EDGE_UPDOWN:
					if (i == top)
					{
						_draggedInfo[i * TILEX + j].tile.x = getFromIntTo(_currentTile.x - 1, _currentTile.x + 1);
						_draggedInfo[i * TILEX + j].tile.y = _currentTile.y - 1;
					}
					else if (i == bottom)
					{
						_draggedInfo[i * TILEX + j].tile.x = getFromIntTo(_currentTile.x - 1, _currentTile.x + 1);
						_draggedInfo[i * TILEX + j].tile.y = _currentTile.y + 1;
					}
					else
					{
						_draggedInfo[i * TILEX + j].tile.x = getFromIntTo(_currentTile.x - 1, _currentTile.x + 1);
						_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;
					}
					break;
				case EDGE:
					{
						if (j == left)
						{
							_draggedInfo[i * TILEX + j].tile.x = _currentTile.x - 1;
							_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;
						}
						else if (j == right)
						{
							_draggedInfo[i * TILEX + j].tile.x = _currentTile.x + 1;
							_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;
						}
						else if (i == top)
						{
							_draggedInfo[i * TILEX + j].tile.x = _currentTile.x;
							_draggedInfo[i * TILEX + j].tile.y = _currentTile.y - 1;
						}
						else if (i == bottom)
						{
							_draggedInfo[i * TILEX + j].tile.x = _currentTile.x;
							_draggedInfo[i * TILEX + j].tile.y = _currentTile.y + 1;
						}
						else
						{
							_draggedInfo[i * TILEX + j].tile.x = _currentTile.x;
							_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;
						}
					}
					break;
				default:
					{
						_draggedInfo[i * TILEX + j].tile.x = _currentTile.x;
						_draggedInfo[i * TILEX + j].tile.y = _currentTile.y;
					}
					break;
				}
			}
		}
	}

	if (type == EDGE)
	{
		_draggedInfo[top * TILEX + left].tile.x = _currentTile.x - 1;
		_draggedInfo[top * TILEX + left].tile.y = _currentTile.y - 1;

		_draggedInfo[bottom * TILEX + left].tile.x = _currentTile.x - 1;
		_draggedInfo[bottom * TILEX + left].tile.y = _currentTile.y + 1;

		_draggedInfo[top * TILEX + right].tile.x = _currentTile.x + 1;
		_draggedInfo[top * TILEX + right].tile.y = _currentTile.y - 1;

		_draggedInfo[bottom * TILEX + right].tile.x = _currentTile.x + 1;
		_draggedInfo[bottom * TILEX + right].tile.y = _currentTile.y + 1;
	}
	
	
}


void maptoolScene::setMap(void)
{
	if (_isDrag && _ctrlSelect == CTRL_TERRAINDRAW)
		dragTile();
	else if(_ctrlSelect)
		drawTile();
}

void maptoolScene::createRoom()
{
	int t;
	if (_room.left > _room.right)
	{
		t = _room.left;
		_room.left = _room.right;
		_room.right = t;
	}
	if (_room.top > _room.bottom)
	{
		t = _room.top;
		_room.top = _room.bottom;
		_room.bottom = t;
	}


	RECT temp;
	int i;
	for (i = 0; i < _roomList.rc.size(); ++i)
	{
		if (IntersectRect(&temp, &_room, &_roomList.rc[i]))
		{
			if (_room.right - _room.left < TILESIZE * 5 || _room.bottom - _room.top < TILESIZE * 5)
			{
				_roomList.rc.erase(_roomList.rc.begin() + i);
				break;
			}
			else
			{
				_roomList.rc[i] = _room;
			}
			break;
		}
	}

	
	if (i == _roomList.rc.size() && 
		!(_room.right - _room.left < TILESIZE * 5 || _room.bottom - _room.top < TILESIZE * 5))
	{
		_roomList.rc.push_back(_room);
	}
}

void maptoolScene::renderRoomRange()
{
	pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	oPen = (HPEN)SelectObject(getMemDC(), pen);

	Rectangle(getMemDC(), _room, CAM->getX(), CAM->getY());
	for (int i = 0; i < _roomList.rc.size(); ++i)
	{
		Rectangle(getMemDC(), _roomList.rc[i], CAM->getX(), CAM->getY());
	}

	SelectObject(getMemDC(), oPen);
	DeleteObject(pen);

	brush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	oBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oPen = (HPEN)SelectObject(getMemDC(), pen);

	Rectangle(getMemDC(), _rightBoard);

	SelectObject(getMemDC(), oBrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oPen);
	DeleteObject(pen);
}

void maptoolScene::locateEnemy()
{
	if (_ctrlSelect != CTRL_ENEMYDRAW) return;

	int startX = CAM->getX() / TILESIZE, startY = CAM->getY() / TILESIZE;

	POINT ptMouseMap = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };

	for (int i = startY; i < startY + TILE_RENDER_RANGE_Y; i++)
	{
		for (int j = startX; j < startX + TILE_RENDER_RANGE_X; j++)
		{
			if (PtInRect(&_tiles[i*TILEX + j].rc, ptMouseMap))
			{
				if (_enemyList[i * TILEX + j].type != ENEMY_NONE) return;

				_enemyCount++;

				POINT pos = { (_tiles[i*TILEX + j].rc.left + _tiles[i*TILEX + j].rc.right) * 0.5f,
					(_tiles[i*TILEX + j].rc.bottom + _tiles[i*TILEX + j].rc.top) * 0.5f };

				_enemyList[i * TILEX + j] = { _currentTile.x, pos };

				_enemyCard._sampleEnemy[_currentTile.x].img->frameRender(_totalMap->getMemDC(),
					pos.x - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameWidth() / 2,
					//_tiles[i*TILEX + j].rc.bottom - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameHeight(),
					pos.y + ENEMY::MOVEBOX_HEIGHT / 2 - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameHeight(),
					0, 0);

				return;
			}
		}
	}
}

void maptoolScene::setBlock()
{
	int startX = CAM->getX() / TILESIZE, startY = CAM->getY() / TILESIZE;

	POINT ptMouseMap = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };

	for (int i = startY; i < startY + TILE_RENDER_RANGE_Y; i++)
	{
		for (int j = startX; j < startX + TILE_RENDER_RANGE_X; j++)
		{
			if (PtInRect(&_tiles[i*TILEX + j].rc, ptMouseMap))
			{
				if (_tiles[i*TILEX + j].objType == OBJECT_NONE)
				{
					_tiles[i*TILEX + j].objType = OBJECT_BLOCK1;
				}
			}
		}
	}
}

void maptoolScene::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(("Stage/stage" + to_string(_selectStage) + ".map").c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	/*for (int i = 0; i < 200; ++i)
	{
		for (int j = 0; j < 200; ++j)
		{
			WriteFile(file, &_tiles[i * TILEX + j], sizeof(tagTile), &write, NULL);
		}
	}*/
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);


	_roomList.numOfRoom = _roomList.rc.size();

	WriteFile(file, &_roomList.numOfRoom, sizeof(int), &write, NULL);

	RECT temp;
	for (int i = 0; i < _roomList.rc.size(); ++i)
	{
		temp = _roomList.rc[i];
		WriteFile(file, &temp, sizeof(temp), &write, NULL);
	}


	WriteFile(file, &_enemyCount, sizeof(int), &write, NULL);
	for (int i = 0; i < TILEY * TILEX; i++)
	{
		if (_enemyList[i].type == ENEMY_NONE) continue;
			WriteFile(file, &_enemyList[i], sizeof(_enemyList[i]), &write, NULL);
	}
	

	CloseHandle(file);
}

void maptoolScene::load()
{
	HANDLE file;
	DWORD read;

	clearMapImg();
	memset(_tiles, 0, sizeof(tagTile) * TILEX * TILEY);
	clearTiles();
	_camPos = { TILESIZE * TILE_RENDER_RANGE_X / 2, TILESIZE * TILE_RENDER_RANGE_Y / 2 };
	_roomList.rc.clear();
	_enemyCount = 0;

	file = CreateFile(( "Stage/stage" + to_string(_selectStage) + ".map").c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE )//&& GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		return;
	}

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	RECT temp;
	_roomList.rc.clear();

	ReadFile(file, &_roomList.numOfRoom, sizeof(int), &read, NULL);
	for (int i = 0; i < _roomList.numOfRoom; ++i)
	{
		ReadFile(file, &temp, sizeof(temp), &read, NULL);
		_roomList.rc.push_back(temp);
	}



	ReadFile(file, &_enemyCount, sizeof(int), &read, NULL);

	EnemyInfo temp1;
	for (int i = 0; i < _enemyCount; ++i)
	{
		ReadFile(file, &temp1, sizeof(temp1), &read, NULL);

		_enemyList[temp1.pos.y/TILESIZE * TILEX + temp1.pos.x / TILESIZE] = temp1;
	}



	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tileImg->frameRender(_totalMap->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (!(_tiles[i].objType == OBJECT_NONE || _tiles[i].objType == OBJECT_BLOCK1))
		{
			if (_tiles[i].objType == OBJECT_TRAP)
			{
				if (_tiles[i].objIndex == AWL_TRAP)
				{
					_objectCard._sampleObject[_tiles[i].objIndex].objImg->frameRender(_totalMap->getMemDC(),
						_tiles[i].rc.left,
						_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight(),
						0, 0);
				}
				else if (_tiles[i].objIndex == BOMB_TRAP)
				{
					_objectCard._sampleObject[_tiles[i].objIndex].objImg->render(_totalMap->getMemDC(),
						_tiles[i].rc.left,
						_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight());
				}
			}
			else
			{
				if (_tiles[i].objType == OBJECT_ENTRANCE || _tiles[i].objType == OBJECT_EXIT || _tiles[i].objType == OBJECT_DECO || _tiles[i].objType == OBJECT_STORAGE)
				{
					_objectCard._sampleObject[_tiles[i].objIndex].objImg->render(_totalMap->getMemDC(),
						(_tiles[i].rc.right + _tiles[i].rc.left - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getWidth())*0.5f,
						(_tiles[i].rc.bottom + _tiles[i].rc.top - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight())*0.5f);
				}
				else
				{
					_objectCard._sampleObject[_tiles[i].objIndex].objImg->render(_totalMap->getMemDC(),
						_tiles[i].rc.left,
						_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight());
				}
			}
		}
		if (_enemyList[i].type != ENEMY_NONE)
		{
			cout <<_enemyList[i].type;
			_enemyCard._sampleEnemy[_enemyList[i].type].img->frameRender(_totalMap->getMemDC(), 
				_enemyList[i].pos.x - _enemyCard._sampleEnemy[_enemyList[i].type].img->getFrameWidth()/2,
				_enemyList[i].pos.y + ENEMY::MOVEBOX_HEIGHT / 2 - _enemyCard._sampleEnemy[_enemyList[i].type].img->getFrameHeight(),
				0, 0);
		}
	}


}

void maptoolScene::clearMapImg()
{
	brush = CreateSolidBrush(RGB(0, 0, 0));
	oBrush = (HBRUSH)SelectObject(_totalMap->getMemDC(), brush);
	
	Rectangle(_totalMap->getMemDC(), RectMake(0, 0, TILESIZEX, TILESIZEY));
	
	SelectObject(_totalMap->getMemDC(), oBrush);
	DeleteObject(brush);

}

void maptoolScene::renderTileRect()
{

	int startX = CAM->getX() / TILESIZE, startY = CAM->getY() / TILESIZE;

	pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oPen = (HPEN)SelectObject(getMemDC(), pen);
	POINT ptMouseCam = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };
	int selectIdx = -1;
	for (int i = startY; i < startY + TILE_RENDER_RANGE_Y; i++)
	{
		for (int j = startX; j < startX + TILE_RENDER_RANGE_X; j++)
		{
			if (_tiles[i * TILEX + j].terrain == TR_NONE || _tiles[i * TILEX + j].objType == OBJECT_BLOCK1)
				Rectangle(getMemDC(), _tiles[i*TILEX + j].rc, CAM->getX(), CAM->getY());

			//else
			//	IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i*TILEX + j].rc.left - CAM->getX(), _tiles[i*TILEX + j].rc.top - CAM->getY(), _tiles[i*TILEX + j].terrainFrameX, _tiles[i*TILEX + j].terrainFrameY);

			if (_isDrag && _draggedInfo[i*TILEX + j].isDragged)
			{
				IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i*TILEX + j].rc.left - CAM->getX(), _tiles[i*TILEX + j].rc.top - CAM->getY(), _draggedInfo[i*TILEX + j].tile.x, _draggedInfo[i*TILEX + j].tile.y);
			}

			if (PtInRect(&_tiles[i*TILEX + j].rc, ptMouseCam))
				selectIdx = i * TILEX + j;

			if (KEYMANAGER->isToggleKey('9'))
			{
				char str[20];
				//sprintf_s(str, "%3d  %3d", j, i);
				sprintf_s(str, "%3d", _tiles[i * TILEX + j].terrain);
				TextOut(getMemDC(), _tiles[i * TILEX + j].rc.left - CAM->getX(), _tiles[i * TILEX + j].rc.top + 10 - CAM->getY(), str, strlen(str));
			}
		}
	}
	SelectObject(getMemDC(), oPen);
	DeleteObject(pen);

	if (selectIdx != -1)
	{
		HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), pen);

		Rectangle(getMemDC(), _tiles[selectIdx].rc, CAM->getX(), CAM->getY());

		SelectObject(getMemDC(), oPen);
		DeleteObject(pen);

		if (_ctrlSelect == CTRL_OBJDRAW)
		{
			if (_objectCard.getFrameImageIndex() <= _currentTile.x)
			{
				_objectCard._sampleObject[_currentTile.x].objImg->frameRender(getMemDC(),
					//_tiles[selectIdx].rc.left + _objectCard._sampleObject[_currentTile.x].objImg->getWidth()/2 - CAM->getX(),
					_tiles[selectIdx].rc.left - CAM->getX(),
					_tiles[selectIdx].rc.bottom - _objectCard._sampleObject[_currentTile.x].objImg->getFrameHeight() - CAM->getY(),
					0, 0);
			}
			else
			{
				if (getObjectType(_currentTile.x) == OBJECT_ENTRANCE || getObjectType(_currentTile.x) == OBJECT_EXIT || getObjectType(_currentTile.x) == OBJECT_DECO || getObjectType(_currentTile.x) == OBJECT_STORAGE)
				{
					_objectCard._sampleObject[_currentTile.x].objImg->render(getMemDC(),
						//_tiles[selectIdx].rc.left + _objectCard._sampleObject[_currentTile.x].objImg->getWidth()/2 - CAM->getX(),
						(_tiles[selectIdx].rc.right + _tiles[selectIdx].rc.left - _objectCard._sampleObject[_currentTile.x].objImg->getWidth())*0.5f - CAM->getX(),
						(_tiles[selectIdx].rc.bottom + _tiles[selectIdx].rc.top - _objectCard._sampleObject[_currentTile.x].objImg->getHeight())*0.5f - CAM->getY());
				}
				else
				{
					_objectCard._sampleObject[_currentTile.x].objImg->render(getMemDC(),
						//_tiles[selectIdx].rc.left + _objectCard._sampleObject[_currentTile.x].objImg->getWidth()/2 - CAM->getX(),
						_tiles[selectIdx].rc.left - CAM->getX(),
						_tiles[selectIdx].rc.bottom - _objectCard._sampleObject[_currentTile.x].objImg->getHeight() - CAM->getY());
				}
			}
		}
		else if (_ctrlSelect == CTRL_ENEMYDRAW)
		{
			_enemyCard._sampleEnemy[_currentTile.x].img->frameRender(getMemDC(),
				(_tiles[selectIdx].rc.left + _tiles[selectIdx].rc.right - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameWidth()) * 0.5f - CAM->getX(),
				//_tiles[selectIdx].rc.bottom - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameHeight(),
				(_tiles[selectIdx].rc.bottom + _tiles[selectIdx].rc.top) *0.5f + ENEMY::MOVEBOX_HEIGHT / 2 - _enemyCard._sampleEnemy[_currentTile.x].img->getFrameHeight() - CAM->getY(),
				0, 0);
		}
	}


	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//게임타일 렉트 렌더
		for (int i = startY; i < startY + TILE_RENDER_RANGE_Y; i++)
		{
			for (int j = startX; j < startX + TILE_RENDER_RANGE_X; j++)
			{
				Rectangle(getMemDC(), _tiles[i*TILEX + j].rc, CAM->getX(), CAM->getY());
			}
		}
	}
}

void maptoolScene::renderControl()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN oPen = (HPEN)SelectObject(getMemDC(), pen);
	//버튼렉트 렌더
	
	if (PtInRect(&_rcSave, _ptMouse))
		Rectangle(getMemDC(), _rcSave);

	if (PtInRect(&_rcLoad, _ptMouse))
		Rectangle(getMemDC(), _rcLoad);

	if (PtInRect(&_rcEraser, _ptMouse))
		Rectangle(getMemDC(), _rcEraser);

	if (PtInRect(&_stageSelectRect[0], _ptMouse))
		Rectangle(getMemDC(), _stageSelectRect[0]);

	if (PtInRect(&_stageSelectRect[1], _ptMouse))
		Rectangle(getMemDC(), _stageSelectRect[1]);

	SelectObject(getMemDC(), oPen);
	DeleteObject(pen);
	
	
	_stageSelectImg[0]->render(getMemDC(), _stageSelectRect[0].left, _stageSelectRect[0].top);

	char str[30];

	if (_currentStage != -1)
	{
		sprintf_s(str, "stage%s.map", to_string(_currentStage).c_str());
		TextOut(getMemDC(), _stageSelectRect[0].right + 10, _stageSelectRect[0].top - 25, str, strlen(str));
	}

	sprintf_s(str, "stage%s.map", to_string(_selectStage).c_str());
	TextOut(getMemDC(), _stageSelectRect[0].right + 10, _stageSelectRect[0].top + 10, str, strlen(str));

	_stageSelectImg[1]->render(getMemDC(), _stageSelectRect[1].left, _stageSelectRect[1].top);


	//버튼렉트 글씨
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOut(getMemDC(), _rcSave.left + 30, _rcSave.top + 20, "SAVE", strlen("SAVE"));
	TextOut(getMemDC(), _rcLoad.left + 30, _rcLoad.top + 20, "LOAD", strlen("LOAD"));
	TextOut(getMemDC(), _rcEraser.left + 30, _rcEraser.top + 20, "ERASER", strlen("ERASER"));

}


TERRAIN maptoolScene::getTerrainType(int frameX, int frameY)
{
	if ((frameX <= 5) ||
		(frameX >= 9 && frameX <= 11))
	{
		return TR_WALL;
	}

	if ((frameX >= 6 && frameX <= 8) ||
		(frameX >= 15 && frameX <= 17))
	{
		return TR_GROUND;
	}
	
	if ((frameX >= 12 && frameX <= 14) ||
		(frameX >= 18 && frameX <= 20))
	{
		return TR_CLIFF;
	}

	return TR_NONE;
}



void maptoolScene::clearTiles()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_tiles[i * TILEX + j].terrainFrameX = 1;
			_tiles[i * TILEX + j].terrainFrameY = 1;
			_tiles[i * TILEX + j].objIndex = 0;
			_tiles[i * TILEX + j].terrain = TR_NONE;
			_tiles[i * TILEX + j].objType = OBJECT_NONE;
			_tiles[i * TILEX + j].obj = NULL;

			_enemyList[i * TILEX + j].type = ENEMY_NONE;
		}
	}
}

void maptoolScene::moveCard()
{
	_cardPos.x = _ptMouse.x - _mouseFromCard.x;
	_cardPos.y = _ptMouse.y - _mouseFromCard.y;

	if (_cardPos.x < 0)
		_cardPos.x = 0;
	else if (_cardPos.x > WINSIZEX)
		_cardPos.x = WINSIZEX;
	if (_cardPos.y < 0)
		_cardPos.y = 0;
	else if (_cardPos.y > WINSIZEY)
		_cardPos.y = WINSIZEY;
}

void maptoolScene::cameraMove()
{
	_moveCount = (_moveCount + 1) % 2;
	if (_moveCount != 0) return;

	int speed = TILESIZE;

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_drawMiniMap)
		{
			//if (_miniMapCamPos.x > WINSIZEX/2)
				_miniMapCamPos.x -= speed;
		}
		else
		{
			if (_camPos.x >= CAM->getCamWidth() / 2 + TILESIZE)
				_camPos.x -= TILESIZE;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_drawMiniMap)
		{
			//if (_miniMapCamPos.x < TILESIZE * TILEX * (0.5f + _angleWheel))
				_miniMapCamPos.x += speed;
		}
		else
		{
			if (_camPos.x <= TILESIZEX - CAM->getCamWidth() / 2)
				_camPos.x += TILESIZE;
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_drawMiniMap)
		{
			//if (_miniMapCamPos.y > WINSIZEY / 2)
				_miniMapCamPos.y -= speed;
		}
		else
		{
			if (_camPos.y >= CAM->getCamHeight() / 2 + TILESIZE)
				_camPos.y -= TILESIZE;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_drawMiniMap)
		{
			//if (_miniMapCamPos.y < TILESIZE * TILEY * (0.5f + _angleWheel))
				_miniMapCamPos.y += speed;
		}
		else
		{
			if (_camPos.y <= TILESIZEY - CAM->getCamHeight() / 2)
				_camPos.y += TILESIZE;
		}
	}

	if (_isDrag)
	{
		if (_ptMouse.x < TILESIZE)
		{
			if (_camPos.x > CAM->getCamWidth() / 2 + TILESIZE)
				_camPos.x -= TILESIZE;
		}
		else if (_ptMouse.x > (TILE_RENDER_RANGE_X - 1)*TILESIZE)
		{
			if (_camPos.x < TILESIZEX - CAM->getCamWidth() / 2)
				_camPos.x += TILESIZE;
		}
		if (_ptMouse.y < TILESIZE)
		{
			if (_camPos.y > CAM->getCamHeight() / 2 + TILESIZE)
				_camPos.y -= TILESIZE;
		}
		else if (_ptMouse.y >(TILE_RENDER_RANGE_Y - 1)*TILESIZE)
		{
			if (_camPos.y < TILESIZEY - CAM->getCamHeight() / 2)
				_camPos.y += TILESIZE;
		}
	}
}
void maptoolScene::settingControl()
{
	{
		if (PtInRect(&_rcSave, _ptMouse))
		{
			//_ctrlSelect = CTRL_SAVE;
			this->save();
		}
		if (PtInRect(&_rcLoad, _ptMouse))
		{
			//_ctrlSelect = CTRL_LOAD;
			this->load();
			_currentStage = _selectStage;
		}
		if (PtInRect(&_rcEraser, _ptMouse))
		{
			_ctrlSelect = CTRL_ERASER;
		}

		if (PtInRect(&_stageSelectRect[0], _ptMouse))
		{
			if (_selectStage > 0)
			{
				--_selectStage;
			}
		}
		if (PtInRect(&_stageSelectRect[1], _ptMouse))
		{
			++_selectStage;
		}

	}
}

void maptoolScene::settingDrawTypeKey()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_ctrlSelect = CTRL_TERRAINDRAW;
		_cardPos = { _cardDeckRect.left, _cardDeckRect.bottom };
		_currentCard->x = _cardPos.x;
		_currentCard->y = _cardPos.y;
		_currentCard->isActive = false;

		_currentCard = &_terrainCard;
		_currentCard->changeCard();
		_currentDrawNum = _currentCard->getDrawNum();
		_currentCard->isActive = true;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_ctrlSelect = CTRL_OBJDRAW;
		_cardPos = { _cardDeckRect.left, _cardDeckRect.bottom };
		_currentCard->x = _cardPos.x;
		_currentCard->y = _cardPos.y;
		_currentCard->isActive = false;

		_currentCard = &_objectCard;
		_currentCard->changeCard();
		_currentDrawNum = _currentCard->getDrawNum();
		_currentTile.x = 10;
		_currentCard->isActive = true;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_ctrlSelect = CTRL_ENEMYDRAW;
		_cardPos = { _cardDeckRect.left, _cardDeckRect.bottom };
		_currentCard->x = _cardPos.x;
		_currentCard->y = _cardPos.y;
		_currentCard->isActive = false;

		_currentCard = &_enemyCard;
		_currentCard->changeCard();
		_currentDrawNum = _currentCard->getDrawNum();
		_currentTile.x = 0;
		_currentCard->isActive = true;
	}
}



OBJECT maptoolScene::getObjectType(int frameX, int frameY)
{
	//if (frameX == 0 && frameY == 0) return OBJECT_COIN;
	//if (frameX == 0 && frameY == 1) return OBJECT_ITEM;

	if (frameX >= SAMPLE_OBJECT_MAX || frameX < 0)
		return OBJECT_NONE;

	if (frameX >= 15 && frameX <= 22)
		return OBJECT_DECO;
	/*else if (frameX == 0)
		return OBJECT_WALL;
	else if (frameX >= 1 && frameX <=4)
		return OBJECT_WALL;*/
	else if ((frameX >= 5 && frameX <= 10) ||
		(frameX == 13))
		return OBJECT_BREAKABLE;
	else if (frameX == AWL_TRAP || frameX == 30)
		return OBJECT_TRAP;
	else if (frameX == 35)
		return OBJECT_EXIT;
	else if (frameX == 36)
		return OBJECT_ENTRANCE;
	else if (frameX == 37)
		return OBJECT_STORAGE;
	//else if()

	return OBJECT_WALL;
}

ENEMY_TYPE maptoolScene::getEnemyType(int frameX)
{
	if(frameX == 0)
		return SHADOW;

	return SHADOW;
}



