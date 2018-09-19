#include "stdafx.h"
#include "UIManager.h"
#include "progressBar.h"



HRESULT UIManager::init(void)
{
	_uiDC = new Image;
	_uiDC->init(WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_uiType = 0;
	_isDrawUI = false;
	_isBlockingUI = false;
	// flickering
	_count = 0;
	_alpha = 200;

	_sceneChanging = _startingScene = false;


	return S_OK;
}

void UIManager::release(void)
{
	_uiDC->release();
	SAFE_DELETE(_uiDC);
}

void UIManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_isDrawUI = true;
	}
	if (!_isDrawUI) return;

	switch (_uiType)
	{
	case 0:

		break;
	case 1:

		break;
	}
}

void UIManager::render(HDC hdc)
{

	_uiDC->render(hdc);


	if (_sceneChanging)
	{
		_count = 0;

		sceneChange(hdc);

	}
	else if (_startingScene)
	{
		_count = 0;

		newSceneStart(hdc);
	}
	else if (_count > 0)
	{
		
		_alpha -= _speed;

		brush = CreateSolidBrush(_color);
		SelectObject(_uiDC->getMemDC(), brush);
		Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
		DeleteObject(brush);

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
}

void UIManager::sceneChange(HDC hdc)
{
	RECT rc = RectMakeCenter(_destX - CAM->getX(), _destY - CAM->getY(), _rcWidth, _rcHeight);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(_uiDC->getMemDC(), brush);
	Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(_uiDC->getMemDC(), brush);
	Ellipse(_uiDC->getMemDC(), rc);
	DeleteObject(brush);

	_uiDC->render(hdc);


	if (_rcWidth <= 0 || _rcHeight <= 0)
	{
		_sceneChanging = false;
		_endScene = true;
	}

	_rcWidth -= WINSIZEX / 50;
	_rcHeight -= WINSIZEY / 50;
	if (_rcWidth <= 0 || _rcHeight <= 0)
	{
		_rcWidth = 0;
		_rcHeight = 0;
	}
}

void UIManager::startingSceneChange(int x, int y)
{
	_sceneChanging = true;
	_endScene = false;
	_destX = x;
	_destY = y;
	_rcWidth = WINSIZEX * 2;
	_rcHeight = WINSIZEY * 2;
}

void UIManager::newSceneStart(HDC hdc)
{
	RECT rc = RectMakeCenter(_destX - CAM->getX(), _destY - CAM->getY(), _rcWidth, _rcHeight);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(_uiDC->getMemDC(), brush);
	Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(_uiDC->getMemDC(), brush);
	Ellipse(_uiDC->getMemDC(), rc);
	DeleteObject(brush);

	_uiDC->render(hdc);


	if (_rcWidth >= WINSIZEX * 2 || _rcHeight >= WINSIZEY * 2)
	{
		_startingScene = false;
		_endScene = false;
	}

	_rcWidth += WINSIZEX / 50;
	_rcHeight += WINSIZEY / 50;
	if (_rcWidth >= WINSIZEX * 2 || _rcHeight >= WINSIZEY*2)
	{
		_rcWidth = WINSIZEX * 2;
		_rcHeight = WINSIZEY * 2;;
	}
}

void UIManager::startingNewScene(int x, int y)
{
	_endScene = false;
	_startingScene = true;
	_destX = x;
	_destY = y;
	_rcWidth = 0;
	_rcHeight = 0;
}

void UIManager::clear()
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(_uiDC->getMemDC(), brush);
	Rectangle(_uiDC->getMemDC(), RectMake(0, 0, WINSIZEX, WINSIZEY));
	DeleteObject(brush);
	
}
