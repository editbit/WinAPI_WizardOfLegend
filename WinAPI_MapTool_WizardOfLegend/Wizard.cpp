#include "stdafx.h"
#include "Wizard.h"
#include "Stuff.h"

HRESULT Wizard::init()
{
	_speed = WIZARD::WALK_SPEED;

	_oldX = _x = 10 * TILESIZE;
	_oldY = _y = 27 * TILESIZE;

	_state = WIZARD::IDLE;
	_dir = WIZARD::DOWN;
	_angle = 3 * PI / 2;

	_img[WIZARD::IDLE] = IMAGEMANAGER->findImage("player_idle");
	_img[WIZARD::WALK] = IMAGEMANAGER->findImage("player_walk");
	_img[WIZARD::RUN] = _img[WIZARD::WALK];
	_img[WIZARD::DASH] = IMAGEMANAGER->findImage("player_dash");
	_img[WIZARD::ATTACK] = IMAGEMANAGER->findImage("player_attack1");
	_img[WIZARD::FALL] = IMAGEMANAGER->findImage("player_fall");
	_img[WIZARD::HIT] = IMAGEMANAGER->findImage("player_hit");

	_delay[WIZARD::IDLE] = 5;
	_delay[WIZARD::WALK] = 5;
	_delay[WIZARD::RUN] = 5;
	_delay[WIZARD::DASH] = 5;
	_delay[WIZARD::ATTACK] = 3;
	_delay[WIZARD::FALL] = 5;
	_delay[WIZARD::HIT] = 10;

	_moveBox = RectMakeCenter(_x, _y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_attackBox = _moveBox;

	_attackAngle = 0;

	_inven = new Inventory;
	_inven->setLinkEnemyManager(_enemyManager);
	_inven->setLinkPixelMap(_pixelMap);
	_inven->setLinkPlayer(this);
	_inven->init();
/*
	_iceDash = new IceDash;
	_iceDash->init();

	_fireDash = new FireDash;
	_fireDash->init();
	_fireDash->setLinkPlayer(this);
	_fireDash->setLinkPixelMap(_pixelMap);*/

	//_currentDash = _iceDash;
	_currentDash = (Dash*)_inven->getCurrentDash();
	_attack = _inven->getBasicAttack();
	return S_OK;
}

void Wizard::release()
{
	_inven->release();
	SAFE_DELETE(_inven);
}

void Wizard::update()
{

	if (_state != WIZARD::HIT)
	{
		_attackAngle = getAnglef(_x, _y, _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());

		if (_state != WIZARD::ATTACK)
		{
			_attackIndex = -1;
		}

		if (_state != WIZARD::FALL)
		{
			if (_state != WIZARD::DASH && (_state != WIZARD::ATTACK || _index >= _attack->getChangableIndex() ) )
			{

				if (_inven->getIsActive())
				{
					_inven->update();
					if (!_inven->getIsActive())
					{
						_currentDash = (Dash*)_inven->getCurrentDash();
						_attack = _inven->getBasicAttack();
					}
				}
				else
					inputProcess();
			}
		}
		else
		{
			_z += 7;
			if (_count > FALL_COUNT)
			{
				_x = _returnPoint.x;
				_y = _returnPoint.y;
				changeState(WIZARD::IDLE);
				_z = 0;

				EFFECTMANAGER->play("파란포탈", _x, _moveBox.bottom - _img[_state]->getFrameHeight()/2, 50);
				EFFECTMANAGER->play("파란포탈_가장자리", _x, _moveBox.bottom - _img[_state]->getFrameHeight() / 2);
			}
		}
	}
	else
	{
		_speed -= 1;
		if (_speed <= 0) _speed = 0;
	}

	move();

	_moveBox = RectMakeCenter(_x, _y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(_x, _y - WIZARD::MOVEBOX_HEIGHT / 2, WIZARD::HITBOX_WIDTH, WIZARD::HITBOX_HEIGHT);

	if (_currentDash->getIsActive())
	{
		_currentDash->setPosition(_x, _y);
		_currentDash->update();
	}

	collide();
	frameSetting();
}

void Wizard::render()
{
	_img[_state]->frameRender(getMemDC(), 
		_x - _img[_state]->getFrameWidth() / 2 - CAM->getX(),
		_moveBox.bottom - _img[_state]->getFrameHeight() - CAM->getY() + _z,
		_index, _dir);

	if (KEYMANAGER->isToggleKey('9'))
	{
		Rectangle(getMemDC(), _moveBox, CAM->getX(), CAM->getY());
	}

	_inven->renderEquipSkill();

	if (_inven->getIsActive())
		_inven->render();
}

void Wizard::inputProcess()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		changeState(WIZARD::IDLE);
		_inven->setIsActive(!_inven->getIsActive());
		return;
	}

	_axisX = NONE; _axisY = NONE;
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_axisY = UP;

		if (_state != WIZARD::RUN)
			changeState(WIZARD::WALK);
		//_dir = WIZARD::UP;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_axisY = DOWN;
		if (_state != WIZARD::RUN)
			changeState(WIZARD::WALK);
		//_dir = WIZARD::DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_axisX = LEFT;
		if (_state != WIZARD::RUN)
			changeState(WIZARD::WALK);
		//dir = WIZARD::LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_axisX = RIGHT;
		if (_state != WIZARD::RUN)
			changeState(WIZARD::WALK);
		//_dir = WIZARD::RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_state != WIZARD::ATTACK)
		{
			changeState(WIZARD::ATTACK);
			_img[WIZARD::ATTACK] = _attack->attack(_x, _moveBox.bottom - _img[WIZARD::ATTACK]->getFrameHeight()/2, _attackAngle);
			_delay[WIZARD::ATTACK] = _attack->getFrameCount();
		}
		else
		{
			_img[WIZARD::ATTACK] = _attack->attack(_x, _moveBox.bottom - _img[WIZARD::ATTACK]->getFrameHeight() / 2, _attackAngle);
			_delay[WIZARD::ATTACK] = _attack->getFrameCount();
			_count = _index = 0;
		}
	}

	if (_state == WIZARD::ATTACK)
		_angle = _attackAngle;
	else
		settingAngle();


	settingDir();




	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_state != WIZARD::DASH)
		{
			//_returnPoint = { _x, _y };
			settingReturnPoint();
			/*if(!_dummy->getIsActive())
				_dummy->generate(_x, _y, _index, _dir);*/
			_currentDash->executeDash(_x, _y);
		}
		changeState(WIZARD::DASH);
	}
}


