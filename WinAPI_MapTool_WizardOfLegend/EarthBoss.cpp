#include "stdafx.h"
#include "EarthBoss.h"


HRESULT EarthBoss::init()
{
	Enemy::init();

	_img[WIZARD::IDLE] = IMAGEMANAGER->findImage("earthBoss_idle");
	_img[WIZARD::ATTACK] = IMAGEMANAGER->findImage("earthBoss_attack1");
	_img[WIZARD::ATTACK_DELAY] = IMAGEMANAGER->findImage("earthBoss_attackDelay");
	_img[WIZARD::DEAD] = IMAGEMANAGER->findImage("earthBoss_dead");
	_img[WIZARD::HIT] = IMAGEMANAGER->findImage("earthBoss_hit");
	_img[WIZARD::FALL] = _img[WIZARD::IDLE];

	_delay[WIZARD::IDLE] = 100;
	_delay[WIZARD::ATTACK_DELAY] = 5;
	_delay[WIZARD::ATTACK] = 5;
	_delay[WIZARD::HIT] = 5;
	_delay[WIZARD::FALL] = 100;
	_delay[WIZARD::DEAD] = 5;

	_index = _dir = _count = 0;
	_speed = 0;

	_shootingAngle = 0;


	return S_OK;
}

void EarthBoss::release()
{
}

void EarthBoss::update()
{
	
	move();

	collide();
	_moveBox = RectMakeCenter(_x, _y, ENEMY::MOVEBOX_WIDTH, ENEMY::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(_x, _y, ENEMY::HITBOX_WIDTH, ENEMY::HITBOX_HEIGHT);
}

void EarthBoss::render()
{
	frameSetting();

	if (!_isActive) return;

	Enemy::render();

	_img[_state]->frameRender(getMemDC(),
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() + _z - CAM->getY(), _index, _dir);
}


void EarthBoss::frameSetting()
{
	if (_state == WIZARD::HIT)
	{
		if (_delayCount <= 0)
			changeState(WIZARD::IDLE);
		return;
	}

	_count = _count + 1;
	if (_count % _delay[_state] == 0)
	{
		_index = _index + 1;
		if (_index > _img[_state]->getMaxFrameX())
		{
			_index = 0;
			if (_state == WIZARD::ATTACK)
			{
				changeState(WIZARD::IDLE);
				_delayCount = 50;
			}
			else if (_state == WIZARD::DEAD)
			{
				_isActive = false;
			}

		}
	}
}

void EarthBoss::attack()
{
	_attack->attack(_x, _moveBox.bottom - _img[_state]->getFrameHeight() / 2, _shootingAngle);
}

void EarthBoss::move()
{
	_x += cos(_angle) *_speed;
	_y += -sin(_angle) * _speed;

	if (_routingIndex > 0 && ((int)_x / TILESIZE) == _routing[_routingIndex].x && ((int)_y / TILESIZE) == _routing[_routingIndex].y)
		_routingIndex--;
}
