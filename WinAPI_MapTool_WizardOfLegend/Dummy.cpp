#include "stdafx.h"
#include "EnemyManager.h"
#include "Dummy.h"



HRESULT Dummy::init()
{
	_img = IMAGEMANAGER->findImage("player_dummy");

	_power = 5;
	_index = _dir = 0;
	_isActive = false;
	return S_OK;
}

void Dummy::release()
{
}

void Dummy::update()
{
	_count = (_count + 1) % 120;
	if (_count == 0)
	{
		_enemyManager->changeDummy(_player);
		_isActive = false;
	}
}

void Dummy::render()
{
	if (!_isActive) return;

	_img->frameRender(getMemDC(), _x - _img->getFrameWidth() / 2 - CAM->getX(), _moveBox.bottom - _img->getFrameHeight() - CAM->getY(), _index, _dir);

}

void Dummy::damaged(Actor * e)
{
	vector<Enemy *>& em = _enemyManager->getEnemys();
	RECT temp;

	_isActive = false;

	for (int i = 0; i < em.size(); ++i)
	{
		if (!em[i]->getIsActive()) continue;
		//temp = { 0, 0, 0, 0 };
		if (IntersectRect(&temp, &em[i]->getHitBox(), &_attackBox))
		{
			em[i]->damaged(this);
			EFFECTMANAGER->play("¾óÀ½±âµÕ", em[i]->getX(), em[i]->getCenterY());
		}
	}

	_enemyManager->changeDummy(_player);
}

void Dummy::generate(float x, float y, int index, int dir)
{
	_x = x; _y = y;
	_moveBox = RectMakeCenter(x, y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(x, y, WIZARD::HITBOX_WIDTH, WIZARD::HITBOX_HEIGHT);
	_attackBox = RectMakeCenter(x, y, 200, 200);
	_index = index;
	_dir = dir;
	_isActive = true;
	_enemyManager->changeDummy(this);
}
