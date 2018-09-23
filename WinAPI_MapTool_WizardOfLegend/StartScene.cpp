#include "stdafx.h"
#include "StartScene.h"


HRESULT StartScene::init()
{
	_titleImg = IMAGEMANAGER->findImage("title");
	_background = IMAGEMANAGER->findImage("titleBackground");


	text[START] = "Start";
	text[MAPTOOL] = "Map Tool";
	text[EXIT] = "Exit";
	
	_buttonPos[START].x= WINSIZEX / 2;
	_buttonPos[MAPTOOL].x = WINSIZEX / 2;
	_buttonPos[EXIT].x = WINSIZEX / 2;

	_buttonPos[START].y = WINSIZEY / 2 + 50;
	_buttonPos[MAPTOOL].y = WINSIZEY / 2 + 100;
	_buttonPos[EXIT].y = WINSIZEY / 2 + 150;


	for (int i = 0; i < 3; ++i)
	{
		_button[i] = RectMakeCenter(_buttonPos[i].x, _buttonPos[i].y, 100, 50);
	}

	_curButton = -1;


	SetTextAlign(getMemDC(), TA_CENTER); //텍스트 중앙정렬

	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	_curButton = -1;

	if (PtInRect(&_button[START], _ptMouse))
	{
		_curButton = START;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//SCENEMANAGER->loadScene("GameScene");
			SCENEMANAGER->loadScene("LoadingScene");
		}
	}
	else if (PtInRect(&_button[EXIT], _ptMouse))
	{
		_curButton = EXIT;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
		}
	}
	else if (PtInRect(&_button[MAPTOOL], _ptMouse))
	{
		_curButton = MAPTOOL;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->loadScene("타일맵");
		}
	}
}

void StartScene::render()
{

	_background->render(getMemDC());
	_titleImg->render(getMemDC(), WINSIZEX / 2 - _titleImg->getWidth()/2, WINSIZEY / 4 - _titleImg->getHeight() / 2);

	char str[128];

	for (int i = 0; i < 3; ++i)
	{
		if (_curButton == i)
		{

			SetTextColor(getMemDC(), RGB(0, 0, 0));

			font = CreateFont(25, 0, 2, 0, 2000, true, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("돋움"));
			oldFont = (HFONT)SelectObject(getMemDC(), font);


			sprintf_s(str, text[i].c_str());
			TextOut(getMemDC(), _buttonPos[i].x, _buttonPos[i].y, str, strlen(str));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
		}
		else
		{

			SetTextColor(getMemDC(), RGB(0, 0, 0));

			font = CreateFont(20, 0, 0, 0, 2000, false, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("돋움"));
			oldFont = (HFONT)SelectObject(getMemDC(), font);

			sprintf_s(str, text[i].c_str());
			TextOut(getMemDC(), _buttonPos[i].x, _buttonPos[i].y, str, strlen(str));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);

		}
	}

}
/*
	font = CreateFont(
	문자 크기, 문자 폭, 문자 기울기, 문자 방향, 문자 굵기,
	기울기(bool), 밑줄(bool), 취소선(bool),
	문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	)
	*/
	// 문자 폭은 문자크기에 따라 비례하게 표시. 0으로 두는 것이 좋음
