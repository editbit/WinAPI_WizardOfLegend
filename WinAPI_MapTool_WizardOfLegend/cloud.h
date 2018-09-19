#pragma once
#include "backgroundActor.h"
class cloud :
	public BackgroundActor
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void changeImage();

	cloud() {}
	~cloud() {}
};

