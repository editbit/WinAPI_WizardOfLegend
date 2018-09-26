#include "stdafx.h"
#include "StoneAttack.h"

HRESULT StoneAttack::init()
{
	_iconImg = IMAGEMANAGER->findImage("stoneAttackIcon");
	_skillType = ATTACK_SKILL;
	_attackCount = 0;

	_power = 40;

	for (int i = 0; i < ATTACK_BULLET; ++i)
	{
		_bullet[i] = new AttackBullet;
		_bullet[i]->init(TILESIZE / 2, 0, _power, 500, "stoneBullet");
	}

	_description = "근접 스킬";

	return S_OK;
}

void StoneAttack::release()
{
	for (int i = 0; i < ATTACK_BULLET; ++i)
	{
		_bullet[i]->release();
		SAFE_DELETE(_bullet[i]);
	}
}

void StoneAttack::update()
{
}

void StoneAttack::render()
{
}

Image* StoneAttack::attack(float x, float y, float angle)
{
	x = x + cos(angle) * 80;  y = y - sin(angle) * 80;

	for (int i = 0; i < ATTACK_BULLET; ++i)
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
