#include "stdafx.h"
#include "MaptoolCard.h"




MaptoolCard::MaptoolCard()
{
	x = WINSIZEX / 2; y = WINSIZEY / 2;
	_currentPage = 0;
	_maxPage = 1;
	rc = { 0, 0, 0,0 };
	card = IMAGEMANAGER->findImage("card");
	changeEffect = IMAGEMANAGER->findImage("cardEffect");

	isDragged = false;
	isActive = true;
}

MaptoolCard::~MaptoolCard()
{
}

void MaptoolCard::init(float x, float y)
{
	card = IMAGEMANAGER->findImage("card");
	changeEffect = IMAGEMANAGER->findImage("cardEffect");

	this->x = x;
	this->y = y;
	rc = RectMakeCenter(x, y, card->getWidth(), card->getHeight());
	curFrameX = -1;
	count = 0;
	isActive = false;
}

void MaptoolCard::update()
{ 
	rc = RectMakeCenter(x, y, card->getWidth(), card->getHeight());
}

void MaptoolCard::render()
{
	card->render(getMemDC(), rc.left, rc.top);
}

void MaptoolCard::changeCard() {
	curFrameX = 0;
	count = 0;
}
void MaptoolCard::effectRender()
{
	if (curFrameX < 0) return;

	changeEffect->frameRender(getMemDC(), rc.left, rc.top, curFrameX, 0);

	count = (count + 1) % 3;

	if (count == 0)
	{
		++curFrameX;
		if (curFrameX > changeEffect->getMaxFrameX())
		{
			curFrameX = -1;
		}
	}
}


void MaptoolCard::changePage(int page)
{
	_currentPage += page;
	if (_currentPage < 0)
		_currentPage = 0;
	else if (_currentPage >= _maxPage)
		_currentPage = _maxPage - 1;
}