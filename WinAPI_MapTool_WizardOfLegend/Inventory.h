#pragma once
#include "gameNode.h"
#include "Dash.h"

class Inventory :
	public GameNode
{
	Image *_img;

	vector<Dash*> _dashList;

public:
	Inventory() {}
	~Inventory() {}
};

