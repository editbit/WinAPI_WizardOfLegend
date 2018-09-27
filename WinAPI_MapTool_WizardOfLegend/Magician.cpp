#include "stdafx.h"
#include "Magician.h"




HRESULT Magician::init()
{
	Enemy::init();

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

	_speed = 0;


	_shootingAngle = 0;

	if (RND->getInt(2) == 0)
	{
		_attack = new WaterThrowAttack;
		_attack->setLinkBulletList(BULLETMANAGER->getEnemyBullets());
		_attack->setLinkPlayer(*_player);
		_attack->setLinkPixelMap(_pixelMap);
		_attack->setLinkEnemyManager(NULL);
		_attack->setMotion(0, IMAGEMANAGER->findImage("player_attack1"));
		_attack->setMotion(1, IMAGEMANAGER->findImage("player_attack2"));
		_attack->init();
	}
	else
	{
		_attack = new StoneThrowAttack;
		_attack->setLinkBulletList(BULLETMANAGER->getEnemyBullets());
		_attack->setLinkPlayer(*_player);
		_attack->setLinkPixelMap(_pixelMap);
		_attack->setLinkEnemyManager(NULL);
		_attack->setMotion(0, IMAGEMANAGER->findImage("player_attack1"));
		_attack->setMotion(1, IMAGEMANAGER->findImage("player_attack2"));
		_attack->init();
	}

	return S_OK;
}

void Magician::release()
{
	Enemy::release();

	_attack->release();
	SAFE_DELETE(_attack);
}

void Magician::update()
{

	if (_state == ENEMY::FALL)
	{
		_z += 7;
		if (_count > FALL_COUNT)
		{
			_isActive = false;
		}
		return;
	}

	if (_state == ENEMY::DEAD)
		return;

	if (_delayCount <= 0)
	{
		if (getDistance(_x, _y, (*_player)->getX(), (*_player)->getY()) < TILESIZE * 5)
		{
			changeState(ENEMY::ATTACK);
			_shootingAngle = getAnglef(_x, _y, (*_player)->getX(), (*_player)->getY());
		}
		else if (_state != ENEMY::ATTACK)
		{
			moveToPlayer();
			//if (_state == ENEMY::WALK)
			//	move();
		}
		if (_state == ENEMY::ATTACK)
		{
			if (_index == _img[_state]->getMaxFrameX() - 1 && _count % _delay[_state] == 0)
			{
				attack();
			}
		}
	}
	else
	{
		_delayCount -= 1;
		_speed -= 0.5f;
		if (_speed < 0)
			_speed = 0;
	}


	//if(_state != ENEMY::IDLE && _state != ENEMY::FALL && _state != ENEMY::ATTACK)
	move();

	collide();
	Enemy::update();
}

void Magician::render()
{
	frameSetting();

	if (!_isActive) return;

	Enemy::render();

	_img[_state]->frameRender(getMemDC(),
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() + _z - CAM->getY(), _index, _dir);

	//if (_state == ENEMY::ATTACK && _index >= 3 && _index < _img[_state]->getMaxFrameX() - 1)
	//{
	//	//Ellipse(getMemDC(), RectMakeCenter(_x, _moveBox.bottom - _img[_state]->getFrameHeight()/2, 20, 20), CAM->getX(), CAM->getY());
	//	tempBullet->getImage()->render(getMemDC(), _x - tempBullet->getImage()->getWidth()/2 - CAM->getX(), _moveBox.bottom - _img[_state]->getFrameHeight() / 2 - tempBullet->getImage()->getHeight()/2 - CAM->getY());
	//}
}


void Magician::frameSetting()
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

void Magician::attack()
{

	_attack->attack(_x, _moveBox.bottom - _img[_state]->getFrameHeight() / 2, _shootingAngle);

}

void Magician::move()
{
	_x += cos(_angle) *_speed;
	_y += -sin(_angle) * _speed;

	if (_routingIndex > 0 && ((int)_x / TILESIZE) == _routing[_routingIndex].x && ((int)_y / TILESIZE) == _routing[_routingIndex].y)
		_routingIndex--;
}
