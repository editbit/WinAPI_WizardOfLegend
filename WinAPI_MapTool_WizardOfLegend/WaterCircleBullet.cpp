#include "stdafx.h"
#include "WaterCircleBullet.h"


HRESULT WaterCircleBullet::init(float radius, float speed, float power, float range, const char * imageName)
{
	_circleAngle = 0;
	return Bullet::init(radius, speed, power, range, imageName);
}

void WaterCircleBullet::update()
{
	x = _x + _speed * cosf(_circleAngle + _angle);
	y = _y +  _speed * -sinf(_circleAngle + _angle);
	_circleAngle += 0.09f * _dir;

	if (_circleAngle >= 2 * PI || _circleAngle <= -2 * PI)
	{
		_isActive = false;
	}
	_hitBox = RectMakeCenter(x, y, _radius * 2, _radius * 2);

	if (_image != NULL)
	{
		++_count;
		if (_count % 2 == 0) ++_index;
		if (_index > _image->getMaxFrameX()) _index = 0;
	}

	//Bullet::collide();

	if (_isActive)
		RENDERMANAGER->addRender(y + WIZARD::HITBOX_HEIGHT, this);
}

void WaterCircleBullet::render()
{
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2 - CAM->getX(), y - _image->getFrameHeight() / 2 - CAM->getY(), _index, 0);
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

void WaterCircleBullet::fire(Image * pixelMap, float x, float y, float angle, int dir)
{
	Bullet::fire(pixelMap, x, y, angle);
	_circleAngle = 0;
	this->x = x;
	this->y - y;

	_dir = dir;
}

