#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include <string>

enum { ASTAR_NONE, ASTAR_OPEN, ASTAR_CLOSE };

class AStarTile :
	public GameNode
{
private:
	POINT _index, _pos;

	int _costFromStart;
	int _costToEnd;
	int _totalCost;

	int _state;

	AStarTile * _parent;

public:

	virtual HRESULT init();
	HRESULT init(int x, int y);
	virtual void release() {}
	virtual void update() {}
	virtual void render() {}

	POINT getIndex() { return _index; }
	POINT getPos() { return _pos; }

	int getCostFromStart() { return _costFromStart; }
	int getCostToEnd() { return _costToEnd; }
	int getTotalCost() { return _costFromStart + _costToEnd; }
	int getState() { return _state; }
	AStarTile * getParent() { return _parent; }

	void setCostFromStart(int costFromStart) { _costFromStart = costFromStart; }
	void setCostToEnd(int costToEnd) { _costToEnd = costToEnd; }
	void setTotalCost(int totalCost) { _totalCost = totalCost; }
	void setState(int state) { _state = state; }
	void setParent(AStarTile * parent) { _parent = parent; }

	AStarTile() { init(); }
	~AStarTile() {}
};

