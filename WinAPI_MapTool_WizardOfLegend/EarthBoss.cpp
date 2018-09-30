#include "stdafx.h"
#include "EarthBoss.h"


HRESULT EarthBoss::init()
{
	Actor::init();

	_img[WIZARD::IDLE] = IMAGEMANAGER->findImage("earthBoss_idle");
	_img[WIZARD::WALK] = IMAGEMANAGER->findImage("earthBoss_idle");
	_img[WIZARD::ATTACK] = IMAGEMANAGER->findImage("earthBoss_attack1");
	_img[WIZARD::ATTACK_DELAY] = IMAGEMANAGER->findImage("earthBoss_attackDelay");
	_img[WIZARD::DEAD] = IMAGEMANAGER->findImage("earthBoss_dead");
	_img[WIZARD::HIT] = IMAGEMANAGER->findImage("earthBoss_hit");
	_img[WIZARD::FALL] = _img[WIZARD::IDLE];

	_delay[WIZARD::IDLE] = 100;
	_delay[WIZARD::ATTACK_DELAY] = 20;
	_delay[WIZARD::ATTACK] = 5;
	_delay[WIZARD::HIT] = 5;
	_delay[WIZARD::FALL] = 100;
	_delay[WIZARD::DEAD] = 5;

	_index = _dir = _count = 0;
	_speed = 0;

	_state = WIZARD::IDLE;

	_shootingAngle = 0;

	_attack[0] = new StoneThrowAttack;
	_attack[0]->setLinkBulletList(BULLETMANAGER->getEnemyBullets());
	_attack[0]->setLinkPlayer(this);
	_attack[0]->setLinkPixelMap(_pixelMap);
	_attack[0]->setLinkEnemyManager(NULL);
	_attack[0]->setMotion(0, IMAGEMANAGER->findImage("earthBoss_attack1"));
	_attack[0]->init();
	_attack[0]->setFrameCount(15);
	_attack[0]->setAttackIndex(2);

	_attack[1] = new StoneAttack;
	_attack[1]->setLinkBulletList(BULLETMANAGER->getEnemyBullets());
	_attack[1]->setLinkPlayer(this);
	_attack[1]->setLinkPixelMap(_pixelMap);
	_attack[1]->setLinkEnemyManager(NULL);
	_attack[1]->setMotion(0, IMAGEMANAGER->findImage("earthBoss_attack2"));
	_attack[1]->setMotion(1, IMAGEMANAGER->findImage("earthBoss_attack2"));
	_attack[1]->init();
	_attack[1]->setFrameCount(15);
	_attack[1]->setAttackIndex(1);
	_attack[1]->setAttackDistance(125);
	_attack[1]->setSpeed(10);


	_attack[2] = new WaterThrowAttack;
	_attack[2]->setLinkBulletList(BULLETMANAGER->getEnemyBullets());
	_attack[2]->setLinkPlayer(this);
	_attack[2]->setLinkPixelMap(_pixelMap);
	_attack[2]->setLinkEnemyManager(NULL);
	_attack[2]->setMotion(0, IMAGEMANAGER->findImage("earthBoss_attack3"));
	_attack[2]->setMotion(1, IMAGEMANAGER->findImage("earthBoss_attack3"));
	_attack[2]->init();
	_attack[2]->setFrameCount(15);
	_attack[2]->setAttackIndex(2);




	_routingIndex = 0;
	_hp = 100;
	_delayCount = 0;
	_hitCount = 0;

	_z = 0;


	if (_hpBar == NULL)
	{
		_hpBar = new ProgressBar;
		_hpBar->init("bosshpBarFront_300x41", "bosshpBarBack_300x41", WINSIZEX/2 - 150, 50, 300, 41);
		_maxHp = 100;	// 맥스HP
		_hp = 100;	// 현재 에너지(이미지수정때문에29)
		_hpBar->setGauge(_hp, _maxHp);
	}

	_isActive = true;
	return S_OK;
}

void EarthBoss::release()
{
	_hpBar->release();

	for (int i = 0; i < EARTH_BOSS_ATTACK_MAX; ++i)
	{
		_attack[i]->release();
		SAFE_DELETE(_attack[i]);
	}
}

