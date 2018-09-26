#include "stdafx.h"
#include "WaterCircleBullet.h"


void WaterCircleBullet::update()
{
	_x += _speed * cosf(_angle);
	_y += _speed * -sinf(_angle);
	if (getDistance(_fireX, _fireY, _x, _y) >= _range)
	{
		_isActive = false;
	}
	_hitBox = RectMakeCenter(_x, _y, _radius * 2, _radius * 2);

	if (_image != NULL)
	{
		++_count;
		if (_count % 7 == 0) ++_index;
		if (_index > _image->getMaxFrameX()) _index = 0;
	}

	//Bullet::collide();

	if (_isActive)
		RENDERMANAGER->addRender(_y + WIZARD::HITBOX_HEIGHT, this);
}

void WaterCircleBullet::render()
{
	_image->frameRender(getMemDC(), _x - _image->getFrameWidth() / 2 - CAM->getX(), _y - _image->getFrameHeight() / 2 - CAM->getY(), _index, 0);
}

bool WaterCircleBullet::collide(Actor * a)
{
	RECT temp;
	if (IntersectRect(&temp, &a->getHitBox(), &_hitBox))
	{
		a->damaged(this);

		return true;
	}

	return false;
}

