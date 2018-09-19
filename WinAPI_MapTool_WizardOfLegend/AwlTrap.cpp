#include "stdafx.h"
#include "AwlTrap.h"


HRESULT AwlTrap::init()
{
	_state = 1;
	_dir = 0;
	_index = 0;
	_power = 5;
	_isActive = true;
	return S_OK;
}

void AwlTrap::release()
{
}

void AwlTrap::update()
{
}

void AwlTrap::render()
{
	_img->frameRender(getMemDC(), _renderPos.x - CAM->getX(), _renderPos.y - CAM->getY(), _img->getFrameX(), _img->getFrameY());
}

bool AwlTrap::checkAttack()
{
	if (_img->getFrameX() == 1)
		return true;
	return false;
}

bool AwlTrap::collide(Actor * a, vector<Enemy*>& em)
{
	a->damaged(this);

	return false;
}

bool AwlTrap::collide(Actor * a)
{
	a->damaged(this);

	return false;
}
