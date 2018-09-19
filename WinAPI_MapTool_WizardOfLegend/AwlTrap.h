#pragma once
#include "Stuff.h"
class AwlTrap :
	public Stuff
{
public:
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();

	virtual bool checkAttack();
	virtual bool collide(Actor * a, vector<Enemy*>& em);
	virtual bool collide(Actor * a);

	AwlTrap() {}
	AwlTrap(Image * img, POINT renderPos) : Stuff(img, renderPos) { 
		init();
		_x = renderPos.x + img->getFrameWidth() / 2;
		_y = renderPos.y + img->getFrameHeight() / 2;
	}
	~AwlTrap() {}
};

