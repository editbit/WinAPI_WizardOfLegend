#include "stdafx.h"
#include "AStarTest.h"
#include "AStarTile.h"
#include "tileMap.h"


HRESULT AStarTest::init(int maxWidthIndex, int maxHeightIndex)
{
	if (maxWidthIndex == 0)
		maxWidthIndex = TILEX;
	if (maxHeightIndex == 0)
		maxHeightIndex = TILEY;

	if (_totalList.size() > 0)
		release();

	_maxWidthIndex = maxWidthIndex;
	_maxHeightIndex = maxHeightIndex;

	AStarTile * node;

	for (int i = 0; i < maxHeightIndex; ++i)
	{
		for (int j = 0; j < maxWidthIndex; ++j)
		{
			node = new AStarTile;
			node->init(j, i);
			_totalList.push_back(node);
		}
	}

	return S_OK;
}

void AStarTest::release()
{
	for (int i = 0; i < _totalList.size(); ++i)
	{
		_totalList[i]->release();
		SAFE_DELETE(_totalList[i]);
	}
	_totalList.clear();
}

void AStarTest::setting(POINT start, POINT end)
{
	setting(start.x, start.y, end.x, end.y);
}

void AStarTest::setting(int startX, int startY, int endX, int endY)
{
	_startTile = _totalList[startY * _maxWidthIndex + startX];
	_endTile = _totalList[endY * _maxWidthIndex + endX];

	_currentTile = _startTile;
}

HRESULT AStarTest::initNode()
{
	_openList.clear();

	for (int i = 0; i < _maxHeightIndex; ++i)
	{
		for (int j = 0; j < _maxWidthIndex; ++j)
		{
			_totalList[i * _maxWidthIndex + j]->init(j, i);
		}
	}

	return S_OK;
}

HRESULT AStarTest::initNode(int startX, int startY)
{
	_openList.clear();

	int endX, endY;

	startX -= 50;
	startY -= 50;
	endX = startX + 100;
	endY = startY + 100;

	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;

	if (endX > _maxWidthIndex - 1) endX = _maxWidthIndex - 1;
	if (endY > _maxHeightIndex - 1) endY = _maxHeightIndex - 1;

	for (int i = startY; i < endY; ++i)
	{
		for (int j = startX; j < endX; ++j)
		{
			_totalList[i * _maxWidthIndex + j]->init(j, i);
		}
	}

	return S_OK;
}


vector<POINT> AStarTest::startPathFind(POINT start, POINT end, int range)
{
	return startPathFind(start.x, start.y, end.x, end.y, range);
}

vector<POINT> AStarTest::startPathFind(int startX, int startY, int endX, int endY, int range)
{
	//initNode();

	initNode(startX, startY);
	setting(startX, startY, endX, endY);

	AStarTile * tempTile;
	int closedTileIndex;

	while (true)
	{

		if (range < 0)
			return vector<POINT>();

		addOpenList(_currentTile);
		if (_openList.size() <= 0) return vector<POINT>();

		int totalCost = 100000000;
		for (int i = 0; i < _openList.size(); ++i)
		{
			if (totalCost > _openList[i]->getTotalCost())
			{
				totalCost = _openList[i]->getTotalCost();
				tempTile = _openList[i];
				closedTileIndex = i;
			}
		}

		if (tempTile == _endTile)
		{
			vector<POINT> routing;

			routing.push_back(tempTile->getIndex());
			
			while (_currentTile->getParent() != NULL)
			{
				routing.push_back(_currentTile->getIndex());
				_currentTile = _currentTile->getParent();
			}

			return routing;
		}

		tempTile->setState(ASTAR_CLOSE);
		_openList.erase(_openList.begin() + closedTileIndex);

		_currentTile = tempTile;

		range--;
	}
}

