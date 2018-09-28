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


void Actor::rewind()
{
	_rewindIndex--;
	if (_rewindIndex < 0)
		_rewindIndex = REWIND_SIZE - 1;

	if (_rewindIndex == _rewindStartIndex)
		_isRewind = false;

	_state = _preState[_rewindIndex].getState();
	_x = _preState[_rewindIndex].getX();
	_y = _preState[_rewindIndex].getY();
	_z = _preState[_rewindIndex].getZ();
	_hp = _preState[_rewindIndex].getHp();
	_dir = _preState[_rewindIndex].getDir();
	_index = _preState[_rewindIndex].getIndex();
	_count = _preState[_rewindIndex].getCount();
	_angle = _preState[_rewindIndex].getAngle();
	_moveBox = _preState[_rewindIndex].getMoveBox();
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
	: _preState(NULL)
{
	_x = _y = _z = _gravity = _speed = _power = _angle = 0;
	_hp = _maxHp = _state = _dir = _count = _index = 0;
	_hitBox = { 0, 0, 0, 0 };
	_isActive = true;
}

Actor::~Actor()
{
}

void Actor::rewindInit()
{
	_preState = new Actor[REWIND_SIZE];
	_rewindIndex = _rewindStartIndex = 0;
	_isRewind = false;
}
void Actor::rewindRelease()
{
	SAFE_DELETE_ARRAY(_preState);
}
