#include "stdafx.h"
#include "tileMap.h"
#include "AwlTrap.h"
#include "Bomb.h"
#include "Storage.h"

HRESULT tileMap::init(const char * fileName)
{
	_objectCard.init(0, 0);
	this->load(fileName);

	return S_OK;
}

HRESULT tileMap::init(void)
{
	//�� �ε�
	_objectCard.init(0, 0);
	this->load();

	return S_OK;
}

void tileMap::release(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj != NULL)
		{
			_tiles[i].obj->release();
			SAFE_DELETE(_tiles[i].obj);
		}
	}
}

void tileMap::update(void)
{
	int startX = CAM->getX(), startY = CAM->getY(),
		endX = CAM->getX() + WINSIZEX, endY = CAM->getY() + WINSIZEY;

	startX = startX / TILESIZE - 10;
	startY = startY / TILESIZE - 1;
	endX = endX / TILESIZE + 1;
	endY = endY / TILESIZE + 10;;


	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX > TILESIZEX) endX = TILESIZEX - 1;
	if (endY > TILESIZEY) endY = TILESIZEY - 1;

	// ������Ʈ�� ��� z���� ������ ���� ����� ���� �� ��Ʈ�ʿ� ������ ���� �ʰ� �ǽð����� ����.

	for (int i = startY; i < endY; i++)
	{
		for (int j = startX; j < endX; ++j)
		{
			//if (_tiles[i * TILEX + j].objType == OBJECT_NONE || _tiles[i * TILEX + j].objType == OBJECT_BLOCK1) continue;
			//_objectCard._sampleObject[_tiles[i*TILEX +j].objIndex].objImg->render(getMemDC(), _tiles[i * TILEX + j].rc.left - CAM->getX(), _tiles[i * TILEX + j].rc.bottom - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getHeight() - CAM->getY());

			if (_tiles[i * TILEX + j].obj == NULL || _tiles[i * TILEX + j].objType == OBJECT_NONE)
				continue;
			_tiles[i*TILEX + j].obj->update();
			RENDERMANAGER->addRender(_tiles[i*TILEX + j].rc.bottom, _tiles[i*TILEX + j].obj);
		}
	}
}

void tileMap::render(void)
{
	////��üȭ�� ������ �׸���
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//}
	////��üȭ�� ������Ʈ�� �׸���
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].objType == OBJECT_NONE) continue;
	//	IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objIndex, _tiles[i].objFrameY);
	//}
}

bool tileMap::prepareLoading(const char* fileName)
{
	release();
	_storageIndex = -1;
	SAVEDATA->setStartPos(-1, -1);
	SAVEDATA->setEndPos(-1, -1);

	_objectCard.init(0, 0);

	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	RECT temp;
	_roomList.rc.clear();

	ReadFile(file, &_roomList.numOfRoom, sizeof(int), &read, NULL);
	for (int i = 0; i < _roomList.numOfRoom; ++i)
	{
		ReadFile(file, &temp, sizeof(temp), &read, NULL);
		_roomList.rc.push_back(temp);
	}


	int numOfEnemy;
	_enemyList.clear();

	ReadFile(file, &numOfEnemy, sizeof(int), &read, NULL);

	EnemyInfo temp1;
	for (int i = 0; i < numOfEnemy; ++i)
	{
		ReadFile(file, &temp1, sizeof(temp1), &read, NULL);

		_enemyList.push_back(temp1);
	}


	CloseHandle(file);

	memset(_attribute, 0, sizeof(DWORD)* TILEX * TILEY);

	_loadingIndex = 0;


	Image* _miniMap = IMAGEMANAGER->findImage("miniMapImage");

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oBrush = (HBRUSH)SelectObject(_miniMap->getMemDC(), brush);

	Rectangle(_miniMap->getMemDC(), RectMake(0, 0, _miniMap->getWidth(), _miniMap->getHeight()));



	Image * tileGameMap = IMAGEMANAGER->findImage("tileMapImage");

	Rectangle(tileGameMap->getMemDC(), RectMake(0, 0, tileGameMap->getWidth(), tileGameMap->getHeight()));

	SelectObject(tileGameMap->getMemDC(), oBrush);
	DeleteObject(brush);


	return false;
}

