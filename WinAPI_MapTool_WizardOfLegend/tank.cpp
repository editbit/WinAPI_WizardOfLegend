#include "stdafx.h"
#include "tank.h"
#include "tileMap.h"

HRESULT tank::init(void)
{
	//탱크 프레임 이미지
	//_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->findImage("player_walk");

	//탱크방향 초기화
	_direction = TANKDIRECTION_UP;

	//탱크 속도
	_speed = 5.0f;

	_curFrameX = 0;

	_count = _index = 0;
	return S_OK;
}


void tank::release(void)
{
}

void tank::update(void)
{
	
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_direction != TANKDIRECTION_UP)
			_curFrameX = 0;

		_direction = TANKDIRECTION_UP;
		//tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_direction != TANKDIRECTION_DOWN)
			_curFrameX = 0;

		_direction = TANKDIRECTION_DOWN;
		//tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_direction != TANKDIRECTION_LEFT)
			_curFrameX = 0;

		_direction = TANKDIRECTION_LEFT;
		//tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if(_direction != TANKDIRECTION_RIGHT)
			_curFrameX = 0;

		_direction = TANKDIRECTION_RIGHT;
		//tankMove();
	}
	tankMove();
}

void tank::render(void)
{
	_count = (_count + 1) % 10;
	if(_count == 0)
		_curFrameX = (_curFrameX + 1) % (_image->getMaxFrameX() + 1);

	//_image->frameRender(getMemDC(), _rc.left - CAM->getX(), _rc.top - CAM->getY(), _curFrameX, _curFrameY);
	_image->frameRender(getMemDC(), _x - _image->getFrameWidth()/2 - CAM->getX(), _y - _image->getFrameHeight() / 2 - CAM->getY(), _curFrameX, _direction);

	if (KEYMANAGER->isToggleKey('9'))
	{
		for (int i = 0; i < collisionRange; ++i)
		{
			Rectangle(getMemDC(), _tankMap->getTiles()[tileIndex[i]].rc, CAM->getX(), CAM->getY());
		}
		
		Rectangle(getMemDC(), _rc, CAM->getX(), CAM->getY());

		char str[50];
		sprintf_s(str, "%d %d", _count, _curFrameX);
		TextOut(UIMANAGER->getUIDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
	}
}

void tank::tankMove(void)
{
	//가상으로 움직일 렉트
	RECT rcCollision;
	//rcCollision = _rc;

	//검사할 타일 인덱스(최소 2개 필요함)
	

	//현재 탱크가 밟고 있는 타일
	int tileX, tileY;

	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		_x -= _speed;
		//rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		//rcCollision = RectMakeCenter(_x, _y, 50, 100);
		rcCollision = RectMakeCenter(_x, _y + 36, 50, 50);
		break;
	case TANKDIRECTION_RIGHT:
		_x += _speed;
		//rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		//rcCollision = RectMakeCenter(_x, _y, 50, 100);
		rcCollision = RectMakeCenter(_x, _y + 36, 50, 50);
		break;
	case TANKDIRECTION_UP:
		_y -= _speed;
		//rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		//rcCollision = RectMakeCenter(_x, _y, 50, 100);
		rcCollision = RectMakeCenter(_x, _y + 36, 50, 50);
		break;
	case TANKDIRECTION_DOWN:
		_y += _speed;
		//rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		//rcCollision = RectMakeCenter(_x, _y, 50, 100);
		rcCollision = RectMakeCenter(_x, _y + 36, 50, 50);
		break;
	}

	//충돌렉트 크기를 타일크기보다 더 작게 깍아준다
	//32 * 32 때문에 0.1오차라도 있으면 타일 사이를 빠져나갈 수가 없다
	rcCollision.left += 1;
	rcCollision.right -= 1;
	rcCollision.top += 1;
	rcCollision.bottom -= 1;
	
	//탱크의 인덱스를 확인할 수 있다
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//타일맵 검사하기(상하좌우 각각 2개씩)
	//자기위치를 기반으로 타일을 전부검색하면 프레임이 떨어질 수 있으니
	//상하좌우 각각 2개씩만 검사를 하자
	switch (_direction)
	{
	case TANKDIRECTION_LEFT:

		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.top / TILESIZE;

		//왼쪽, 왼쪽아래
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;/*
		tileIndex[2] = tileX + (tileY + 2) * TILEX;
		tileIndex[3] = tileX + (tileY + 3) * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_RIGHT:
		tileX = rcCollision.right / TILESIZE;
		tileY = rcCollision.top / TILESIZE;
		//오른쪽, 오른쪽아래
		tileIndex[0] = (tileX) + tileY * TILEX;
		tileIndex[1] = (tileX) + (tileY + 1) * TILEX;/*
		tileIndex[2] = (tileX) + (tileY + 2) * TILEX;
		tileIndex[3] = (tileX)+(tileY + 3) * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_UP:
		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.top / TILESIZE;
		//위, 오른쪽위
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;/*
		tileIndex[2] = (tileX + 2) + tileY * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_DOWN:
		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.bottom / TILESIZE;
		//아래, 오른쪽아래
		tileIndex[0] = tileX + (tileY) * TILEX;
		tileIndex[1] = (tileX + 1) + (tileY) * TILEX;/*
		tileIndex[2] = (tileX + 2) + (tileY)* TILEX;*/
		collisionRange = 2;
		break;
	}

	for (int i = 0; i < collisionRange; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{
			if((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVAL) == ATTR_UNMOVAL)
			{
				switch (_direction)
				{
				case TANKDIRECTION_LEFT:
					
					_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;
					_rc.right = _rc.left + 50;
					_x = _rc.left + (_rc.right - _rc.left) / 2;

					//rcCollision = RectMakeCenter(_x, _y, 50, 100);
					break;
				case TANKDIRECTION_RIGHT:
					

					_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
					_rc.left = _rc.right - 50;
					_x = _rc.left + (_rc.right - _rc.left) / 2;
					break;
				case TANKDIRECTION_UP:
					
					_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
					_rc.bottom = _rc.top + 50;
					//_y = _rc.top + (_rc.bottom - _rc.top) / 2;
					_y = _rc.top -8;
					break;
				case TANKDIRECTION_DOWN:
					
					_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
					_rc.top = _rc.bottom - 50;
					_y = _rc.top -14;
					break;
				}
			}
			else if(_tankMap->getTiles()[tileIndex[i]].objType == OBJECT_COIN)
			{
				if((rc.bottom - rc.top) * (rc.right - rc.left) > 500)
					_tankMap->getTiles()[tileIndex[i]].objType = OBJECT_NONE;
			}
			else if (_tankMap->getTiles()[tileIndex[i]].objType == OBJECT_ITEM)
			{
				_tankMap->getTiles()[tileIndex[i]].objType = OBJECT_NONE;
			}
		}
	}

	rcCollision = RectMakeCenter(_x, _y + 36, 50, 50);
	_rc = rcCollision;


}

void tank::setTankPosition(int index)
{
	_rc = _tankMap->getTiles()[index].rc;
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}