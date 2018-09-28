#include "stdafx.h"
#include "IceDash.h"


HRESULT IceDash::init()
{
	_dummy = new Dummy;
	_dummy->setLinkPlayer(_player);
	_dummy->setLinkEnemyManager(_enemyManager);
	_dummy->init();

	_iconImg = IMAGEMANAGER->findImage("iceDashIcon");
	_description = "적을 유인하는 분신을 생성하는 대시 스킬";


	BULLETMANAGER->setLinkDummy(_dummy);
	return S_OK;
}

void IceDash::release()
{
}

void IceDash::update()
{
	if (_dummy->getIsActive())
	{
		_dummy->update();
	}
}

void IceDash::render()
{
}

void IceDash::executeDash(float x, float y)
{
	if (!_dummy->getIsActive())
		_dummy->generate(x, y, _player->getIndex(), _player->getDir());
}
