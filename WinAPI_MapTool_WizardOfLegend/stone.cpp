#include "stdafx.h"
#include "stone.h"


HRESULT stone::init()
{
	_x = RND->getInt(CAM->getMaxWidth());
	_y = RND->getInt(CAM->getMaxHeight());
	_z = RND->getInt(4) + 1;
	_speed = 1;
	_dirY = RND->getInt(300)/10.0f;

	int c = RND->getInt(2);

	switch (c)
	{
	case 0:
		_img = IMAGEMANAGER->findImage("µ¹1");
		break;
	case 1:
		_img = IMAGEMANAGER->findImage("µ¹2");
		break;
	}

	return S_OK;
}

void stone::release()
{
}

void stone::update()
{
	_dirY += 0.01f;
	if (_dirY > 2 * PI)
	{
		_dirY -= 2 * PI;
	}
	_y += -sin(_dirY) * _speed;
}

void stone::render()
{
}
