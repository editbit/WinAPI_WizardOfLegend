#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(void)
{
	_fileName = SAVEDATA->getMapName();
	_tileMap = SAVEDATA->getTileMap();

	_loadingCircle = IMAGEMANAGER->findImage("loadingCircle");

	_tileMap->prepareLoading(_fileName.c_str());

	_str.clear();
	_str.push_back("성을 재생성하는 중");
	_str.push_back("레이아웃을 조정하는 중");
	_str.push_back("어둠을 걷어내는 중");
	_str.push_back("즐겨찾기를 선택하는 중");
	_str.push_back("인테리어를 꾸미는 중");
	_str.push_back("적을 소환하는 중");
	_str.push_back("방을 만드는 중");
	_str.push_back("패턴을 마무리하는 중");
	_str.push_back("준비하세요...");


	_loadingImgIndex = _count = _index = 0;


	_miniMap = IMAGEMANAGER->findImage("miniMapImage");

	brush = CreateSolidBrush(RGB(255, 255, 255));
	oBrush = (HBRUSH)SelectObject(_miniMap->getMemDC(), brush);

	return S_OK;
}

void LoadingScene::release(void)
{
	SelectObject(_miniMap->getMemDC(), oBrush);
	DeleteObject(brush);
}

void LoadingScene::update(void)
{
	if (_tileMap->loadingDone())
	{
		SCENEMANAGER->loadScene("GameScene");

		return;
	}

	_count += 200;
	if (_count % (int)(TILEX * TILEY /_str.size()) < 200)
	{
		_count = 0;
		_index++;
		if (_index >= _str.size())
			_index = _str.size() - 1;
	}
	if (_count % (int)(TILEX * TILEY / _loadingCircle->getMaxFrameX()) < 200)
	{
		_loadingImgIndex++;
		if (_loadingImgIndex >= _loadingCircle->getMaxFrameX())
			_loadingImgIndex = _loadingCircle->getMaxFrameX() - 1;
	}
}

void LoadingScene::render(void)
{
	char str[256];

	string temp = "";

	for (int i = _index, count = 0; i >= 0; --i, count++ )
	{
		temp = _str[_index - count].c_str();
		if (count == 0)
			temp += "...";
		sprintf_s(str, "%s", temp.c_str());
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 200 - count * 25, str, strlen(str));

		if (count >= 5)
			break;
	}

	_loadingCircle->frameRender(getMemDC(), WINSIZEX - _loadingCircle->getFrameWidth() - 50, WINSIZEY - _loadingCircle->getFrameHeight() - 50, _loadingImgIndex, 0);
}
