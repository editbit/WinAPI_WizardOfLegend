#include "stdafx.h"
#include "ObjectCard.h"


void ObjectCard::init(float x, float y)
{
	MaptoolCard::init(x, y);
	
	cardType = CTRL_OBJDRAW;

	_drawNum = 4;
	_maxPage = 4;

	settingSample();
}

void ObjectCard::update()
{
	MaptoolCard::update();
}

void ObjectCard::render()
{
	MaptoolCard::render();

	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	for (int i = _currentPage * _drawNum * 3; i < _currentPage * _drawNum * 3 + _drawNum * 3 && i < SAMPLE_OBJECT_MAX; ++i)
	{
		Rectangle(getMemDC(), 55 +  rc.left + _sampleObject[i].rc.left, 99 +  rc.top + _sampleObject[i].rc.top, 55 + rc.left + _sampleObject[i].rc.right, 99 + rc.top + _sampleObject[i].rc.bottom);

		_sampleObject[i].objImg->render(getMemDC(), 
			55 + rc.left + _sampleObject[i].rc.left + SAMPLE_OBJECT_RC_SIZE/2 - _sampleObject[i].width/2,
			99 + rc.top + _sampleObject[i].rc.top + SAMPLE_OBJECT_RC_SIZE / 2 - _sampleObject[i].height / 2,
			_sampleObject[i].objImg->getWidth() / 2 - _sampleObject[i].width / 2, 0,
			_sampleObject[i].width, _sampleObject[i].height);
	}

	SelectObject(getMemDC(), oBrush);
	DeleteObject(brush);

	effectRender();
}

void ObjectCard::settingSample()
{
	/*
	기둥 1
	문 4
	물체 11
	배경 1
	바닥 1
	벽장식 5
	석상 7
	함정 2
	*/

	string type[SAMPLE_OBJECT_TYPE] = {
		"기둥",
		"문",
		"물체",
		"배경",
		"바닥",
		"벽장식",
		"석상",
		"함정",
	};
	int maxNum[SAMPLE_OBJECT_TYPE] = { 1, 4, 10, 1, 1, 5, 7, 1 };

	int i = 0;
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "기둥1");	// 0
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "문1");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "문2");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "문3");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "문4");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "물체1");	// 5
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "물체2");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "물체3");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "물체4");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "물체5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "물체6");	// 10
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "물체7");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "물체8");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "물체9");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage( "물체10");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "배경1");	// 15
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "바닥1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식3");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식4");	// 20
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("벽장식6");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상3");	// 25
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상4");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상6");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "석상7");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "함정1");	// 30
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("나무1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("나무2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("나무3");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("나무4");	// 34
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("출구");
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("입구");	// 36
	frameImangeIndex = i;
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("함정2");
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("보물상자1");	// 38





	int xPos = 0, yPos = 0;
	for (int i = 0; i < SAMPLE_OBJECT_MAX; ++i)
	{
		_sampleObject[i].width = (_sampleObject[i].objImg->getWidth() < SAMPLE_OBJECT_RC_SIZE)? _sampleObject[i].objImg->getWidth() : SAMPLE_OBJECT_RC_SIZE;
		_sampleObject[i].height = (_sampleObject[i].objImg->getHeight() < SAMPLE_OBJECT_RC_SIZE) ? _sampleObject[i].objImg->getHeight() : SAMPLE_OBJECT_RC_SIZE;

		_sampleObject[i].rc = RectMake(
			xPos * (SAMPLE_OBJECT_RC_SIZE + 30), 
			yPos * (SAMPLE_OBJECT_RC_SIZE + 30),
			SAMPLE_OBJECT_RC_SIZE, SAMPLE_OBJECT_RC_SIZE);

		xPos = (xPos + 1) % 3;
		if(xPos == 0) yPos = (yPos + 1) % _drawNum;
	}
}
