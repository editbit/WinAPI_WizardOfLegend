#include "stdafx.h"
#include "StoneAttack.h"

HRESULT StoneAttack::init()
{
	Skill::init();

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

	_frameCount = 5;

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
	Skill::update();

	if (!_isActive)
		return;

	bool isFire = false;
	for (int i = 0; i < ATTACK_BULLET; ++i)
	{
		if (!_bullet[i]->getIsActive())
			continue;

		_bullet[i]->setX(_bullet[i]->getX() + cos(_player->getAngle()) * _player->getSpeed());
		_bullet[i]->setY(_bullet[i]->getY() - sin(_player->getAngle()) * _player->getSpeed());
		isFire = true;
	}

	if (!isFire)
	{
		_isActive = false;
	}
}

void StoneAttack::render()
{
}

Image* StoneAttack::attack(float x, float y, float angle)
{
	x = x + cos(angle) * _attackDistance;  y = y - sin(angle) * _attackDistance;

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

			_isActive = true;

			_coolTimeCount = 0;

			break;
		}

		break;
	}


	int t = _attackCount;

	_attackCount = (_attackCount + 1) % 2;
	return _motion[t];
}
