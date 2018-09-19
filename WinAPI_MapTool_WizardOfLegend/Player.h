#pragma once
#include "gameNode.h"
#include "Wizard.h"

class Player :
	public GameNode
{
	Actor * _wizard;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Player() {}
	~Player() {}
};

