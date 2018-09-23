#include "stdafx.h"
#include "WaterThrowBullet.h"


void WaterThrowBullet::render()
{
	_image->frameRender(getMemDC(), _x - _image->getFrameWidth() / 2 - CAM->getX(), _y - _image->getFrameHeight() / 2 - CAM->getY(), _index, 0);
}


bool WaterThrowBullet::collide(Actor * a)
{
	//if (_index != 0)
	//	return false;

	RECT temp;
	if (IntersectRect(&temp, &a->getHitBox(), &_hitBox))
	{
		a->damaged(this);

		return true;
	}

	return false;
}