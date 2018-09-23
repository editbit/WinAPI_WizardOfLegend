#include "stdafx.h"
#include "StoneAttack.h"

HRESULT StoneAttack::init()
{
	_iconImg = IMAGEMANAGER->findImage("stoneAttackIcon");
	_skillType = ATTACK_SKILL;
	_attackCount = 0;

	for (int i = 0; i < ATTACK_BULLET; ++i)
	{
		_bullet[i] = new AttackBullet;
		_bullet[i]->init(TILESIZE / 2, 0, 5, 500, "stoneBullet");
	}

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
	vector<Bullet *>& playerBullet = BULLETMANAGER->getPlayerBullets();
	for (int i = 0; i < ATTACK_BULLET; ++i)
	{
		if (_bullet[i]->getIsActive())
			continue;

		for (int j = 0; j < playerBullet.size(); ++j)
		{
			if (playerBullet[j] == NULL)
				continue;

			_bullet[i]->fire(_pixelMap, x, y, angle);
			
			playerBullet[j] = _bullet[i];

			break;
		}

		break;
	}

	return _motion[_attackCount];
}
