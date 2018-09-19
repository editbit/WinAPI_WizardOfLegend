#include "stdafx.h"
#include "bullet.h"
HRESULT bullet::init(float radius, float speed, float power, float range, const char * imageName)
{
	if (strcmp(imageName, "없음") != 0) //문자열 비교함수 strcmp 
		_image = IMAGEMANAGER->findImage(imageName);
	else
		_image = NULL;
	_radius = radius;
	_speed = speed;
	_range = range;
	_power = power;
	_isActive = false;

	_x = _y = _fireX = _fireY = 0;
	_angle = 0;
	_gravity = 0;
	_count = _index = 0;

	return S_OK;
}

HRESULT bullet::init(float radius, float speed, float range, const char * imageName)
{
	if (strcmp(imageName, "없음") != 0) //문자열 비교함수 strcmp 
		_image = IMAGEMANAGER->findImage(imageName);
	else
		_image = NULL;
	_radius = radius;
	_speed = speed;
	_range = range;
	_power = 10;
	_isActive = false;

	_x = _y = _fireX = _fireY = 0;
	_angle = 0;
	_gravity = 0;
	_count = _index = 0;

	return S_OK;
	return S_OK;
}

void bullet::update()
{
	if (_isActive)
	{
		_x += _speed * cosf(_angle * 0.017f);
		_y += _speed * -sinf(_angle * 0.017f) + _gravity;
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
	}
}

void bullet::render(bool rotate)
{
	if (_isActive)
	{
		if (_image == NULL) Ellipse(getMemDC(), _hitBox.left - CAM->getX(), _hitBox.top - CAM->getY(), _hitBox.right - CAM->getX(),_hitBox.bottom-CAM->getY());
		else if(!rotate) _image->frameRender(getMemDC(), _x-CAM->getX(), _y-CAM->getY(), _index, _dir); //기본렌더
		else _image->rotateFrameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _index, 0, _angle*0.017); //회전렌더
	}
}

void bullet::release()
{
}

bool bullet::collide(string pixelImageName)
{
	//벽과 충돌할떄
	COLORREF color = GetPixel(IMAGEMANAGER->findImage(pixelImageName)->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if (!(r == 255 && g == 0 && b == 255))
	{
		if(_isActive) _isActive = false;
		return true;
	}

	//사거리 벗어남
	float distance = getDistance(_fireX, _fireY, _x, _y);
	if (_range < distance)
	{
		_isActive = false;
	}

	//플레이어랑 충돌도 만들자
	return false;
}

bool bullet::collide(Image * pixelImage)
{
	//벽과 충돌할떄
	COLORREF color = GetPixel(pixelImage->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_isActive) _isActive = false;
		return true;
	}

	//사거리 벗어남
	float distance = getDistance(_fireX, _fireY, _x, _y);
	if (_range < distance)
	{
		_isActive = false;
	}

	return false;
}
