#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## LoadItem ## (�ε������ Ŭ����)
//=============================================================
HRESULT LoadItem::init(string keyName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;
	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_SOUND;
	//���� ����ü �ʱ�ȭ
	_soundResource.keyName = keyName;
	_soundResource.soundName = soundName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}


//=============================================================
//	## Loading ## (�ε�Ŭ����)
//=============================================================
HRESULT Loading::init(void)
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	//�ε��� Ŭ���� �ʱ�ȭ
	/*
	_loadingBar = new ProgressBar;
	_loadingBar->init("Texture/Loading/loadingBarFront", "Texture/Loading/loadingBarBack", 100, 430, 600, 20);
	_loadingBar->setGauge(0, 0);
	*/
	//���� ������ �ʱ�ȭ
	_currentGauge = 0;


	return S_OK;
}

void Loading::release(void)
{
	//�ε��� Ŭ���� ����
	/*
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
	*/
}

void Loading::update(void)
{
	//�ε��� Ŭ���� ������Ʈ
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
	//�ε��� �Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE; //���� ��ȯ�ϱ� ���� true�� ������
	}

	LoadItem* item = _vLoadItem[_currentGauge]; //�̹��� �ε��� ������������ ��������

	//���⿡�� LoadItemŬ������ �����͸� ������ addimage, addsound�Ѵ�.
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
	//�� ���� ���� ���� �˾Ƽ�...
	case LOAD_KIND_SOUND:
		{
			tagSoundResource bgm = item->getSoundResource();
			SOUNDMANAGER->addSound(bgm.keyName, bgm.soundName, bgm.bgm, bgm.loop);
		}
		break;
	}

	//switch������ �����͸� �ε��ϰ��ϸ� �ε��� ������ ����
	//��������� ����
	_currentGauge++;

	//�ε��� �̹��� ����
	/*
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	*/

	return 0;
}


