#include "stdafx.h"
#include "UIManager.h"
#include "progressBar.h"



HRESULT UIManager::init(void)
{
	_uiDC = new Image;
	_uiDC->init(WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_flickeringImg = new Image;
	_flickeringImg->init(WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_uiType = 0;
	_isDrawUI = false;
	_isBlockingUI = false;
	// flickering
	_count = 0;
	_alpha = 200;


	SetBkMode(_uiDC->getMemDC(), TRANSPARENT);

	return S_OK;
}

void UIManager::release(void)
{
	_flickeringImg->release();
	SAFE_DELETE(_flickeringImg);
	_uiDC->release();
	SAFE_DELETE(_uiDC);
}

void UIManager::update()
{
	
}

void UIManager::render(HDC hdc)
{

	_uiDC->render(hdc);

	if (_count > 0)
	{
		
		_alpha -= _speed;

		//brush = CreateSolidBrush(_color);
		//oBrush = (HBRUSH)SelectObject(_uiDC->getMemDC(), brush);
		//Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
		//SelectObject(_uiDC->getMemDC(), oBrush);
		//DeleteObject(brush);
		_flickeringImg->alphaRender(hdc, _alpha);

		_uiDC->alphaRender(hdc, _alpha);


		if (_alpha <= 0)
		{
			_alpha = 200;
			_count -= 1;
		}
	}

}

void UIManager::flickering(COLORREF color, int speed, int count)
{
	_color = color;
	_speed = speed;
	_count = count;


	brush = CreateSolidBrush(_color);
	oBrush = (HBRUSH)SelectObject(_flickeringImg->getMemDC(), brush);
	Rectangle(_flickeringImg->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
	SelectObject(_flickeringImg->getMemDC(), oBrush);
	DeleteObject(brush);


	HPEN pen = CreatePen(PS_SOLID, 2, _color);
	HPEN oPen = (HPEN)SelectObject(_flickeringImg->getMemDC(), pen);

	brush = CreateSolidBrush(RGB(255, 0, 255));
	oBrush = (HBRUSH)SelectObject(_flickeringImg->getMemDC(), brush);
	Rectangle(_flickeringImg->getMemDC(), { 50, 50, WINSIZEX - 50, WINSIZEY - 50 });
	SelectObject(_flickeringImg->getMemDC(), oBrush);
	DeleteObject(brush);

	SelectObject(_flickeringImg->getMemDC(), oPen);
	DeleteObject(pen);
}

void UIManager::clear()
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(_uiDC->getMemDC(), brush);
	Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
	DeleteObject(brush);
	
}
