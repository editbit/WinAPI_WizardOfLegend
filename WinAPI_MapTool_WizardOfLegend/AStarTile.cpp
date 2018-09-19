#include "stdafx.h"
#include "AStarTile.h"

HRESULT AStarTile::init()
{
	return init(0, 0);
}

HRESULT AStarTile::init(int x, int y)
{
	_index = {x, y};
	_pos = {x * TILESIZE + TILESIZE / 2, y * TILESIZE + TILESIZE / 2};

	_costFromStart = _costToEnd = _totalCost = 0;

	_state = ASTAR_NONE;

	_parent = NULL;

	return S_OK;
}
