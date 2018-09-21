#include "stdafx.h"
#include "Skill.h"

HRESULT Skill::init()
{
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