void Wizard::damaged(Actor * e)
{
	if (_state == WIZARD::HIT ||
		_state == WIZARD::FALL)
		return;


	changeState(WIZARD::HIT);
	_angle = getAnglef(_x, _y, e->getX(), e->getY());
	settingDir();
	_angle = _angle + PI;

	//_returnPoint = { _x, _y };
	settingReturnPoint();
}

void Wizard::attackStuff()
{
	int startX = _attackBox.left / TILESIZE, endX = _attackBox.right / TILESIZE;
	int startY = _attackBox.top / TILESIZE, endY = _attackBox.bottom / TILESIZE;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			if (tiles[i * TILEX + j].objType == OBJECT_TRAP)
			{
				if (tiles[i * TILEX + j].obj->damaged(this, _enemyManager->getEnemys()))
				{
					tiles[i * TILEX + j].objType = OBJECT_NONE;
				}
			}
		}
	}
}

void Wizard::attack()
{
	vector<Enemy *>& enemys = _enemyManager->getEnemys();
	
	if (enemys.size() <= 0) return;
	
	_attackBox = RectMakeCenter(_x + cos(_attackAngle) * 100, _y - sin(_attackAngle) * 100, 100, 100);
	
	RECT hitbox, temp;
	for (int i = 0; i < enemys.size(); ++i)
	{
		if (!enemys[i]->getIsActive()) continue;
	
		hitbox = enemys[i]->getHitBox();
	
		if (IntersectRect(&temp, &_attackBox, &hitbox))
		{
			enemys[i]->damaged(this);
		}
	}
	
	attackStuff();
}

void Wizard::move()
{
	if (_state == WIZARD::IDLE)
		return;

	_oldX = _x; _oldY = _y; _oldZ = _z;


	if (_state == WIZARD::WALK)
	{
		if (_count >= WIZARD::RUN_COUNT)
		{
			changeState(WIZARD::RUN);
		}
	}


	Actor::move();
	
}

void Wizard::collide()
{
	collidePixelMap();
	collideTileObject();
}

void Wizard::collideTileObject()
{
	RECT rc;
	int index = (int)_x/TILESIZE + (int)_y/TILESIZE * TILEX;
	if (IntersectRect(&rc, &tiles[index].rc, &_moveBox))
	{
		if ((attribute[index] & ATTR_UNMOVAL) == ATTR_UNMOVAL)
		{
			if (tiles[index].objType == OBJECT_BREAKABLE)
			{
				tiles[index].objType = OBJECT_NONE;
				attribute[index] = attribute[index] ^ ATTR_UNMOVAL;
			}
			else if (tiles[index].objType == OBJECT_TRAP)
			{
				if (!tiles[index].obj->checkAttack())
					return;

				if (tiles[index].obj->collide(this, _enemyManager->getEnemys()))
				{
					tiles[index].objType = OBJECT_NONE;
					attribute[index] = attribute[index] ^ ATTR_UNMOVAL;
				}
			}
		}
	}

}


