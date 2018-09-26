#include "stdafx.h"
#include "StoneThrowAttack.h"

HRESULT StoneThrowAttack::init()
{
	_iconImg = IMAGEMANAGER->findImage("stoneThrowIcon");
	_skillType = ATTACK_SKILL;
	for (int i = 0; i < STONE_THROW_BULLET_MAX; ++i)
	{
		_bullet[i] = new Bullet;
		_bullet[i]->init(TILESIZE / 2, 5, 5, 500, "stoneBullet");
	}

	_description = "돌을 던지는 스킬";
	return S_OK;
}

void StoneThrowAttack::release()
{
	for (int i = 0; i < STONE_THROW_BULLET_MAX; ++i)
	{
		_bullet[i]->release();
		SAFE_DELETE(_bullet[i]);
	}
}

void StoneThrowAttack::update()
{
}

void StoneThrowAttack::render()
{
}

Image * StoneThrowAttack::attack(float x, float y, float angle)
{
	x = x + cos(angle) * 70;  y = y - sin(angle) * 70;

	angle -= PI / 6;

	int count = 0;
	for (int i = 0; i < STONE_THROW_BULLET_MAX; ++i)
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
		++count;
		angle += PI / 6;
		if (count >= 3)
			break;
	}


	return _motion[0];
}
