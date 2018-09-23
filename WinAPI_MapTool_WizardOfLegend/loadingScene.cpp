#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(void)
{
	_fileName = SAVEDATA->getMapName();
	_tileMap = SAVEDATA->getTileMap();


	_tileMap->prepareLoading(_fileName.c_str());

	_str[0] = "���� �д� ��...";
	_str[1] = "�� ��ġ ��...";
	_str[2] = "������Ʈ ��ġ ��...";
	_str[3] = "�Ϸ�";

	_count = _index = 0;

	return S_OK;
}

void LoadingScene::release(void)
{
}

void LoadingScene::update(void)
{
	if (_tileMap->loadingDone())
	{
		SCENEMANAGER->loadScene("GameScene");

		return;
	}

	_count++;
	if (_count % 80 == 0)
	{
		_count = 0;
		_index++;
		if (_index >= 4)
			_index = 3;
	}
}

void LoadingScene::render(void)
{
	char str[256];

	for (int i = _index, count = 0; i >= 0; --i, count++ )
	{
		sprintf_s(str, "%s", _str[_index - count].c_str());
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 200 - count * 50, str, strlen(str));
	}
}
