#pragma once
#include "gameNode.h"

enum SKILL_TYPE
{
	ATTACK_SKILL, DASH_SKILL
};

class Skill :
	public GameNode
{
protected:
	Image * _iconImg;
	int _skillType;

public:
	virtual HRESULT init();				//void�� �ᵵ�Ǵµ� �ʱ�ȭ�� ������ ����� �ٷ� �˷���
	virtual void release();
	virtual void update();
	virtual void render();

	void renderIcon(float x, float y);

	int getSkillType() { return _skillType; }

	Skill() {}
	~Skill() {}
};

