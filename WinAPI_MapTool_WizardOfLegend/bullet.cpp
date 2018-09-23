#include "stdafx.h"
#include "bullet.h"

HRESULT Bullet::init(float radius, float speed, float power, float range, const char * imageName)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_radius = radius;
	_speed = speed;
	_range = range;
	_power = power;
	_isActive = false;

	_x = _y = _fireX = _fireY = 0;
	_angle = 0;
	_gravity = 0;
	_count = _index = 0;

	_state = 1;

	return S_OK;
}


HRESULT Bullet::init()
{
	return S_OK;
}
void Bullet::release()
{
}

void Bullet::update()
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

	collide();

	if(_isActive)
		RENDERMANAGER->addRender(_y + WIZARD::HITBOX_HEIGHT, this);
}

void Bullet::render()
{
	if (_image == NULL)
	{
		Ellipse(getMemDC(), RectMake(_x, _y, 20, 20), CAM->getX(), CAM->getY());
		return;
	}
	//_image->frameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _index, _dir);
	_image->render(getMemDC(), _x - _image->getWidth()/2 - CAM->getX(), _y - _image->getHeight()/2 - CAM->getY());
}
void Bullet::fire(Image * pixelMap, float x, float y, float angle)
{
	_pixelMap = pixelMap;
	_fireX = _x = x; _fireY = _y = y;
	_angle = angle;

	_hitBox = RectMakeCenter(_x, _y, TILESIZE, TILESIZE);

	_isActive = true;
}


bool Bullet::collide(Actor * a)
{
	RECT temp;
	if (IntersectRect(&temp, &a->getHitBox(), &_hitBox))
	{
		a->damaged(this);
		_isActive = false;

		return true;
	}

	return false;
}

void Bullet::collide()
{
	COLORREF color = GetPixel(_pixelMap->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if ((r == 255 && g == 0 && b == 0))
	{
		if (_isActive) _isActive = false;
	}
}