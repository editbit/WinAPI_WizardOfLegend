#include "stdafx.h"
#include "mainGame.h"

float _soundVolume;
float _effectVolume;
Image * cursor;
string collisionKey[2] = { "�浹1", "�浹2" };


//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	GameNode::init(TRUE);

	//���ڹ����
	SetBkMode(getMemDC(), TRANSPARENT);

	_tileMap = new tileMap;
	//_tileMap->init();
	SAVEDATA->setTileMap(_tileMap);
	SAVEDATA->setMapName("Stage/Stage0.map");

	_soundVolume = INIDATA->loadDataFloat("Data/setting", "Sound", "master");
	_effectVolume = INIDATA->loadDataFloat("Data/setting", "Sound", "effect");

	//�̰����� �ʱ�ȭ�� �Ѵ�
	SCENEMANAGER->addScene("Ÿ�ϸ�", new maptoolScene);
	SCENEMANAGER->addScene("��ũ", new tankGameScene);
	SCENEMANAGER->addScene("StartLoadingScene", new StartLoadingScene);
	SCENEMANAGER->addScene("StartScene", new StartScene);
	SCENEMANAGER->addScene("GameScene", new GamePlayScene);
	SCENEMANAGER->addScene("LoadingScene", new LoadingScene);

	SCENEMANAGER->loadScene("StartLoadingScene");

	//cursor = IMAGEMANAGER->addImage("CURSOR", "Texture/UI/cursor_30x42.bmp", 30, 42, true, RGB(255, 0, 255));

	
	return S_OK;
}

//=============================================================
//	## ���� ## release()
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
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	UIMANAGER->clear();

	SCENEMANAGER->update();

	EFFECTMANAGER->update();

}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render() //���� �̹����Ŵ����� �߰��߰� GameNode�� �����ؼ� HDC�Ű����� ������ �ʿ䰡 ����.
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
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
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}