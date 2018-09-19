#include "stdafx.h"
#include "Stuff.h"

HRESULT Stuff::init()
{
	_state = 1;
	return S_OK;
}

void Stuff::release()
{
}

void Stuff::update()
{
}

void Stuff::render()
{
	_img->render(getMemDC(), _renderPos.x - CAM->getX(), _renderPos.y - CAM->getY());
}

