#include "stdafx.h"
#include "actor.h"

void Actor::move()
{
	_x += cos(_angle)*_speed;
	_y += -sin(_angle)*_speed;
}

void Actor::throwed(float speed, float angle)
{
	_speed = speed;
	_angle = angle;
	_gravity = 0;
}

void Actor::changeState(int state)
{
	if (_state == state)
		return;

	_state = state;
	_count = 0;
	_index = 0;
}

bool Actor::checkMovable(COLORREF color)
{
	if (color == RGB(255, 0, 0))
		return false;

	return true;
}

void Actor::setLinkTileMap(tileMap * tile)
{
	_tileMap = tile;
	tiles = _tileMap->getTiles();		//타일
	attribute = _tileMap->getAttribute();	//속성
}

bool Actor::collide(Actor * a)
{
	RECT temp;

	return IntersectRect(&temp, &a->getHitBox(), &_hitBox);
}

HRESULT Actor::init()
{
	_x = _y = 0;
	return S_OK;
}

void Actor::update()
{
}

void Actor::render()
{
}

void Actor::release()
{
}

Actor::Actor()
{
	_x = _y = _z = _gravity = _speed = _power = _angle = 0;
	_hp = _maxHp = _state = _dir = _count = _index = 0;
	_hitBox = { 0, 0, 0, 0 };
	_isActive = true;
}

