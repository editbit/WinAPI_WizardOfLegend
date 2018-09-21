#include "stdafx.h"
#include "FireDash.h"



HRESULT FireDash::init()
{
	Dash::init();


	_firePillar[FIRE_DASH_PILLAR_MAX];

	for (int i = 0; i < FIRE_DASH_PILLAR_MAX; ++i)
	{
		_firePillar[i] = new FirePillar;
		_firePillar[i]->init(20, 0, 5, 500, "ice_skill");
	}

	_isActive = false;

	_iconImg = IMAGEMANAGER->findImage("fireDash1Icon");
	return S_OK;
}

void FireDash::release()
{
}

void FireDash::update()
{
	_count = (_count + 1);

	if (_count % 30 == 0 || _player->getState() != WIZARD::DASH)
	{
		_isActive = false;
		_count = 0;

		return;
	}

	if (_player->getIndex() >= 2)
	{
		_isActive = false;
		_count = 0;

		return;
	}

	if (_count % 5 == 1)
	{

		vector<Bullet *>& playerBullet = BULLETMANAGER->getPlayerBullets();
		for (int i = 0; i < FIRE_DASH_PILLAR_MAX; ++i)
		{
			if (_firePillar[i]->getIsActive())
				continue;

			_firePillar[i]->fire(_pixelMap, _x, _y, 0);

			for (int j = 0; j < playerBullet.size(); ++j)
			{
				if (playerBullet[j] == NULL)
				{
					playerBullet[j] = _firePillar[i];
					break;
				}
			}

			break;
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
