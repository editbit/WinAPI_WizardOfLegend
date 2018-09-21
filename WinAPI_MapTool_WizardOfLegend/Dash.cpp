#include "stdafx.h"
#include "Dash.h"


HRESULT Dash::init()
{
	_skillType = DASH_SKILL;
	_timer = 0;
	_count = 0;
	return S_OK;
}

void Dash::release()
{
}

void Dash::update()
{
}

void Dash::render()
{
}

void Dash::executeDash(float x, float y)
{
}
