#include "stdafx.h"
#include "tileMap.h"
#include "AwlTrap.h"
#include "Bomb.h"

HRESULT tileMap::init(const char * fileName)
{
	_objectCard.init(0, 0);
	this->load(fileName);

	return S_OK;
}

HRESULT tileMap::init(void)
{
	//맵 로드
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

	// 오브젝트의 경우 z오더 적용을 위해 배경을 위한 빈 비트맵에 렌더해 놓지 않고 실시간으로 렌더.

	for (int i = startY; i < endY; i++)
	{
		for (int j = startX; j < endX; ++j)
		{
			if (_tiles[i * TILEX + j].objType == OBJECT_NONE || _tiles[i * TILEX + j].objType == OBJECT_BLOCK1) continue;
			//_objectCard._sampleObject[_tiles[i*TILEX +j].objIndex].objImg->render(getMemDC(), _tiles[i * TILEX + j].rc.left - CAM->getX(), _tiles[i * TILEX + j].rc.bottom - _objectCard._sampleObject[_tiles[i*TILEX + j].objIndex].objImg->getHeight() - CAM->getY());

			_tiles[i*TILEX + j].obj->update();
			RENDERMANAGER->addRender(_tiles[i*TILEX + j].rc.bottom, _tiles[i*TILEX + j].obj);
		}
	}
}

void tileMap::render(void)
{
	////전체화면 지형을 그린다
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//}
	////전체화면 오브젝트를 그린다
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].objType == OBJECT_NONE) continue;
	//	IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objIndex, _tiles[i].objFrameY);
	//}
}

bool tileMap::prepareLoading(const char* fileName)
{
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

	return false;
}

bool tileMap::loadingDone()
{
	if (_loadingIndex >= TILEX * TILEY)
		return true;

	//맵 속성 정의
	Image * tileMap = IMAGEMANAGER->findImage("tilemap");
	Image * pixelTile = IMAGEMANAGER->findImage("pixel_tile");
	Image * tankGameMap = IMAGEMANAGER->findImage("tileMapImage");
	Image * tankGamePixel = IMAGEMANAGER->findImage("tileMapPixel");

	for(int j = 0 ; _loadingIndex < TILEX * TILEY && j< 200;++j, _loadingIndex++)
	{
		if (_tiles[_loadingIndex].terrain == TR_WALL ||
			_tiles[_loadingIndex].terrain == TR_CLIFF)
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;

		pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, _tiles[_loadingIndex].terrainFrameX, _tiles[_loadingIndex].terrainFrameY);


		if (_tiles[_loadingIndex].objType == OBJECT_NONE || _tiles[_loadingIndex].objType == OBJECT_BLOCK1)
			_tiles[_loadingIndex].obj = NULL;

		if (_tiles[_loadingIndex].objType == OBJECT_WALL ||
			_tiles[_loadingIndex].objType == OBJECT_BLOCK1)
		{
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;
			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, 0, 0);
		}
		if (_tiles[_loadingIndex].objType == OBJECT_BREAKABLE || _tiles[_loadingIndex].objType == OBJECT_TRAP)
			_attribute[_loadingIndex] |= ATTR_UNMOVAL;

		tileMap->frameRender(tankGameMap->getMemDC(), _tiles[_loadingIndex].rc.left, _tiles[_loadingIndex].rc.top, _tiles[_loadingIndex].terrainFrameX, _tiles[_loadingIndex].terrainFrameY);

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
			else
			{
				_tiles[_loadingIndex].obj = new Stuff(_objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg,
					{ _tiles[_loadingIndex].rc.left,
					_tiles[_loadingIndex].rc.bottom - _objectCard._sampleObject[_tiles[_loadingIndex].objIndex].objImg->getHeight() });
			}
		}
	}

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

	//맵 속성 정의
	memset(_attribute, 0, sizeof(DWORD)* TILEX * TILEY); 
	Image * tileMap = IMAGEMANAGER->findImage("tilemap");
	Image * pixelTile = IMAGEMANAGER->findImage("pixel_tile");
	Image * tankGameMap = IMAGEMANAGER->findImage("tileMapImage");
	Image * tankGamePixel = IMAGEMANAGER->findImage("tileMapPixel");
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//물지형 및 블럭오브젝트들은 탱크가 지나다닐 수 없으니
		//속성을 attr_unmoval로 정의한다
		//불변수로 처리해도 상관없다

		
		
		if (_tiles[i].terrain == TR_WALL ||
			_tiles[i].terrain == TR_CLIFF)
			_attribute[i] |= ATTR_UNMOVAL;

		pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		

		if (_tiles[i].objType == OBJECT_NONE || _tiles[i].objType == OBJECT_BLOCK1)
			_tiles[i].obj = NULL;

		if (_tiles[i].objType == OBJECT_WALL ||
			_tiles[i].objType == OBJECT_BLOCK1)
		{
			_attribute[i] |= ATTR_UNMOVAL;
			pixelTile->frameRender(tankGamePixel->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, 0, 0);
		}
		if(_tiles[i].objType == OBJECT_BREAKABLE || _tiles[i].objType == OBJECT_TRAP)
			_attribute[i] |= ATTR_UNMOVAL;

		tileMap->frameRender(tankGameMap->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		/*if (_tiles[i].objType == OBJECT_BLOCK1) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCK3) _attribute[i] |= ATTR_UNMOVAL;
		if (_tiles[i].objType == OBJECT_BLOCKS) _attribute[i] |= ATTR_UNMOVAL;*/


		if (_tiles[i].objType == OBJECT_NONE || _tiles[i].objType == OBJECT_BLOCK1) continue;

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
