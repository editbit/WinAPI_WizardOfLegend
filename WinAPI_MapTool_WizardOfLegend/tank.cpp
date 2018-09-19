#include "stdafx.h"
#include "tank.h"
#include "tileMap.h"

HRESULT tank::init(void)
{
	//��ũ ������ �̹���
	//_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->findImage("player_walk");

	//��ũ���� �ʱ�ȭ
	_direction = TANKDIRECTION_UP;

	//��ũ �ӵ�
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
	//�������� ������ ��Ʈ
	RECT rcCollision;
	//rcCollision = _rc;

	//�˻��� Ÿ�� �ε���(�ּ� 2�� �ʿ���)
	

	//���� ��ũ�� ��� �ִ� Ÿ��
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
	case TANKDIRECTION_LEFT:

		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.top / TILESIZE;

		//����, ���ʾƷ�
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;/*
		tileIndex[2] = tileX + (tileY + 2) * TILEX;
		tileIndex[3] = tileX + (tileY + 3) * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_RIGHT:
		tileX = rcCollision.right / TILESIZE;
		tileY = rcCollision.top / TILESIZE;
		//������, �����ʾƷ�
		tileIndex[0] = (tileX) + tileY * TILEX;
		tileIndex[1] = (tileX) + (tileY + 1) * TILEX;/*
		tileIndex[2] = (tileX) + (tileY + 2) * TILEX;
		tileIndex[3] = (tileX)+(tileY + 3) * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_UP:
		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.top / TILESIZE;
		//��, ��������
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = (tileX + 1) + tileY * TILEX;/*
		tileIndex[2] = (tileX + 2) + tileY * TILEX;*/
		collisionRange = 2;
		break;
	case TANKDIRECTION_DOWN:
		tileX = rcCollision.left / TILESIZE;
		tileY = rcCollision.bottom / TILESIZE;
		//�Ʒ�, �����ʾƷ�
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