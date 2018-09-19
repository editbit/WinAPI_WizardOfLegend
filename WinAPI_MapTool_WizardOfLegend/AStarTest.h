#pragma once
#include <vector>
#include <string>

class tileMap;
class AStarTile;

class AStarTest : public SingletonBase<AStarTest>
{
private:
	int _maxWidthIndex, _maxHeightIndex;

	vector<AStarTile*> _totalList;

	vector<AStarTile*> _openList;

	AStarTile * _startTile;
	AStarTile * _endTile;
	AStarTile * _currentTile;

	tileMap * _tankMap;


public:
	HRESULT init(int maxWidthIndex = 0, int maxHeightIndex = 0);
	void release();

	void setting(POINT start, POINT end);
	void setting(int startX, int startY, int endX, int endY);
	HRESULT initNode();
	HRESULT initNode(int startX, int startY);

	vector<POINT> startPathFind(POINT start, POINT end, int range = 5);
	vector<POINT> startPathFind(int startX, int startY, int endX, int endY, int range = 5);

	void addOpenList(AStarTile * currentTile);

	void setTankMap(tileMap *map) { _tankMap = map; }

	AStarTest() {}
	~AStarTest() {}
};

