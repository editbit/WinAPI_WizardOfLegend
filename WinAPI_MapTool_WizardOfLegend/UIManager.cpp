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
	if (!_isBlockingUI)
		return;
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{

	}

	switch (_uiType)
	{
	case OPTION_MENU:
		updateOptionUI();
		break;
	}
}

void UIManager::render(HDC hdc)
{

	_uiDC->render(hdc);

	if (_count > 0)
	{
		_alpha -= _speed;

		_flickeringImg->alphaRender(hdc, _alpha);

		_uiDC->alphaRender(hdc, _alpha);


		if (_alpha <= 0)
		{
			_alpha = 200;
			_count -= 1;
		}
	}

	if (!_isBlockingUI)
		return;

	switch (_uiType)
	{
	case OPTION_MENU:
		renderOptionUI();
		break;
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

void UIManager::updateOptionUI()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_optionUI.volumeRect[1], _ptMouse))
		{
			int x = _ptMouse.x;
			if (x < _optionUI.volumeRect[0].left)
				x = _optionUI.volumeRect[0].left;
			else if (x >  _optionUI.volumeRect[0].right)
				x = _optionUI.volumeRect[0].right;

			_optionUI.volumeRect[1] = RectMakeCenter(x, 102, _optionUI.optionBtnImg->getWidth(), _optionUI.optionBtnImg->getHeight());

			_soundVolume = (float)(x - _optionUI.volumeRect[0].left) / (_optionUI.volumeRect[0].right - _optionUI.volumeRect[0].left);
		}
	}
}

void UIManager::renderOptionUI()
{
	_optionUI.optionImg->render(_uiDC->getMemDC(), _optionUI.x, _optionUI.y);
	_optionUI.optionBtnImg->render(_uiDC->getMemDC(), _optionUI.volumeRect[1].left, _optionUI.volumeRect[1].top);
}

OptionUI::OptionUI()
{
	optionImg = IMAGEMANAGER->addImage("optionMenu", "Texture/UI/audioOption_570x125.bmp", 570, 125, true, RGB(255, 0, 255));
	optionBtnImg = IMAGEMANAGER->addImage("optionButton", "Texture/UI/optionButton_32x17.bmp", 32, 17, true, RGB(255, 0, 255));
	x = (WINSIZEX - optionImg->getWidth()) * 0.5f;
	y = (WINSIZEY - optionImg->getHeight())*0.5f;

	volumeRect[0] = RectMake(316, 102, 227, 1);
	volumeRect[1] = RectMakeCenter(316, 102, optionBtnImg->getWidth(), optionBtnImg->getHeight());
}
