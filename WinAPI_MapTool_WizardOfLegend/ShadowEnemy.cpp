#include "stdafx.h"
#include "ShadowEnemy.h"


HRESULT ShadowEnemy::init()
{
	Enemy::init();

	_img[ENEMY::IDLE] = IMAGEMANAGER->findImage("shadow_idle");
	_img[ENEMY::WALK] = IMAGEMANAGER->findImage("shadow_walk");
	_img[ENEMY::ATTACK] = IMAGEMANAGER->findImage("shadow_attack1");
	_img[ENEMY::HIT] = IMAGEMANAGER->findImage("shadow_dead");
	_img[ENEMY::DEAD] = _img[ENEMY::HIT];

	_img[ENEMY::FALL] = _img[ENEMY::IDLE];


	_delay[ENEMY::IDLE] = 100;
	_delay[ENEMY::WALK] = 5;
	_delay[ENEMY::ATTACK] = 25;
	_delay[ENEMY::HIT] = 5;
	_delay[ENEMY::FALL] = 100;
	_delay[ENEMY::DEAD] = 5;

	_state = ENEMY::APPEAR;
	_index = _dir = _count = 0;
	
	_speed = 0;

	_power = 20;
	_delayCount = 0;

	return S_OK;
}

void ShadowEnemy::release()
{
	Enemy::release();

}

void ShadowEnemy::update()
{
	if (_state == ENEMY::APPEAR)
	{
		if (_count == 0)
		{
			EFFECTMANAGER->play("������", _x, _y - ENEMY::MOVEBOX_HEIGHT / 2);
		}
		else if(_count >= APPEAR_COUNT)
			changeState(ENEMY::IDLE);
		
		++_count;

		return;
	}

	if (_state == ENEMY::FALL)
	{
		_z += 7;
		if (_count > FALL_COUNT)
		{
			_isActive = false;
		}
		RENDERMANAGER->addRender(_moveBox.bottom - _z, this);
		return;
	}

	if (_state == ENEMY::DEAD)
	{
		frameSetting();
		RENDERMANAGER->addRender(_moveBox.bottom - _z, this);
		return;
	}

	if (_delayCount <= 0)
	{
		if (getDistance(_x, _y, (*_player)->getX(), (*_player)->getY()) < TILESIZE + 10)
		{
			changeState(ENEMY::ATTACK);
		}

		if (_state != ENEMY::ATTACK)
		{
			moveToPlayer();
		}

		if (_state == ENEMY::ATTACK && _index == 1)
		{
			attack();
		}
	}
	else
	{
		_delayCount -= 1;
		_speed -= 0.5f;
		if (_speed < 0)
			_speed = 0;
	}

	move();
	collide();
	Enemy::update();

	if (_x > CAM->getX() - 100 && _x < CAM->getX() + WINSIZEX + 100 &&
		_y > CAM->getY() - 100 && _y < CAM->getY() + WINSIZEY + 100)
	{
		RENDERMANAGER->addRender(_moveBox.bottom - _z, this);
	}
}

void ShadowEnemy::render()
{
	frameSetting();
	if (!_isActive) return;

	Enemy::render();
	_img[_state]->frameRender(getMemDC(),
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() + _z - CAM->getY(), _index, _dir);
}


void ShadowEnemy::frameSetting()
{
	if (_state == ENEMY::HIT)
	{
		if (_delayCount <= 0)
			changeState(ENEMY::IDLE);
		return;
	}


	_count = _count + 1;
	if (_count % _delay[_state] == 0)
	{
		_index = _index + 1;
		if (_index > _img[_state]->getMaxFrameX())
		{
			_index = 0;
			if (_state == ENEMY::ATTACK)
			{
				changeState(ENEMY::IDLE);
				_delayCount = 50;
			}
			else if (_state == ENEMY::DEAD)
			{
				_isActive = false;
			}
		}
	}
}

void ShadowEnemy::attack()
{
	_attackBox = RectMakeCenter(_x + cos(_angle) * 50, _y - sin(_angle) * 50, 50, 50);

	RECT temp;
	if (IntersectRect(&temp, &((*_player)->getHitBox()), &_attackBox))
	{
		(*_player)->damaged(this);
	}
}


void ShadowEnemy::move()
{
	_x += cos(_angle) *_speed;
	_y += -sin(_angle) * _speed;

	if (_routingIndex > 0 && ((int)_x / TILESIZE) == _routing[_routingIndex].x && ((int)_y / TILESIZE) == _routing[_routingIndex].y)
		_routingIndex--;
	
}
