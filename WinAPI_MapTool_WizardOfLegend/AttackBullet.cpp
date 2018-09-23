#include "stdafx.h"
#include "AttackBullet.h"



HRESULT AttackBullet::init(float radius, float speed, float power, float range, const char * imageName)
{
	Bullet::init(radius, speed, power, range, imageName);
	return S_OK;
}

HRESULT AttackBullet::init()
{
	return S_OK;
}

void AttackBullet::update()
{
	_count = (_count + 1) % 5;
	if (_count == 0)
	{
		_index = (_index + 1);

		if (_index >= 3)
			_isActive = false;
	}

	if (_isActive)
		RENDERMANAGER->addRender(_y + WIZARD::HITBOX_HEIGHT, this);
}

void AttackBullet::render()
{
	_image->render(getMemDC(), _x - _image->getWidth()/2, _y - _image->getHeight()/2);
}

void AttackBullet::release()
{
}

void AttackBullet::fire(Image * pixelMap, float x, float y, float angle)
{
	Bullet::fire(pixelMap, x, y, angle);

	_hitBox = RectMakeCenter(_x, _y, _radius*2, _radius*2);
}

bool AttackBullet::collide(Actor * a)
{
	if (_index != 0)
		return false;

	RECT temp;
	if (IntersectRect(&temp, &a->getHitBox(), &_hitBox))
	{
		a->damaged(this);

		return true;
	}

	return false;
}