void Wizard::collidePixelMap()
{
	int r, g, b;
	COLORREF color;

	// move right

	if (_state != WIZARD::DASH)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, _y);
		if (color == RGB(0, 0, 255))
		{
			changeState(WIZARD::FALL);

			return;
		}
	}


	for (int i = _x + WIZARD::MOVEBOX_WIDTH / 2 - _speed; i <= _x + WIZARD::MOVEBOX_WIDTH / 2; ++i)
	{
		color = GetPixel(_pixelMap->getMemDC(), i, _y);

		if (!checkMovable(color))
		{
			_x = i - WIZARD::MOVEBOX_WIDTH / 2;
			break;
		}
	}

	// move left
	for (int i = _x - WIZARD::MOVEBOX_WIDTH / 2 + _speed; i >= _x - WIZARD::MOVEBOX_WIDTH / 2; --i)
	{
		color = GetPixel(_pixelMap->getMemDC(), i, _y);

		if (!checkMovable(color))
		{
			_x = i + WIZARD::MOVEBOX_WIDTH / 2;
			break;
		}
	}


	// move up
	for (int i = _y - WIZARD::MOVEBOX_HEIGHT / 2 + _speed; i >= _y - WIZARD::MOVEBOX_HEIGHT / 2; --i)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, i);

		if (!checkMovable(color))
		{
			_y = i + WIZARD::MOVEBOX_HEIGHT / 2;
			break;
		}
	}

	// move down
	for (int i = _y + WIZARD::MOVEBOX_HEIGHT / 2 - _speed; i <= _y + WIZARD::MOVEBOX_HEIGHT / 2; ++i)
	{
		color = GetPixel(_pixelMap->getMemDC(), _x, i);

		if (!checkMovable(color))
		{
			_y = i - WIZARD::MOVEBOX_HEIGHT / 2;
			break;
		}
	}

	_moveBox = RectMakeCenter(_x, _y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(_x, _y - WIZARD::MOVEBOX_HEIGHT / 2, WIZARD::HITBOX_WIDTH, WIZARD::HITBOX_HEIGHT);


}


void Wizard::frameSetting()
{
	_count = (_count + 1);
	if (_count % _delay[_state] == 0)
	{
		
		if (_state == WIZARD::DASH)
		{
			if (_count >= WIZARD::DASH_COUNT)
			
			{
				_index = (_index + 1);
				_speed = WIZARD::DASH_STOP_SPEED;
			}
		}
		else
		{
			_index = (_index + 1);
		}
		
		if (_index > (_img[_state]->getMaxFrameX()))
		{
			_index = 0;
			if (_state == WIZARD::ATTACK)
			{
				changeState(WIZARD::IDLE);
			}
			else if (_state == WIZARD::DASH || _state == WIZARD::HIT)
			{
				changeState(WIZARD::IDLE);
			}
		}
	}

}

void Wizard::changeState(int state)
{
	if (_state == state)
		return;

	_state = state;
	_count = 0;
	_index = 0;

	switch (_state)
	{
	case WIZARD::WALK:
		_speed = WIZARD::WALK_SPEED;
		break;
	case WIZARD::RUN:
		_speed = WIZARD::RUN_SPEED;
		break;
	case WIZARD::ATTACK:
		_speed = WIZARD::ATTACK_SPEED;
		break;
	case WIZARD::DASH:
		_speed = WIZARD::DASH_SPEED;
		break;
	case WIZARD::HIT:
		_speed = 10;
		break;
	default:
		_speed = 0;
		break;
	}
}



void Wizard::settingReturnPoint()
{
	RECT t = tiles[((int)_y / TILESIZE)*TILEX + ((int)_x)/TILESIZE].rc;

	_returnPoint = {(t.left + t.right) * 0.5f, (t.top + t.bottom) * 0.5f};
}

void Wizard::settingDir()
{
	if (_state == WIZARD::IDLE)
		return;

	float angle = _angle * 180 / PI;

	if (angle > 45 && angle < 135)
		_dir = WIZARD::UP;
	else if (angle >= 135 && angle <= 225)
		_dir = WIZARD::LEFT;
	else if (angle > 225 && angle < 315)
		_dir = WIZARD::DOWN;
	else
		_dir = WIZARD::RIGHT;
}

void Wizard::settingAngle()
{


	switch (_axisX)
	{
	case RIGHT:

		if (_axisY == UP)
		{
			_angle = 45;
		}
		else if (_axisY == DOWN)
		{
			_angle = 315;
		}
		else
		{
			_angle = 0;
		}

		break;

	case LEFT:
		if (_axisY == UP)
		{
			_angle = 135;
		}
		else if (_axisY == DOWN)
		{
			_angle = 225;
		}
		else
		{
			_angle = 180;
		}
		break;

	case NONE:
		if (_axisY == UP)
		{
			_angle = 90;
		}
		else if (_axisY == DOWN)
		{
			_angle = 270;
		}
		break;
	}

	if (_axisX == NONE && _axisY == NONE)
	{
		if ((_state == WIZARD::WALK || _state == WIZARD::RUN))
		{
			changeState(WIZARD::IDLE);
			return;
		}
	}
	else
	{
		_angle = _angle * PI / 180;
	}
}
