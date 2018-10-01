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
		_isBlockingUI = false;
		return;
	}

	switch (_uiType)
	{
	case OPTION_MENU:
		updateOptionUI();
		break;
	case EXIT_MENU:
		updateExitUI();
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
		renderOptionUI(hdc);
		break;
	case EXIT_MENU:
		renderExitUI(hdc);
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
			_optionUI.selectVolumeBtn = true;

		if (PtInRect(&_optionUI.effectVolumeRect[1], _ptMouse))
			_optionUI.selectEffectVolumeBtn = true;

	}
	else
	{
		_optionUI.selectVolumeBtn = false;

		if (_optionUI.selectEffectVolumeBtn == true)
		{
			SOUNDMANAGER->play("충돌소리", _effectVolume);
			_optionUI.selectEffectVolumeBtn = false;
		}
	}



	if (_optionUI.selectVolumeBtn == true)
	{
		int x = _ptMouse.x;
		if (x < _optionUI.volumeRect[0].left)
			x = _optionUI.volumeRect[0].left;
		else if (x >  _optionUI.volumeRect[0].right)
			x = _optionUI.volumeRect[0].right;

		_optionUI.volumeRect[1] = RectMakeCenter(x, _optionUI.y + 102, _optionUI.optionBtnImg->getWidth(), _optionUI.optionBtnImg->getHeight());

		_soundVolume = (float)(x - _optionUI.volumeRect[0].left) / (_optionUI.volumeRect[0].right - _optionUI.volumeRect[0].left);
		SOUNDMANAGER->setVolume(_soundVolume);
	}

	if (_optionUI.selectEffectVolumeBtn == true)
	{
		int x = _ptMouse.x;
		if (x < _optionUI.effectVolumeRect[0].left)
			x = _optionUI.effectVolumeRect[0].left;
		else if (x >  _optionUI.effectVolumeRect[0].right)
			x = _optionUI.effectVolumeRect[0].right;

		_optionUI.effectVolumeRect[1] = RectMakeCenter(x, _optionUI.y + 136, _optionUI.optionBtnImg->getWidth(), _optionUI.optionBtnImg->getHeight());

		_effectVolume = (float)(x - _optionUI.effectVolumeRect[0].left) / (_optionUI.effectVolumeRect[0].right - _optionUI.effectVolumeRect[0].left);
		
	}

	
}

void UIManager::renderOptionUI(HDC hdc)
{
	_optionUI.optionImg->render(hdc, _optionUI.x, _optionUI.y);
	_optionUI.optionBtnImg->render(hdc, _optionUI.volumeRect[1].left, _optionUI.volumeRect[1].top);
	_optionUI.optionBtnImg->render(hdc, _optionUI.effectVolumeRect[1].left, _optionUI.effectVolumeRect[1].top);
}

void UIManager::updateExitUI()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4;++i)
		{
			if (PtInRect(&_exitUI.btnRect[i], _ptMouse))
				_exitUI.selectBtnIndex = i;
		}

		switch (_exitUI.selectBtnIndex)
		{
		case 0:
			_isBlockingUI = false;
			break;
		case 1:
			_isBlockingUI = false;
			SCENEMANAGER->loadScene("StartScene");
			break;
		case 2:
			_uiType = OPTION_MENU;
			break;
		case 3:
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
			break;
		}
	}

}

void UIManager::renderExitUI(HDC hdc)
{
	_exitUI.exitMenuImg->render(hdc, _exitUI.x, _exitUI.y);
}

OptionUI::OptionUI()
{
	optionImg = IMAGEMANAGER->addImage("optionMenu", "Texture/UI/option_570x180.bmp", 570, 180, true, RGB(255, 0, 255));
	optionBtnImg = IMAGEMANAGER->addImage("optionButton", "Texture/UI/optionButton_32x17.bmp", 32, 17, true, RGB(255, 0, 255));
	x = (WINSIZEX - optionImg->getWidth()) * 0.5f;
	y = (WINSIZEY - optionImg->getHeight())*0.5f;

	volumeRect[0] = RectMake(x+ 316, y+102, 227, 1);
	volumeRect[1] = RectMakeCenter(x + 316,y+ 102, optionBtnImg->getWidth(), optionBtnImg->getHeight());

	effectVolumeRect[0] = RectMake(x + 316, y + 136, 227, 1);;
	effectVolumeRect[1] = RectMakeCenter(x + 316, y + 136, optionBtnImg->getWidth(), optionBtnImg->getHeight());;

}

ExitUI::ExitUI()
{
	exitMenuImg = IMAGEMANAGER->addImage("exitMenu", "Texture/UI/exitMenu_260x315.bmp", 260, 315, true, RGB(255, 0, 255));
	x = (WINSIZEX - exitMenuImg->getWidth()) * 0.5f;
	y = (WINSIZEY - exitMenuImg->getHeight())*0.5f;

	btnRect[0] = RectMake(x + 110, y + 102, 44, 24);
	btnRect[1] = RectMake(x + 78, y + 150, 108, 24);
	btnRect[2] = RectMake(x + 110, y + 203, 44, 24);
	btnRect[3] = RectMake(x + 88, y + 254, 85, 24);

	selectBtnIndex = -1;
}
