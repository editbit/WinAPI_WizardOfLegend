#pragma once
#include "singletonBase.h"
//씬 전환등에 사용하도록 하자

class tileMap;

class SaveData : public SingletonBase <SaveData>
{
private:
	string _mapName;
	tileMap *_tileMap;

	int _hp;
	char _data[128];

public:
	HRESULT init();
	void release();

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	void setTileMap(tileMap *tiles) { _tileMap = tiles; }
	tileMap* getTileMap() { return _tileMap; }

	void setMapName(string mapName) { _mapName = mapName; }
	string getMapName() { return _mapName; }

	SaveData() : _tileMap(NULL) {}
	~SaveData() {}
};


//예시
//체력 저장
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	SAVEDATA->setHp(_currentHp);
//}
////체력 로드
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	_currentHp = SAVEDATA->getHp();
//}

