#include "stdafx.h"
#include "FireDash.h"



HRESULT FireDash::init()
{
	Dash::init();


	_firePillar[FIRE_DASH_PILLAR_MAX];

	for (int i = 0; i < FIRE_DASH_PILLAR_MAX; ++i)
	{
		_firePillar[i] = new FirePillar;
		_firePillar[i]->init(20, 0, 5, 500, "stoneBullet");
	}

	return S_OK;
}

void FireDash::release()
{
}

void FireDash::update()
{
	_count = (_count + 1);
	if (_count % 10 == 0)
	{
		for (int i = 0; i < FIRE_DASH_PILLAR_MAX; +i)
		{
			if (_firePillar[i]->getIsActive())
				continue;

			_firePillar[i]->fire(_pixelMap, _x, _y, 0);
		}
	}
}

void FireDash::render()
{
}

void FireDash::fireBullet()
{
}

void FireDash::executeDash(float x, float y)
{
	_x = x; _y = y;
	_isActive = true;
}
