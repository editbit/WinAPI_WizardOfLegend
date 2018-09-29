#pragma once
#include "singletonBase.h"
//씬 전환등에 사용하도록 하자

class tileMap;

class SaveData : public SingletonBase <SaveData>
{
private:
	string _mapName;
	tileMap *_tileMap;

	POINT _startPos, _endPos;

	int _currentStage;

	int _hp;
	char _data[128];

public:
	HRESULT init();
	void release();

	void setCurrentStage(int stage) { _currentStage = stage; }
	int getCurrentStage() { return _currentStage; }

	void setStartPos(int x, int y) { _startPos = { x, y }; }
	POINT getStartPos() { return _startPos; }

	void setEndPos(int x, int y) { _endPos = { x, y }; }
	POINT getEndPos() { return _endPos; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	void setTileMap(tileMap *tiles) { _tileMap = tiles; }
	tileMap* getTileMap() { return _tileMap; }

	void setMapName(string mapName) { _mapName = mapName; }
	string getMapName() { return _mapName; }

	SaveData() : _tileMap(NULL), _currentStage(0){}
	~SaveData() {}
};

