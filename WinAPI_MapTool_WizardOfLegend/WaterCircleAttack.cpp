#include "stdafx.h"
#include "WaterCircleAttack.h"

HRESULT WaterCircleAttack::init()
{
	_iconImg = IMAGEMANAGER->findImage("waterCircleIcon");
	_skillType = ATTACK_SKILL;
	_attackCount = 0;

	_power = 40;

	for (int i = 0; i < WATER_CIRCLE_BAX; ++i)
	{
		_bullet[i] = new WaterCircleBullet;
		_bullet[i]->init(TILESIZE / 2, 0, _power, 500, "water_skill");
	}

	_description = "근접 스킬";

	return S_OK;
}

void WaterCircleAttack::release()
{
	for (int i = 0; i < WATER_CIRCLE_BAX; ++i)
	{
		_bullet[i]->release();
		SAFE_DELETE(_bullet[i]);
	}
}

void WaterCircleAttack::update()
{
}

void WaterCircleAttack::render()
{
}

Image * WaterCircleAttack::attack(float x, float y, float angle)
{
	x = x + cos(angle) * 80;  y = y - sin(angle) * 80;

	for (int i = 0; i < WATER_CIRCLE_BAX; ++i)
	{
		if (_bullet[i]->getIsActive())
			continue;

		for (int j = 0; j < _bulletList->size(); ++j)
		{
			if (_bulletList->at(j) != NULL)
				continue;

			_bullet[i]->fire(_pixelMap, x, y, angle);

			_bulletList->at(j) = _bullet[i];

			break;
		}

		break;
	}


	int t = _attackCount;

	_attackCount = (_attackCount + 1) % 2;
	return _motion[t];
}
