#include "stdafx.h"
#include "Bomb.h"
#include "Enemy.h"


tagTile* Bomb::_tiles = NULL;

HRESULT Bomb::init()
{
	_state = 1;
	_dir = 0;
	_index = 0;
	_power = 5;
	_isActive = true;
	return S_OK;
}


void Bomb::render()
{
	_img->render(getMemDC(), _renderPos.x - CAM->getX(), _renderPos.y - CAM->getY());
}

bool Bomb::collide(Actor * a, vector<Enemy*>& em)
{
	EFFECTMANAGER->play("Æø¹ß", _x, _y);

	a->damaged(this);
	RECT temp;
	for (int i = 0; i < em.size(); ++i)
	{
		if (IntersectRect(&temp, &_attackBox, &em[i]->getHitBox()))
		{
			em[i]->damaged(this);
		}
	}
	_isActive = false;

	collideStuff(em);


	return true;
}

bool Bomb::collide(Actor * a)
{
	a->damaged(this);
	EFFECTMANAGER->play("Æø¹ß", _x, _y);
	_isActive = false;

	return true;
}

bool Bomb::damaged(Actor * a, vector<Enemy*>& em)
{
	return collide(a, em);
}

void Bomb::collideStuff(vector<Enemy*>& em)
{
	int startX = _attackBox.left / TILESIZE, endX = _attackBox.right / TILESIZE;
	int startY = _attackBox.top / TILESIZE, endY = _attackBox.bottom / TILESIZE;


	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			if (_tiles[i * TILEX + j].objType == OBJECT_TRAP)
			{
				if (!_tiles[i * TILEX + j].obj->getIsActive()) continue;

				if (_tiles[i * TILEX + j].obj->damaged(this, em))
				{
					_tiles[i * TILEX + j].objType = OBJECT_NONE;
				}
			}
		}
	}
}

Bomb::Bomb(Image * img, POINT renderPos) : Stuff(img, renderPos) {
	init();
	_x = renderPos.x + img->getWidth() / 2;
	_y = renderPos.y + img->getHeight() / 2;

	_attackBox = RectMakeCenter(_x, _y, 200, 200);
}