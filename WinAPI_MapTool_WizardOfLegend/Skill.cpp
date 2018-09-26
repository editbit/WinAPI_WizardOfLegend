#include "stdafx.h"
#include "Skill.h"
#include "actor.h"
#include "EnemyManager.h"

HRESULT Skill::init()
{
	_power = 10;
	return S_OK;
}

void Skill::release()
{
}

void Skill::update()
{
}

void Skill::render()
{
}

void Skill::renderIcon(float x, float y)
{
	_iconImg->render(UIMANAGER->getUIDC(), x - _iconImg->getWidth()/2, y - _iconImg->getHeight()/2);
}
