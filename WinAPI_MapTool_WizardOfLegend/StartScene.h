#pragma once
#include "gameNode.h"

#define BUTTON_MAX 4

class StartScene :
	public GameNode
{
	enum {START, MAPTOOL, OPTION, EXIT};

	Image * _titleImg, *_background;

	RECT _button[BUTTON_MAX];
	string text[BUTTON_MAX];
	POINT _buttonPos[BUTTON_MAX];
	int _curButton;

	HFONT font;
	HFONT oldFont;
public:
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();

	StartScene() {}
	~StartScene() {}
};