void EarthBoss::update()
{
	if (_state == WIZARD::FALL)
	{
		_z += 7;
		if (_count > FALL_COUNT)
		{
			_isActive = false;
		}
		return;
	}

	if (_state == WIZARD::DEAD)
	{
		_delayCount -= 1;
		if (_delayCount < 0)
		{
			_isActive = false;
			_delayCount = 0;
		}

		return;
	}

	if (_delayCount <= 0)
	{
		if (_state != WIZARD::ATTACK_DELAY)
		{
			if (_state != WIZARD::ATTACK)
			{
				changeState(WIZARD::ATTACK);
				settingAttack();
			}
			if (_state == WIZARD::ATTACK)
			{
				//if (_index == _img[_state]->getMaxFrameX() && _count % _delay[_state] == 0)
				if (_index == _attack[_currentAttack]->getAttackIndeX() && _count % _delay[_state] == 0)
				{
					attack();
				}
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

	move();

	if(_state == WIZARD::ATTACK)
		_attack[_currentAttack]->update();

	collide();

	_hpBar->update();
	_hpBar->setGauge(_hp, _maxHp);

	_moveBox = RectMakeCenter(_x, _y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(_x, _moveBox.top, WIZARD::HITBOX_WIDTH, WIZARD::HITBOX_HEIGHT);

	_hpBar->render();

	_hitCount -= 1;
	if (_hitCount < 0)
		_hitCount = 0;

	if (_x > CAM->getX() - 100 && _x < CAM->getX() + WINSIZEX + 100 &&
		_y > CAM->getY() - 100 && _y < CAM->getY() + WINSIZEY + 100)
	{
		RENDERMANAGER->addRender(_moveBox.bottom - _z, this);
	}
}

void EarthBoss::render()
{
	frameSetting();

	if (!_isActive) return;

	_img[_state]->frameRender(getMemDC(),
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() + _z - CAM->getY(), _index, _dir);
}

void EarthBoss::changeState(int state)
{
	if (_state == state)
		return;

	_state = state;
	_count = 0;
	_index = 0;

	switch (_state)
	{
	case WIZARD::ATTACK:
		_speed = WIZARD::ATTACK_SPEED;
		break;
	case WIZARD::DASH:
		_speed = WIZARD::DASH_SPEED;
		break;
	case WIZARD::HIT:
		_speed = WIZARD::HIT_SPEED;
		break;
	default:
		_speed = 0;
		break;
	}
}

void EarthBoss::damaged(Actor * e)
{
	if (_state == WIZARD::DEAD || _state == WIZARD::HIT || _state == WIZARD::FALL)
		return;

	if (_state == WIZARD::ATTACK)
	{
		if (_hitCount > 0)
			return;

		_hitCount = e->getPower() * 2;
		_hp -= e->getPower();
		if (_hp <= 0)
		{
			changeState(WIZARD::DEAD);
			_hp = 0;
			_delayCount = 50;
		}
		return;
	}

	if (_hitCount > 0)
		return;

	_angle = getAnglef(e->getX(), e->getY(), _x, _y);
	//_angle = _angle + PI;
	if (e->getX() > _x)
		_dir = WIZARD::RIGHT;
	else
		_dir = WIZARD::LEFT;

	_hitCount = e->getPower();
	_hp -= e->getPower();
	if (_hp <= 0)
		changeState(WIZARD::DEAD);
	else
		changeState(WIZARD::HIT);

	_delayCount = 50;
}

void EarthBoss::settingDir()
{
	if (_state == WIZARD::IDLE)
		return;

	float angle = _angle * 180 / PI;

	if (angle > 45 && angle < 135)
	{
		_dir = WIZARD::UP;
	}
	else if (angle >= 135 && angle <= 225)
	{
		_dir = WIZARD::LEFT;
	}
	else if (angle > 225 && angle < 315)
	{
		_dir = WIZARD::DOWN;
	}
	else
	{
		_dir = WIZARD::RIGHT;
	}
}


void EarthBoss::frameSetting()
{
	if (_state == WIZARD::DEAD)
	{
		return;
	}

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
				changeState(WIZARD::ATTACK_DELAY);
				_delayCount = 50;
			}
			else if (_state == WIZARD::DEAD)
			{
				_isActive = false;
			}
			else if (_state == WIZARD::ATTACK_DELAY)
			{
				changeState(WIZARD::IDLE);
			}

		}
	}
}

void EarthBoss::settingAttack()
{
	_currentAttack = RND->getInt(EARTH_BOSS_ATTACK_MAX);

	_angle = _shootingAngle = getAnglef(_x, _y, (*_player)->getX(), (*_player)->getY());

	_img[WIZARD::ATTACK] = _attack[_currentAttack]->getImage();
	_delay[WIZARD::ATTACK] = _attack[_currentAttack]->getFrameCount();

	switch (_img[WIZARD::ATTACK]->getMaxFrameY())
	{
	case 0:
		_dir = 0;
		break;
	case 1:
		if (_x < (*_player)->getX())
			_dir = ENEMY::RIGHT;
		else
			_dir = ENEMY::LEFT;
		break;

	case 3:
		settingDir();
		break;
	}
}

void EarthBoss::attack()
{
	_speed = _attack[_currentAttack]->getSpeed();
	_attack[_currentAttack]->attack(_x, _moveBox.bottom - _img[_state]->getFrameHeight() / 2, _shootingAngle);
}

void EarthBoss::move()
{
	_x += cos(_angle) *_speed;
	_y += -sin(_angle) * _speed;

	if (_routingIndex > 0 && ((int)_x / TILESIZE) == _routing[_routingIndex].x && ((int)_y / TILESIZE) == _routing[_routingIndex].y)
		_routingIndex--;
}

void EarthBoss::freeze(float x, float y)
{
	_x = x; _y = y;
	_state = WIZARD::HIT;
	_delayCount = 2;
	_speed = 0;
}
