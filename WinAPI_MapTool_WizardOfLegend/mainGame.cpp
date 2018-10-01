#include "stdafx.h"
#include "mainGame.h"

float _soundVolume;
float _effectVolume;
Image * cursor;
string collisionKey[2] = { "충돌1", "충돌2" };


//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	GameNode::init(TRUE);

	//글자배경모드
	SetBkMode(getMemDC(), TRANSPARENT);

	_tileMap = new tileMap;
	//_tileMap->init();
	SAVEDATA->setTileMap(_tileMap);
	SAVEDATA->setMapName("Stage/Stage0.map");

	_soundVolume = INIDATA->loadDataFloat("Data/setting", "Sound", "master");
	_effectVolume = INIDATA->loadDataFloat("Data/setting", "Sound", "effect");

	//이곳에서 초기화를 한다
	SCENEMANAGER->addScene("타일맵", new maptoolScene);
	SCENEMANAGER->addScene("탱크", new tankGameScene);
	SCENEMANAGER->addScene("StartLoadingScene", new StartLoadingScene);
	SCENEMANAGER->addScene("StartScene", new StartScene);
	SCENEMANAGER->addScene("GameScene", new GamePlayScene);
	SCENEMANAGER->addScene("LoadingScene", new LoadingScene);

	SCENEMANAGER->loadScene("StartLoadingScene");

	//cursor = IMAGEMANAGER->addImage("CURSOR", "Texture/UI/cursor_30x42.bmp", 30, 42, true, RGB(255, 0, 255));

	
	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	GameNode::release();

	_tileMap->release();
	SAFE_DELETE(_tileMap);

	INIDATA->addData("Sound", "master", to_string(_soundVolume).c_str());
	INIDATA->addData("Sound", "effect", to_string(_effectVolume).c_str());
	INIDATA->saveINI("Data/setting");
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	UIMANAGER->clear();

	SCENEMANAGER->update();

	EFFECTMANAGER->update();

}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render() //이제 이미지매니저를 추가했고 GameNode를 수정해서 HDC매개변수 가져올 필요가 없다.
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	SCENEMANAGER->render();
	
	EFFECTMANAGER->render();
	
	UIMANAGER->render(getMemDC());
	
	TIMEMANAGER->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[20];
		sprintf_s(str, "%d %d", _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());
		TextOut(getMemDC(), 30, 100, str, strlen(str));
	}

	//cursor->render(getMemDC(), _ptMouse.x, _ptMouse.y);

//=============================================================	
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}