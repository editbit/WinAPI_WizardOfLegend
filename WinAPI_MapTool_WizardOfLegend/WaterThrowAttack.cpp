#include "stdafx.h"
#include "WaterThrowAttack.h"

HRESULT WaterThrowAttack::init()
{
	_iconImg = IMAGEMANAGER->findImage("waterThrowIcon");
	_skillType = ATTACK_SKILL;
	_attackCount = 0;

	for (int i = 0; i < STONE_THROW_MAX; ++i)
	{
		_bullet[i] = new WaterThrowBullet;
		_bullet[i]->init(TILESIZE / 2, 5, 5, 500, "water_skill");
	}
	return S_OK;
}

void WaterThrowAttack::release()
{
	for (int i = 0; i < STONE_THROW_MAX; ++i)
	{
		_bullet[i]->release();
		SAFE_DELETE(_bullet[i]);
	}
}

void WaterThrowAttack::update()
{
}

void WaterThrowAttack::render()
{
}

Image * WaterThrowAttack::attack(float x, float y, float angle)
{
	x = x + cos(angle) * 70;  y = y - sin(angle) * 70;

	vector<Bullet *>& playerBullet = BULLETMANAGER->getPlayerBullets();
	for (int i = 0; i < STONE_THROW_MAX; ++i)
	{
		if (_bullet[i]->getIsActive())
			continue;

		for (int j = 0; j < playerBullet.size(); ++j)
		{
			if (playerBullet[j] != NULL)
				continue;

			_bullet[i]->fire(_pixelMap, x, y, angle);

			playerBullet[j] = _bullet[i];

			break;
		}

		break;
	}


	int t = _attackCount;

	_attackCount = (_attackCount + 1) % 2;
	return _motion[t];
}
