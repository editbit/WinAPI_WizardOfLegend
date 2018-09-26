#include "stdafx.h"
#include "Enemy.h"


HRESULT Enemy::init()
{
	_routingIndex = 0;
	_hp = 100;
	_hitCount = 0;
	_delayCount = 0;

	_z = 0;
	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
}

void Enemy::render()
{
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		for (int i = 0; i < _routing.size(); ++i)
		{
			Rectangle(getMemDC(), RectMake(_routing[i].x * TILESIZE, _routing[i].y * TILESIZE, TILESIZE, TILESIZE), CAM->getX(), CAM->getY());
		}
	}
	Rectangle(getMemDC(), _moveBox, CAM->getX(), CAM->getY());
}

void Enemy::damaged(Actor * e)
{
	if (_state == ENEMY::DEAD || _state == ENEMY::HIT || _state == ENEMY::FALL)
		return;

	_angle = getAnglef(e->getX(), e->getY(), _x, _y);
	//_angle = _angle + PI;
	if (e->getX() > _x)
		_dir = ENEMY::RIGHT;
	else
		_dir = ENEMY::LEFT;

	_hp -= e->getPower();
	if (_hp <= 0)
		changeState(ENEMY::DEAD);
	else
	{
		changeState(ENEMY::HIT);
		_delayCount = 50;
	}
}

void Enemy::collide()
{
	collisionPixel();
}

void Enemy::collisionPixel()
{
	int r, g, b;
	COLORREF color;

	// move right

	//if (_state != ENEMY::DASH)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, _y);
		if (color == RGB(0, 0, 255))
		{
			changeState(ENEMY::FALL);

			return;
		}
	}


	for (int i = _x + ENEMY::MOVEBOX_WIDTH / 2 - _speed; i <= _x + ENEMY::MOVEBOX_WIDTH / 2; ++i)
	{
		color = GetPixel(_pixelMap->getMemDC(), i, _y);

		if (!checkMovable(color))
		{
			_x = i - ENEMY::MOVEBOX_WIDTH / 2;
		}
	}

	// move left
	for (int i = _x - ENEMY::MOVEBOX_WIDTH / 2 + _speed; i >= _x - ENEMY::MOVEBOX_WIDTH / 2; --i)
	{
		color = GetPixel(_pixelMap->getMemDC(), i, _y);

		if (!checkMovable(color))
		{
			_x = i + ENEMY::MOVEBOX_WIDTH / 2;
		}
	}


	// move up
	for (int i = _y - ENEMY::MOVEBOX_HEIGHT / 2 + _speed; i >= _y - ENEMY::MOVEBOX_HEIGHT / 2; --i)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, i);

		if (!checkMovable(color))
		{
			_y = i + ENEMY::MOVEBOX_HEIGHT / 2;
		}
	}

	// move down
	for (int i = _y + ENEMY::MOVEBOX_HEIGHT / 2 - _speed; i <= _y + ENEMY::MOVEBOX_HEIGHT / 2; ++i)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, i);

		if (!checkMovable(color))
		{
			_y = i - ENEMY::MOVEBOX_HEIGHT / 2;
		}
	}
}
void Enemy::moveToPlayer()
{
	int x = _x / TILESIZE, y = _y / TILESIZE;
	if(_routing.size() > 0)
	{
		changeState(ENEMY::WALK);
		
		if (_routingIndex < 0)
		{
			changeState(ENEMY::IDLE);
			return;
		}

		else if (_routing[_routingIndex].x < x)
		{
			_dir = ENEMY::LEFT;
			if (_routing[_routingIndex].y < y)
			{
				_angle = 135 * PI / 180;
			}
			else if (_routing[_routingIndex].y > y)
			{
				_angle = 225 * PI / 180;
			}
			else
			{
				_angle = 180 * PI / 180;
			}

		}
		else if (_routing[_routingIndex].x > x)
		{
			_dir = ENEMY::RIGHT;
			if (_routing[_routingIndex].y < y)
			{
				_angle = 45 * PI / 180;
			}
			else if (_routing[_routingIndex].y > y)
			{
				_angle = 315 * PI / 180;
			}
			else
			{
				_angle = 0;
			}
		}
		else
		{
			if (_routing[_routingIndex].y < y)
			{
				_angle = 90 * PI / 180;
			}
			else if (_routing[_routingIndex].y > y)
			{
				_angle = 270 * PI / 180;
			}
			else
			{
				//_angle = 0;
				//_state = ENEMY::IDLE;
			}
		}
	}
	else
	{
		//if (_routing[_routingIndex].x == x && _routing[_routingIndex].y == y)
		changeState(ENEMY::IDLE);
	}
}

void Enemy::changeState(int state)
{
	if (_state == state)
		return;

	_state = state;
	_count = 0;
	_index = 0;

	switch (_state)
	{
	case ENEMY::WALK:
		_speed = ENEMY::WALK_SPEED;
		break;
	case ENEMY::ATTACK:
		_speed = ENEMY::ATTACK_SPEED;
		break;
	case ENEMY::DASH:
		_speed = ENEMY::DASH_SPEED;
		break;
	case ENEMY::HIT:
		_speed = ENEMY::HIT_SPEED;
		break;
	default:
		_speed = 0;
		break;
	}
}
