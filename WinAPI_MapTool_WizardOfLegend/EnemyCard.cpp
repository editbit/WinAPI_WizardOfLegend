#include "stdafx.h"
#include "EnemyCard.h"


void EnemyCard::init(float x, float y)
{
	MaptoolCard::init(x, y);
	cardType = CTRL_ENEMYDRAW;

	_drawNum = 4;
	_maxPage = 1;

	settingSample();
}

void EnemyCard::update()
{
	MaptoolCard::update();
}

void EnemyCard::render()
{
	MaptoolCard::render();


	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	for (int i = _currentPage * _drawNum * 3; i < _currentPage * _drawNum * 3 + _drawNum * 3 && i < _sampleEnemy.size(); ++i)
	{
		Rectangle(getMemDC(), 55 + rc.left + _sampleEnemy[i].rc.left, 99 + rc.top + _sampleEnemy[i].rc.top, 55 + rc.left + _sampleEnemy[i].rc.right, 99 + rc.top + _sampleEnemy[i].rc.bottom);

		_sampleEnemy[i].img->render(getMemDC(),
			55 + rc.left + _sampleEnemy[i].rc.left + SAMPLE_ENEMY_RC_SIZE / 2 - _sampleEnemy[i].width / 2,
			99 + rc.top + _sampleEnemy[i].rc.top + SAMPLE_ENEMY_RC_SIZE / 2 - _sampleEnemy[i].height / 2,
			_sampleEnemy[i].img->getFrameWidth() / 2 - _sampleEnemy[i].width / 2, 0,
			_sampleEnemy[i].width, _sampleEnemy[i].height);
	}

	SelectObject(getMemDC(), oBrush);
	DeleteObject(brush);

	effectRender();
}

void EnemyCard::settingSample()
{

	int xPos = 0, yPos = 0;
	SampleEnemy temp;

	_sampleEnemy.clear();
	for (int i = 0; i < SAMPLE_ENEMY_MAX; ++i)
	{
		temp.width = 0;
		temp.height = 0;

		temp.rc = RectMake(
			xPos * (SAMPLE_ENEMY_RC_SIZE + 30),
			yPos * (SAMPLE_ENEMY_RC_SIZE + 30),
			SAMPLE_ENEMY_RC_SIZE, SAMPLE_ENEMY_RC_SIZE);

		xPos = (xPos + 1) % 3;
		if (xPos == 0) yPos = (yPos + 1) % _drawNum;

		_sampleEnemy.push_back(temp);
	}

	int i = 0;
	_sampleEnemy[i++].img = IMAGEMANAGER->findImage("shadow_idle");
	_sampleEnemy[i++].img = IMAGEMANAGER->findImage("mage_idle");
	_sampleEnemy[i++].img = IMAGEMANAGER->findImage("rogue_idle");

	for (int i = 0; i < _sampleEnemy.size(); ++i)
	{
		_sampleEnemy[i].width = (_sampleEnemy[i].img->getFrameWidth() < SAMPLE_ENEMY_RC_SIZE) ? _sampleEnemy[i].img->getFrameWidth() : SAMPLE_ENEMY_RC_SIZE;
		_sampleEnemy[i].height = (_sampleEnemy[i].img->getFrameHeight() < SAMPLE_ENEMY_RC_SIZE) ? _sampleEnemy[i].img->getFrameHeight() : SAMPLE_ENEMY_RC_SIZE;
	}
}
