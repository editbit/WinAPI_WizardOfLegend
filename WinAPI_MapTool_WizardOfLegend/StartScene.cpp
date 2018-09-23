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


	SetTextAlign(getMemDC(), TA_CENTER); //�ؽ�Ʈ �߾�����

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
			SCENEMANAGER->loadScene("Ÿ�ϸ�");
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

			font = CreateFont(25, 0, 2, 0, 2000, true, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
			oldFont = (HFONT)SelectObject(getMemDC(), font);


			sprintf_s(str, text[i].c_str());
			TextOut(getMemDC(), _buttonPos[i].x, _buttonPos[i].y, str, strlen(str));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
		}
		else
		{

			SetTextColor(getMemDC(), RGB(0, 0, 0));

			font = CreateFont(20, 0, 0, 0, 2000, false, false, false, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
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
	���� ũ��, ���� ��, ���� ����, ���� ����, ���� ����,
	����(bool), ����(bool), ��Ҽ�(bool),
	���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
	)
	*/
	// ���� ���� ����ũ�⿡ ���� ����ϰ� ǥ��. 0���� �δ� ���� ����
