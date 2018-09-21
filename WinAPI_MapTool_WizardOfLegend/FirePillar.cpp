#include "stdafx.h"
#include "FirePillar.h"

HRESULT FirePillar::init(float radius, float speed, float power, float range, const char * imageName)
{
	Bullet::init(radius, speed, power, range, imageName);

	_activeCount = 0;

	return S_OK;
}

HRESULT FirePillar::init()
{
	Bullet::init();

	_activeCount = 0;
	return S_OK;
}

void FirePillar::release()
{
	Bullet::release();
}

void FirePillar::update()
{
	_activeCount--;

	if (_activeCount == 0)
		_isActive = false;
	

	if (_isActive)
		RENDERMANAGER->addRender(_y + WIZARD::HITBOX_HEIGHT, this);
}

void FirePillar::render()
{
	if (_image == NULL)
	{
		Ellipse(getMemDC(), RectMake(_x, _y, 20, 20), CAM->getX(), CAM->getY());
		return;
	}

	_count = (_count + 1) % 5;
	if (_count == 0)
	{
		_index = (_index + 1) % (_image->getMaxFrameX() + 1);
		if (_index == 0)
		{
			_isActive = false;
			return;
		}
	}

	_image->frameRender(getMemDC(), _x - _image->getFrameWidth() / 2 - CAM->getX(), _hitBox.bottom - _image->getFrameHeight() - CAM->getY(), _index, 0);
}

void FirePillar::fire(Image * pixelMap, float x, float y, float angle)
{
	Bullet::fire(pixelMap, x, y, angle);
	
	_hitBox = RectMakeCenter(_x, _y, TILESIZE, TILESIZE);

	_activeCount = FIRE_COUNT_MAX;
}

bool FirePillar::collide(Actor * a)
{
	RECT temp;
	if (IntersectRect(&temp, &a->getHitBox(), &_hitBox))
	{
		a->damaged(this);

		return true;
	}

	return false;
}

void FirePillar::collide()
{
}