bool tileMap::loadingDone()
{
	Image* _miniMap = IMAGEMANAGER->findImage("miniMapImage");
	if (_loadingIndex >= TILEX * TILEY)
		return true;

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oBrush = (HBRUSH)SelectObject(_miniMap->getMemDC(), brush);
	
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN oPen = (HPEN)SelectObject(_miniMap->getMemDC(), pen);

	//�� �Ӽ� ����
	Image * tileMap = IMAGEMANAGER->findImage("tilemap");
	Image * pixelTile = IMAGEMANAGER->findImage("pixel_tile");
	Image * tileGameMap = IMAGEMANAGER->findImage("tileMapImage");
	Image * tileGamePixel = IMAGEMANAGER->findImage("tileMapPixel");

	for(int j = 0 ; _loadingIndex < TILEX * TILEY && j< 200;++j, _loadingIndex++)
	{
		if (_tiles[_loadingIndex].terrain == TR_GROUND)
		{

			//Rectangle(_miniMap->getMemDC(),
			//	RectMake(_tiles[_loadingIndex].rc.left / 16, _tiles[_loadingIndex].rc.top / 16, TILESIZE / 16, TILESIZE / 16));
			Rectangle(_miniMap->getMemDC(),
				RectMake(_tiles[_loadingIndex].rc.left / MINIMAP_RATE, _tiles[_loadingIndex].rc.top / MINIMAP_RATE, TILESIZE / MINIMAP_RATE, TILESIZE / MINIMAP_RATE));

		}
		else if (_tiles[_loadingIndex].terrain == TR_CLIFF)
		{

			brush = CreateSolidBrush(RGB(40, 40, 40));
			oBrush = (HBRUSH)SelectObject(_miniMap->getMemDC(), brush);
			pen = CreatePen(PS_SOLID, 1, RGB(40, 40, 40));
			oPen = (HPEN)SelectObject(_miniMap->getMemDC(), pen);

			Rectangle(_miniMap->getMemDC(),
				RectMake(_tiles[_loadingIndex].rc.left / MINIMAP_RATE, _tiles[_loadingIndex].rc.top / MINIMAP_RATE, TILESIZE / MINIMAP_RATE, TILESIZE / MINIMAP_RATE));

			SelectObject(_miniMap->getMemDC(), oPen);
			DeleteObject(pen);
			SelectObject(_miniMap->getMemDC(), oBrush);
			DeleteObject(brush);
		}

		if (_tiles[_loadingIndex].terrain == TR_WALL ||
			_tiles[_loadingIndex].terrain == TR_CLIFF)
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;

		pixelTile->frameRender(tileGamePixel->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, _tiles[_loadingIndex].terrainFrameX, _tiles[_loadingIndex].terrainFrameY);


		if (_tiles[_loadingIndex].objType == OBJECT_NONE || _tiles[_loadingIndex].objType == OBJECT_BLOCK1)
			_tiles[_loadingIndex].obj = NULL;

		if (_tiles[_loadingIndex].objType == OBJECT_WALL ||
			_tiles[_loadingIndex].objType == OBJECT_BLOCK1 ||
			_tiles[_loadingIndex].objType == OBJECT_STORAGE)
		{
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;
			pixelTile->frameRender(tileGamePixel->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, 0, 0);
		}
		if (_tiles[_loadingIndex].objType == OBJECT_BREAKABLE || _tiles[_loadingIndex].objType == OBJECT_TRAP)
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;


		tileMap->frameRender(tileGameMap->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, _tiles[_loadingIndex].terrainFrameX, _tiles[_loadingIndex].terrainFrameY);

		/*if (_tiles[i].objType == OBJECT_BLOCK1) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCK3) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCKS) _attribute[i] |= ATTR_UNMOVAL;*/


		if (!(_tiles[_loadingIndex].objType == OBJECT_NONE || _tiles[_loadingIndex].objType == OBJECT_BLOCK1))
		{

			if (_tiles[_loadingIndex].objType == OBJECT_TRAP)
			{
				if (_tiles[_loadingIndex].objIndex == AWL_TRAP)
				{
					_tiles[_loadingIndex].obj = new AwlTrap(_objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg,
						{ _tiles[_loadingIndex].rc.left,
						_tiles[_loadingIndex].rc.bottom - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getHeight() });
				}
				else if (_tiles[_loadingIndex].objIndex == BOMB_TRAP)
				{
					_tiles[_loadingIndex].obj = new Bomb(_objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg,
						{ _tiles[_loadingIndex].rc.left,
						_tiles[_loadingIndex].rc.bottom - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getHeight() });
				}

			}

			else if (_tiles[_loadingIndex].objType == OBJECT_STORAGE)
			{
				_storageIndex = _loadingIndex;

				pixelTile->frameRender(tileGamePixel->getMemDC(), _tiles[_loadingIndex + 1].rc.left, _tiles[_loadingIndex + 1].rc.top, 0, 0);
				pixelTile->frameRender(tileGamePixel->getMemDC(), _tiles[_loadingIndex + 1 + TILEX].rc.left, _tiles[_loadingIndex + 1 + TILEX].rc.top, 0, 0);
				pixelTile->frameRender(tileGamePixel->getMemDC(), _tiles[_loadingIndex - TILEX].rc.left, _tiles[_loadingIndex - TILEX].rc.top, 0, 0);
			}

			else if (_tiles[_loadingIndex].objType == OBJECT_ENTRANCE || _tiles[_loadingIndex].objType == OBJECT_EXIT || _tiles[_loadingIndex].objType == OBJECT_DECO)
			{
				_objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->render(tileGameMap->getMemDC(),
					(_tiles[_loadingIndex].rc.right + _tiles[_loadingIndex].rc.left - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getWidth()) * 0.5f,
					(_tiles[_loadingIndex].rc.bottom + _tiles[_loadingIndex].rc.top - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getHeight()) * 0.5f);

				_tiles[_loadingIndex].obj = NULL;

				if (_tiles[_loadingIndex].objType == OBJECT_ENTRANCE)
				{
					SAVEDATA->setStartPos(
							(_tiles[_loadingIndex].rc.right + _tiles[_loadingIndex].rc.left) * 0.5f,
							(_tiles[_loadingIndex].rc.bottom + _tiles[_loadingIndex].rc.top) * 0.5f
					);
				}
				else if (_tiles[_loadingIndex].objType == OBJECT_EXIT)
				{
					SAVEDATA->setEndPos(
						(_tiles[_loadingIndex].rc.right + _tiles[_loadingIndex].rc.left) * 0.5f,
						(_tiles[_loadingIndex].rc.bottom + _tiles[_loadingIndex].rc.top) * 0.5f
					);
				}
			}
			else
			{
				_tiles[_loadingIndex].obj = new Stuff(_objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg,
					{ _tiles[_loadingIndex].rc.left,
					_tiles[_loadingIndex].rc.bottom - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getHeight() });
			}
		}
	}

	if (_loadingIndex >= TILEX * TILEY)
	{
		if(SAVEDATA->getStartPos().x != -1)
			_objectCard._sampleObject[36].objImg->render(tileGameMap->getMemDC(),
				SAVEDATA->getStartPos().x - (_objectCard._sampleObject[36].objImg->getWidth()) * 0.5f,
				SAVEDATA->getStartPos().y - (_objectCard._sampleObject[36].objImg->getHeight()) * 0.5f);
		if (SAVEDATA->getEndPos().x != -1)
			_objectCard._sampleObject[35].objImg->render(tileGameMap->getMemDC(),
				SAVEDATA->getEndPos().x - (_objectCard._sampleObject[36].objImg->getWidth()) * 0.5f,
				SAVEDATA->getEndPos().y - (_objectCard._sampleObject[36].objImg->getHeight()) * 0.5f);

		if(_storageIndex != -1)
			IMAGEMANAGER->findImage("â��")->render(tileGameMap->getMemDC(),
				_tiles[_storageIndex].rc.left,
				_tiles[_storageIndex].rc.bottom - IMAGEMANAGER->findImage("â��")->getHeight());
	}

	SelectObject(_miniMap->getMemDC(), oPen);
	DeleteObject(pen);
	SelectObject(_miniMap->getMemDC(), oBrush);
	DeleteObject(brush);

	return false;
}

