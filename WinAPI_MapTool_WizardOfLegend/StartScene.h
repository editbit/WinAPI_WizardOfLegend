#pragma once
#include "gameNode.h"
class StartScene :
	public GameNode
{
	enum {START, EXIT, MAPTOOL};

	Image * _titleImg, *_background;

	RECT _button[3];
	string text[3];
	POINT _buttonPos[3];
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

