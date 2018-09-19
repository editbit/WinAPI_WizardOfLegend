#pragma once
#include "gameNode.h"
#include "tileNode.h"

class MaptoolCard :
	public GameNode
{
public:
	CTRL cardType;

	float x, y;
	int curFrameX, count;

	int _currentPage;
	int _maxPage;

	int _drawNum;

	RECT rc;
	bool isDragged;
	bool isActive;

	Image * card;
	Image * changeEffect;

public:
	virtual void init(float x, float y);
	virtual void update();
	virtual void render();

	virtual bool  select() { return false; }

	void changeCard();
	void effectRender();

	void setIsDragged(bool is) { isDragged = is; }
	bool getIsDragged() { return isDragged; }
	int getCurrentPage() { return _currentPage; }
	void setCurrentPage(int curPage) { _currentPage = curPage; }

	void setDrawNum(int num) { _drawNum = num; }
	int getDrawNum() { return _drawNum; }

	void changePage(int page);

	MaptoolCard();
	virtual ~MaptoolCard();
};