bool tileMap::endLoading()
{
	CloseHandle(file);

	return false;
}

void tileMap::load(const char * fileName)
{
	HANDLE file;
	DWORD read;

	//file = CreateFile("tiles.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL, NULL);
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);



	RECT temp;
	_roomList.rc.clear();

	ReadFile(file, &_roomList.numOfRoom, sizeof(int), &read, NULL);
	for (int i = 0; i < _roomList.numOfRoom; ++i)
	{
		ReadFile(file, &temp, sizeof(temp), &read, NULL);
		_roomList.rc.push_back(temp);
	}


	int numOfEnemy;
	_enemyList.clear();

	ReadFile(file, &numOfEnemy, sizeof(int), &read, NULL);

	EnemyInfo temp1;
	for (int i = 0; i < numOfEnemy; ++i)
	{
		ReadFile(file, &temp1, sizeof(temp1), &read, NULL);

		_enemyList.push_back(temp1);
	}


	CloseHandle(file);

	//�� �Ӽ� ����
	memset(_attribute, 0, sizeof(DWORD)* TILEX * TILEY); 
	Image * tileMap = IMAGEMANAGER->findImage("tilemap");
	Image * pixelTile = IMAGEMANAGER->findImage("pixel_tile");
	Image * tankGameMap = IMAGEMANAGER->findImage("tileMapImage");
	Image * tankGamePixel = IMAGEMANAGER->findImage("tileMapPixel");
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		

		pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		

		if (_tiles[i].objType == OBJECT_WALL ||
			_tiles[i].objType == OBJECT_BLOCK1 || 
			_tiles[i].objType == OBJECT_STORAGE)
		{
			_attribute[i] |= ATTR_UNMOVAL;
			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 0, 0);
		}

		if(_tiles[i].objType == OBJECT_BREAKABLE ||
			_tiles[i].objType == OBJECT_TRAP ||
			_tiles[i].terrain == TR_WALL ||
			_tiles[i].terrain == TR_CLIFF)
			_attribute[i] |= ATTR_UNMOVAL;

		tileMap->frameRender(tankGameMap->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		/*if (_tiles[i].objType == OBJECT_BLOCK1) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCK3) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCKS) _attribute[i] |= ATTR_UNMOVAL;*/


		if (_tiles[i].objType == OBJECT_NONE || _tiles[i].objType == OBJECT_BLOCK1)
		{
			_tiles[i].obj = NULL;
			continue;
		}

		if (_tiles[i].objType == OBJECT_TRAP)
		{
			if (_tiles[i].objIndex == AWL_TRAP)
			{
				_tiles[i].obj = new AwlTrap(_objectCard._sampleObject[_tiles[i].objIndex].objImg,
					{ _tiles[i].rc.left,
					_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight() });
			}
			else if (_tiles[i].objIndex == BOMB_TRAP)
			{
				_tiles[i].obj = new Bomb(_objectCard._sampleObject[_tiles[i].objIndex].objImg,
					{ _tiles[i].rc.left,
					_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight() });
			}

		}
		else if (_tiles[i].objType == OBJECT_TRAP)
		{
			_tiles[i].obj = new Storage(_objectCard._sampleObject[_tiles[i].objIndex].objImg,
				{ _tiles[i].rc.left,
				_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight() });
		}
		else if (_tiles[i].objType == OBJECT_ENTRANCE || _tiles[i].objType == OBJECT_EXIT || _tiles[i].objType == OBJECT_DECO)
		{
			_objectCard._sampleObject[_tiles[i].objIndex].objImg->render(tankGameMap->getMemDC(), 
				(_tiles[i].rc.right + _tiles[i].rc.left - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getWidth()) * 0.5f,
				(_tiles[i].rc.bottom + _tiles[i].rc.top - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight()) * 0.5f);
		}
		else if (_tiles[i].objType == OBJECT_STORAGE)
		{
			_objectCard._sampleObject[_tiles[i].objIndex].objImg->render(tankGameMap->getMemDC(),
				_tiles[i].rc.left,
				_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight());

			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i+1].rc.left, _tiles[i+1].rc.top, 0, 0);
			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i+1 + TILEX].rc.left, _tiles[i+1 + TILEX].rc.top, 0, 0);
			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i - TILEX].rc.left, _tiles[i - TILEX].rc.top, 0, 0);
		}
		else
		{
			_tiles[i].obj = new Stuff(_objectCard._sampleObject[_tiles[i].objIndex].objImg,
				{ _tiles[i].rc.left,
				_tiles[i].rc.bottom - _objectCard._sampleObject[_tiles[i].objIndex].objImg->getHeight() });
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

void tileMap::load()
{
	load("tiles.map");
}
