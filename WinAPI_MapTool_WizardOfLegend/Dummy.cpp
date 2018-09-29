#include "stdafx.h"
#include "EnemyManager.h"
#include "Dummy.h"



HRESULT Dummy::init()
{
	_img = IMAGEMANAGER->findImage("player_dummy");
	_effectImg = IMAGEMANAGER->findImage("ice_skill");

	_power = 5;
	_index = _dir = 0;
	_isActive = false;
	_isCrash = false;

	_state = 1;
	return S_OK;
}

void Dummy::release()
{
}

void Dummy::update()
{
	_count = (_count + 1) % 180;
	if (_count == 0)
	{
		_enemyManager->changeDummy(_player);
		_isActive = false;
		return;
	}
	

	if (_isCrash)
	{
		if (_index != 4)
		{
			if (_count % 10 == 0)
			{
				_index += 1;
				if (_index > _effectImg->getMaxFrameX())
					_index = _effectImg->getMaxFrameX();
			}
		}
		else if (_count >= 150)
		{
			_index += 1;
			if (_index > _effectImg->getMaxFrameX())
				_index = _effectImg->getMaxFrameX();
		}

		for (int i = 0; i < _enemys.size(); ++i)
		{
			_enemys[i]->freeze(_enemysPos[i].x, _enemysPos[i].y);
		}
	}
	if(!_isCrash)
		RENDERMANAGER->addRender(_moveBox.bottom, this);
	else
		RENDERMANAGER->addRender(TILESIZEY, this);
}

void Dummy::render()
{
	if (!_isActive) return;

	if(!_isCrash)
		_img->frameRender(getMemDC(), _x - _img->getFrameWidth() / 2 - CAM->getX(), _moveBox.bottom - _img->getFrameHeight() - CAM->getY(), _index, _dir);
	else
	{
		for (int i = 0; i < _enemys.size(); ++i)
		{
			_effectImg->alphaFrameRender(getMemDC(), 
				_enemys[i]->getX() - _effectImg->getFrameWidth() * 0.5f - CAM->getX(), 
				_enemys[i]->getMoveBox().bottom - _effectImg->getFrameHeight() - CAM->getY(), _index, 0, 100);
		}
	}

}

void Dummy::damaged(Actor * e)
{
	vector<Enemy *>& em = _enemyManager->getEnemys();
	RECT temp;

	if (_isCrash)
		return;

	_enemys.clear();
	_enemysPos.clear();

	_index = 0;
	_count = 0;
	_isCrash = true;

	for (int i = 0; i < em.size(); ++i)
	{
		if (!em[i]->getIsActive()) continue;
		//temp = { 0, 0, 0, 0 };
		if (IntersectRect(&temp, &em[i]->getHitBox(), &_attackBox))
		{
			em[i]->damaged(this);
			//EFFECTMANAGER->play("¾óÀ½±âµÕ", em[i]->getX(), em[i]->getCenterY());

			_enemys.push_back(em[i]);
			_enemysPos.push_back({ (int)em[i]->getX(), (int)em[i]->getY() });
		}
	}

	_enemyManager->changeDummy(_player);
}

void Dummy::generate(float x, float y, int index, int dir)
{
	_x = x; _y = y;
	_moveBox = RectMakeCenter(x, y, WIZARD::MOVEBOX_WIDTH, WIZARD::MOVEBOX_HEIGHT);
	_hitBox = RectMakeCenter(x, y - WIZARD::MOVEBOX_HEIGHT / 2, WIZARD::HITBOX_WIDTH, WIZARD::HITBOX_HEIGHT);
	_attackBox = RectMakeCenter(x, y, 200, 200);
	_index = index;
	_dir = dir;
	_count = 0;
	_isActive = true;
	_isCrash = false;
	_enemyManager->changeDummy(this);
}
