#include "stdafx.h"
#include "TankEnemy.h"
#include "tileMap.h"

HRESULT TankEnemy::init(void)
{
	//��ũ ������ �̹���
	//_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->findImage("enemy_walk");

	//��ũ���� �ʱ�ȭ
	_direction = UP;

	//��ũ �ӵ�
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
	//�������� ������ ��Ʈ
	RECT rcCollision;
	//rcCollision = _rc;

	//�˻��� Ÿ�� �ε���(�ּ� 2�� �ʿ���)


	//���� ��ũ�� ��� �ִ� Ÿ��
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


	//�浹��Ʈ ũ�⸦ Ÿ��ũ�⺸�� �� �۰� ����ش�
	//32 * 32 ������ 0.1������ ������ Ÿ�� ���̸� �������� ���� ����
	rcCollision.left += 1;
	rcCollision.right -= 1;
	rcCollision.top += 1;
	rcCollision.bottom -= 1;

	//��ũ�� �ε����� Ȯ���� �� �ִ�
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//Ÿ�ϸ� �˻��ϱ�(�����¿� ���� 2����)
	//�ڱ���ġ�� ������� Ÿ���� ���ΰ˻��ϸ� �������� ������ �� ������
	//�����¿� ���� 2������ �˻縦 ����
	switch (_direction)
	{
	case LEFT:
		//����, ���ʾƷ�
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
	case RIGHT:
		//������, �����ʾƷ�
		tileIndex[0] = (tileX + 1) + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + (tileY + 1) * TILEX;
		break;
	case UP:
		//��, ��������
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;
		break;
	case DOWN:
		//�Ʒ�, �����ʾƷ�
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