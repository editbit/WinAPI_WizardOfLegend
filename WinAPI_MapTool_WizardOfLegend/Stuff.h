#pragma once
#include "actor.h"

class Enemy;

class Stuff : public Actor
{
protected:
	Image * _img;
	POINT _renderPos;

public:
	virtual HRESULT init();				//void�� �ᵵ�Ǵµ� �ʱ�ȭ�� ������ ����� �ٷ� �˷���
	virtual void release();
	virtual void update();
	virtual void render();

	virtual bool checkAttack() { return false; }

	virtual bool damaged(Actor * a, vector<Enemy*>& em) { return false; }
	virtual bool collide(Actor * actor) {return false;}
	virtual bool collide(Actor * actor, vector<Enemy*>& em) { return false; }

	Stuff() : _img(NULL) { _state = 1; }
	Stuff(Image * img, POINT renderPos) : _img(img), _renderPos(renderPos) { _state = 1; }
	~Stuff() {}
};