void AStarTest::addOpenList(AStarTile * currentTile)
{
	POINT temp = currentTile->getIndex();
	int startX = temp.x - 1,
		startY = temp.y - 1,
		endX = temp.x + 1,
		endY = temp.y + 1;

	if (startX < 0) startX = 0;
	else if (startX >= _maxWidthIndex) startX = _maxWidthIndex - 1;
	if (startY < 0) startY = 0;
	else if (startY >= _maxHeightIndex) startY = _maxHeightIndex - 1;

	if (endX < 0) endX = 0;
	else if (endX >= _maxWidthIndex) endX = _maxWidthIndex - 1;
	if (endY < 0) endY = 0;
	else if (endY >= _maxHeightIndex) endY = _maxHeightIndex - 1;


	DWORD * map = _tankMap->getAttribute();
	AStarTile * node;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			if (i == temp.y && j == temp.x) continue;

			node = _totalList[i * _maxWidthIndex + j];
			if (map[i * _maxWidthIndex + j] & ATTR_UNMOVAL && node != _endTile) continue;
			if (node->getState() == ASTAR_CLOSE) continue;
			if (node == _startTile)continue;
			if ((getDistance(currentTile->getPos().x, currentTile->getPos().y, node->getPos().x, node->getPos().y) > TILESIZE))
			{
				// 왼쪽 아래
				if (node->getIndex().x == currentTile->getIndex().x - 1 &&
					node->getIndex().y > currentTile->getIndex().y)
				{
					if (map[(i)* _maxWidthIndex + (j + 1)] & ATTR_UNMOVAL ||
						map[(i - 1)* _maxWidthIndex + (j)] & ATTR_UNMOVAL)
					{
						continue;
					}
				}
				// 왼쪽 위
				else if (node->getIndex().x == currentTile->getIndex().x - 1 &&
					node->getIndex().y < currentTile->getIndex().y)
				{
					if (map[(i)* _maxWidthIndex + (j + 1)] & ATTR_UNMOVAL ||
						map[(i + 1)* _maxWidthIndex + (j)] & ATTR_UNMOVAL)
					{
						continue;
					}
				}
				// 오른쪽 아래
				else if (node->getIndex().x == currentTile->getIndex().x + 1 &&
					node->getIndex().y > currentTile->getIndex().y)
				{
					if (map[(i)* _maxWidthIndex + (j - 1)] & ATTR_UNMOVAL ||
						map[(i - 1)* _maxWidthIndex + (j)] & ATTR_UNMOVAL)
					{
						continue;
					}
				}
				// 오른쪽 위
				else if (node->getIndex().x == currentTile->getIndex().x + 1 &&
					node->getIndex().y < currentTile->getIndex().y)
				{
					if (map[(i)* _maxWidthIndex + (j - 1)] & ATTR_UNMOVAL ||
						map[(i + 1)* _maxWidthIndex + (j)] & ATTR_UNMOVAL)
					{
						continue;
					}
				}
			}

			int costToEnd = ((abs(_endTile->getIndex().x - node->getIndex().x) + abs(_endTile->getIndex().y - node->getIndex().y)) * 10);
			POINT center1 = currentTile->getPos();
			POINT center2 = node->getPos();

			int costFromStart = currentTile->getCostFromStart() + ((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10);
			int totalCost = (costToEnd + costFromStart);

			if (node->getState() == ASTAR_NONE)
			{
				node->setParent(currentTile);
				node->setState(ASTAR_OPEN);

				node->setCostToEnd(costToEnd);
				node->setCostFromStart(costFromStart);
				node->setTotalCost(totalCost);

				_openList.push_back(node);
			}
			else if(node->getState() == ASTAR_OPEN)
			{
				if (totalCost < node->getTotalCost() || ( totalCost == node->getTotalCost() && costFromStart < node->getCostFromStart() ))
				{
					node->setParent(currentTile);
					node->setCostToEnd(costToEnd);
					node->setCostFromStart(costFromStart);
					node->setTotalCost(totalCost);
				}
			}

		}
	}
}

