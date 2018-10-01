#include "stdafx.h"
#include "Skill.h"
#include "actor.h"
#include "EnemyManager.h"

HRESULT Skill::init()
{
	_coolTime = 0;
	_coolTimeCount = 0;
	return S_OK;
}

void Skill::release()
{
}

void Skill::update()
{
	++_coolTimeCount;
	if (_coolTimeCount >= _coolTime)
		_coolTimeCount = _coolTime;
}

void Skill::render()
{
}

void Skill::renderIcon(float x, float y)
{
	_iconImg->render(UIMANAGER->getUIDC(), x - _iconImg->getWidth()/2, y - _iconImg->getHeight()/2);
}
