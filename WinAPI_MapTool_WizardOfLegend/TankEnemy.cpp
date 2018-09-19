#include "stdafx.h"
#include "TankEnemy.h"
#include "tileMap.h"

HRESULT TankEnemy::init(void)
{
	//탱크 프레임 이미지
	//_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->findImage("enemy_walk");

	//탱크방향 초기화
	_direction = UP;

	//탱크 속도
	_speed = 5.0f;

	_curFrameX = _count = _curFrameY = 0;
	_isTrace = false;

	return S_OK;
}

void TankEnemy::release(void)
{
}

void TankEnemy::update(void)
{
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	_direction = LEFT;
	//	//tankMove();
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	_direction = RIGHT;
	//	//tankMove();
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	_direction = UP;
	//	//tankMove();
	//}
	//else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	_direction = DOWN;
	//	//tankMove();
	//}

	enemyMove();
}

void TankEnemy::render(void)
{
	_count = (_count + 1) % 5;
	if (_count == 0)
		_curFrameX = (_curFrameX + 1) % (_image->getMaxFrameX() + 1);

	_image->frameRender(getMemDC(), _x - _image->getFrameWidth()/2 - CAM->getX(), _rc.bottom - _image->getFrameHeight() - CAM->getY(), _curFrameX, _curFrameY);

	if (KEYMANAGER->isToggleKey('9'))
	{
		//Rectangle(getMemDC(), _tankMap->getTiles()[tileIndex[0]].rc, CAM->getX(), CAM->getY());
		//Rectangle(getMemDC(), _tankMap->getTiles()[tileIndex[1]].rc, CAM->getX(), CAM->getY());
		Rectangle(getMemDC(), _rc, CAM->getX(), CAM->getY());
	}
}

void TankEnemy::enemyMove(void)
{
	//가상으로 움직일 렉트
	RECT rcCollision;
	//rcCollision = _rc;

	//검사할 타일 인덱스(최소 2개 필요함)


	//현재 탱크가 밟고 있는 타일
	int tileX, tileY;

	switch (_direction)
	{
	case LEFT:
		_curFrameY = 1;
		_x -= _speed;
		rcCollision = RectMakeCenter(_x, _y, SAMPLETILESIZE, SAMPLETILESIZE);
		break;
	case RIGHT:
		_curFrameY = 0;
		_x += _speed;
		rcCollision = RectMakeCenter(_x, _y, SAMPLETILESIZE, SAMPLETILESIZE);
		break;
	case UP:
		//_curFrameY = 0;
		_y -= _speed;
		rcCollision = RectMakeCenter(_x, _y, SAMPLETILESIZE, SAMPLETILESIZE);
		break;
	case DOWN:
		//_curFrameY = 1;
		_y += _speed;
		rcCollision = RectMakeCenter(_x, _y, SAMPLETILESIZE, SAMPLETILESIZE);
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
	case LEFT:
		//왼쪽, 왼쪽아래
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
	case RIGHT:
		//오른쪽, 오른쪽아래
		tileIndex[0] = (tileX + 1) + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + (tileY + 1) * TILEX;
		break;
	case UP:
		//위, 오른쪽위
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
		break;
	case DOWN:
		//아래, 오른쪽아래
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = (tileX + 1) + (tileY + 1) * TILEX;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{
			if ((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVAL) == ATTR_UNMOVAL)
			{
				switch (_direction)
				{
				case LEFT:
					if (rc.bottom - rc.top < 30)
					{
						if (rcCollision.top > _tankMap->getTiles()[tileIndex[i]].rc.top)
						{
							_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
							_rc.bottom = _rc.top + TILESIZE;
							_y = _rc.top + (_rc.bottom - _rc.top) / 2;
							break;
						}
						else
						{
							_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
							_rc.top = _rc.bottom - TILESIZE;
							_y = _rc.top + (_rc.bottom - _rc.top) / 2;
							break;
						}
					}

					_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;
					_rc.right = _rc.left + TILESIZE;
					_x = _rc.left + (_rc.right - _rc.left) / 2;

					//_direction = (RND->getInt(2) != 0)?DOWN : UP;
					break;
				case RIGHT:
					if (rc.bottom - rc.top < 30)
					{
						if (rcCollision.top > _tankMap->getTiles()[tileIndex[i]].rc.top)
						{
							_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
							_rc.bottom = _rc.top + TILESIZE;
							_y = _rc.top + (_rc.bottom - _rc.top) / 2;
							break;
						}
						else
						{
							_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
							_rc.top = _rc.bottom - TILESIZE;
							_y = _rc.top + (_rc.bottom - _rc.top) / 2;
							break;
						}
					}

					_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
					_rc.left = _rc.right - TILESIZE;
					_x = _rc.left + (_rc.right - _rc.left) / 2;

					//_direction = (RND->getInt(2) != 0) ? DOWN : UP;
					break;
				case UP:
					if (rc.right - rc.left < 30)
					{
						if (rcCollision.left > _tankMap->getTiles()[tileIndex[i]].rc.left)
						{
							_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;
							_rc.right = _rc.left + TILESIZE;
							_x = _rc.left + (_rc.right - _rc.left) / 2;
							break;
						}
						else
						{
							_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
							_rc.left = _rc.right - TILESIZE;
							_x = _rc.left + (_rc.right - _rc.left) / 2;
							break;
						}

					}

					_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
					_rc.bottom = _rc.top + TILESIZE;
					_y = _rc.top + (_rc.bottom - _rc.top) / 2;

					//_direction = (RND->getInt(2) != 0) ? LEFT : RIGHT;
					break;
				case DOWN:
					if (rc.right - rc.left < 30)
					{
						if (rcCollision.left > _tankMap->getTiles()[tileIndex[i]].rc.left)
						{
							_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;
							_rc.right = _rc.left + TILESIZE;
							_x = _rc.left + (_rc.right - _rc.left) / 2;
							break;
						}
						else
						{
							_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
							_rc.left = _rc.right - TILESIZE;
							_x = _rc.left + (_rc.right - _rc.left) / 2;
							break;
						}

					}

					_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
					_rc.top = _rc.bottom - TILESIZE;
					_y = _rc.top + (_rc.bottom - _rc.top) / 2;

					//_direction = (RND->getInt(2) != 0) ? LEFT : RIGHT;
					break;
				}
			}
		}
	}

	if (_isTrace)
	{

	}

	rcCollision = RectMakeCenter(_x, _y, SAMPLETILESIZE, SAMPLETILESIZE);
	_rc = rcCollision;
}

void TankEnemy::setEnemyPosition(int index)
{
	_rc = _tankMap->getTiles()[index].rc;
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}