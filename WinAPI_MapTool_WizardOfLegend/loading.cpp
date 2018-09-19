#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## LoadItem ## (로드아이템 클래스)
//=============================================================
HRESULT LoadItem::init(string keyName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, string soundName, bool bgm, bool loop)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_SOUND;
	//사운드 구조체 초기화
	_soundResource.keyName = keyName;
	_soundResource.soundName = soundName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}


//=============================================================
//	## Loading ## (로딩클래스)
//=============================================================
HRESULT Loading::init(void)
{
	//로딩화면 백그라운드 이미지 초기화
	//로딩바 클래스 초기화
	/*
	_loadingBar = new ProgressBar;
	_loadingBar->init("Texture/Loading/loadingBarFront", "Texture/Loading/loadingBarBack", 100, 430, 600, 20);
	_loadingBar->setGauge(0, 0);
	*/
	//현재 게이지 초기화
	_currentGauge = 0;


	return S_OK;
}

void Loading::release(void)
{
	//로딩바 클래스 해제
	/*
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
	*/
}

void Loading::update(void)
{
	//로딩바 클래스 업데이트
	//_loadingBar->update();

}

void Loading::render(void)
{
	


}

void Loading::loadImage(string keyName, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void Loading::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void Loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void Loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void Loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void Loading::loadSound(string keyName, string soundName, bool bgm, bool loop)
{
	LoadItem* item = new LoadItem;
	item->init(keyName, soundName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL Loading::loadingDone()
{
	//로딩이 완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE; //씬을 전환하기 위해 true를 리턴함
	}

	LoadItem* item = _vLoadItem[_currentGauge]; //이번에 로딩할 데이터정보를 가져오자

	//여기에서 LoadItem클래스의 데이터를 가지고 addimage, addsound한다.
	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_2:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	//곧 사운드 배우고 난후 알아서...
	case LOAD_KIND_SOUND:
		{
			tagSoundResource bgm = item->getSoundResource();
			SOUNDMANAGER->addSound(bgm.keyName, bgm.soundName, bgm.bgm, bgm.loop);
		}
		break;
	}

	//switch문으로 데이터를 로드하고하면 로딩바 게이지 증가
	//현재게이지 증가
	_currentGauge++;

	//로딩바 이미지 변경
	/*
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	*/

	return 0;
}


