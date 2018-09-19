#include "stdafx.h"
#include "cloud.h"

HRESULT cloud::init()
{
	_x = RND->getInt(CAM->getMaxWidth());
	_y = RND->getInt(CAM->getMaxHeight());
	_z = RND->getInt(4) + 1;
	_speed = 0.5f;
	
	changeImage();

	return S_OK;
}

void cloud::release()
{
}

void cloud::update()
{
	_x += _speed;
	if (_x - _img->getWidth()  > CAM->getMaxWidth())
	{
		changeImage();
		_x = -_img->getWidth()*7;
		_x -= RND->getInt(100);
	}
}

void cloud::render()
{
}


void cloud::changeImage()
{
	int c = RND->getInt(7);

	switch (c)
	{
	case 0:
		_img = IMAGEMANAGER->findImage("备抚1");
		break;
	case 1:
		_img = IMAGEMANAGER->findImage("备抚2");
		break;
	case 2:
		_img = IMAGEMANAGER->findImage("备抚3");
		break;
	case 3:
		_img = IMAGEMANAGER->findImage("备抚4");
		break;
	case 4:
		_img = IMAGEMANAGER->findImage("备抚5");
		break;
	case 5:
		_img = IMAGEMANAGER->findImage("备抚6");
		break;
	case 6:
		_img = IMAGEMANAGER->findImage("备抚7");
		break;
	}
}
