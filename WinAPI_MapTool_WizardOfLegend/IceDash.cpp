#include "stdafx.h"
#include "IceDash.h"
#include "EnemyManager.h"


HRESULT IceDash::init()
{
	_dummy = new Dummy;
	_dummy->setLinkPlayer(_player);
	_dummy->setLinkEnemyManager(_enemyManager);
	_dummy->init();

	_iconImg = IMAGEMANAGER->findImage("iceDashIcon");
	_description = "���� �����ϴ� �н��� �����ϴ� ��� ��ų";


	BULLETMANAGER->setLinkDummy(_dummy);
	return S_OK;
}

void IceDash::release()
{
	_dummy->release();
	SAFE_DELETE(_dummy);
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

void IceDash::endDash()
{
	if (_dummy != NULL)
	{
		_enemyManager->changeDummy(_player);
		_dummy->setIsActive(false);
	}
}

void IceDash::executeDash(float x, float y)
{
	if (!_dummy->getIsActive())
		_dummy->generate(x, y, _player->getIndex(), _player->getDir());
}
