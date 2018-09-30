#pragma once
#include "Skill.h"


class Dash
	: public Skill
{
protected:
	float _x, _y;


	int _timer, _count;
public:

	virtual void executeDash(float x, float y);


	virtual HRESULT init();				//void�� �ᵵ�Ǵµ� �ʱ�ȭ�� ������ ����� �ٷ� �˷���
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPosition(float x, float y) { _x = x; _y = y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	virtual void endDash() {}

	Dash() { init(); }
	Dash(Actor *p, EnemyManager* em) : Skill(p, em) { init(); }
	~Dash() {}
};

