#pragma once
#include "singletonBase.h"
//�� ��ȯ� ����ϵ��� ����

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


//����
//ü�� ����
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	SAVEDATA->setHp(_currentHp);
//}
////ü�� �ε�
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	_currentHp = SAVEDATA->getHp();
//}

