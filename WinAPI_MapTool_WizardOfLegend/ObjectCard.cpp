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
	��� 1
	�� 4
	��ü 11
	��� 1
	�ٴ� 1
	����� 5
	���� 7
	���� 2
	*/

	string type[SAMPLE_OBJECT_TYPE] = {
		"���",
		"��",
		"��ü",
		"���",
		"�ٴ�",
		"�����",
		"����",
		"����",
	};
	int maxNum[SAMPLE_OBJECT_TYPE] = { 1, 4, 10, 1, 1, 5, 7, 1 };

	int i = 0;
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "���1");	// 0
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "��1");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "��2");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "��3");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage(   "��4");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "��ü1");	// 5
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "��ü2");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "��ü3");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "��ü4");
	_sampleObject[i++].objImg  = IMAGEMANAGER->findImage( "��ü5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "��ü6");	// 10
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "��ü7");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "��ü8");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "��ü9");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage( "��ü10");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "���1");	// 15
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "�ٴ�1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����3");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����4");	// 20
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("�����6");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����3");	// 25
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����4");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����5");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����6");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����7");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage(  "����1");	// 30
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("����1");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("����2");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("����3");
	_sampleObject[i++].objImg =  IMAGEMANAGER->findImage("����4");	// 34
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("�ⱸ");
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("�Ա�");	// 36
	frameImangeIndex = i;
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("����2");
	_sampleObject[i++].objImg = IMAGEMANAGER->findImage("��������1");	// 38





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
