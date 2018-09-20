#include "stdafx.h"
#include "Magician.h"




HRESULT Magician::init()
{
	_img[ENEMY::IDLE] = IMAGEMANAGER->findImage("mage_idle");
	_img[ENEMY::WALK] = IMAGEMANAGER->findImage("mage_walk");
	_img[ENEMY::ATTACK] = IMAGEMANAGER->findImage("mage_attack1");
	_img[ENEMY::ATTACK + 1] = IMAGEMANAGER->findImage("mage_attack2");
	_img[ENEMY::HIT] = IMAGEMANAGER->findImage("mage_dead");
	_img[ENEMY::DEAD] = _img[ENEMY::HIT];

	_img[ENEMY::FALL] = _img[ENEMY::IDLE];


	_delay[ENEMY::IDLE] = 100;
	_delay[ENEMY::WALK] = 5;
	_delay[ENEMY::ATTACK] = 10;
	_delay[ENEMY::HIT] = 5;
	_delay[ENEMY::FALL] = 100;
	_delay[ENEMY::DEAD] = 5;

	_state = ENEMY::IDLE;
	_index = _dir = _count = 0;

	_speed = ENEMY::WALK_SPEED;

	_delayCount = 0;

	tempBullet = new Bullet;
	tempBullet->init(20, 5, 5, 500, "stoneBullet");
	_shootingAngle = 0;

	return S_OK;
}

void Magician::release()
{
	tempBullet->release();
	SAFE_DELETE(tempBullet);
}

void Magician::update()
{

	if (_state == ENEMY::DEAD)
		return;

	if (_delayCount > 0)
	{
		_delayCount -= 1;
		return;
	}

	if (getDistance(_x, _y, (*_player)->getX(), (*_player)->getY()) < TILESIZE * 5)
	{
		changeState(ENEMY::ATTACK);
		_shootingAngle = getAnglef(_x, _y, (*_player)->getX(), (*_player)->getY());
	}
	else if (_state != ENEMY::ATTACK)
	{
		moveToPlayer();
		if (_state == ENEMY::WALK)
			move();
	}
	
	if(_state == ENEMY::ATTACK)
	{
		if(_index == _img[_state]->getMaxFrameX() - 1)
			attack();
	}


	collide();
	_moveBox = RectMakeCenter(_x, _y, ENEMY::MOVEBOX_WIDTH, ENEMY::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(_x, _y, ENEMY::HITBOX_WIDTH, ENEMY::HITBOX_HEIGHT);
}

void Magician::render()
{
	frameSetting();

	if (!_isActive) return;


	_img[_state]->frameRender(getMemDC(),
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() - CAM->getY(), _index, _dir);

	if (_state == ENEMY::ATTACK && _index >= 3 && _index < _img[_state]->getMaxFrameX() - 1)
	{
		//Ellipse(getMemDC(), RectMakeCenter(_x, _moveBox.bottom - _img[_state]->getFrameHeight()/2, 20, 20), CAM->getX(), CAM->getY());
		tempBullet->getImage()->render(getMemDC(), _x - tempBullet->getImage()->getWidth()/2 - CAM->getX(), _moveBox.bottom - _img[_state]->getFrameHeight() / 2 - tempBullet->getImage()->getHeight()/2 - CAM->getY());
	}
}


void Magician::frameSetting()
{
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

void Magician::attack()
{
	if (tempBullet->getIsActive())
		return;

	tempBullet->fire(_pixelMap, _x, _moveBox.bottom - _img[_state]->getFrameHeight() / 2, _shootingAngle);

	vector<Bullet *>& enemyBullet = BULLETMANAGER->getEnemyBullets();
	for (int i = 0; i < enemyBullet.size(); ++i)
	{
		if (enemyBullet[i] == NULL)
		{
			enemyBullet[i] = tempBullet;
			break;
		}
	}
}

void Magician::damaged(Actor * e)
{
	changeState(ENEMY::DEAD);
}

void Magician::move()
{
	_x += cos(_angle) *_speed;
	_y += -sin(_angle) * _speed;

	if (_routingIndex > 0 && ((int)_x / TILESIZE) == _routing[_routingIndex].x && ((int)_y / TILESIZE) == _routing[_routingIndex].y)
		_routingIndex--;

}
