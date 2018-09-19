#pragma once
#include "backgroundActor.h"
class stone :
	public BackgroundActor
{
	float _dirY;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	stone() {}
	~stone() {}
};

