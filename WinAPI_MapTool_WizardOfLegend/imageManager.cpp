#include "stdafx.h"
#include "imageManager.h"

HRESULT ImageManager::init()
{
	return S_OK;
}

void ImageManager::release()
{
	deleteAll();
}

// �� ��Ʈ������ �ʱ�ȭ
Image * ImageManager::addImage(string strKey, int width, int height, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� �������ʰ� �ٷ� ����
	if (img) return img;

	// ������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->init(width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//�ʿ� ��ƾ� ���߿� Ű������ ���ٰ���
	/* STL ���� �ٽ� */
	// Ű, ���� ���� ������ ��
	// ù��° = Ű -> first
	// �ι�° = ��(���) ->second;
	//�����͸� �߰��� �� Ű,����� "��(pair)"���� ����־�� �Ѵ�.
	//pair, make_pair�� ����ؼ� �߰��Ѵ�.
	//insert��� �տ��ֵ� �ڿ��ֵ� �����Ʈ�� ������ �����ع����Ƿ� pushback ���� �ڷ��߰�Ÿ���� ���� insert�� ���
	//_mImageList.insert(pair<string, Image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���)
Image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL �ʾȿ� �̹����� ��Ƴ���
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
Image * ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL �ʾȿ� �̹����� ��Ƴ���
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
Image * ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL �ʾȿ� �̹����� ��Ƴ���
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
Image * ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL �ʾȿ� �̹����� ��Ƴ���
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// �̹��� Ű������ ã��
Image * ImageManager::findImage(string strKey)
{
	// map ���ο� find��� �Լ��� �ִ�. �ݺ��ڸ� ���� ����� �� �ִ�.
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);
	// _mImageList�� strKey�� �˻��ؼ� mapImageIter key�� ����

	//�˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	// begin�� ���� end�� �� find�Լ��� begin���� end���� �˻��Ͽ� �˻��� Ű�� ������ end�� ������ �Ǿ��ִ�.
	if (key != _mImageList.end())
	{
		return key->second;		// �̹����� second�� ����ִ�.
	}

	//�˻��� Ű�� end���� �̹����� ��ã�Ҵٸ� NULL;
	return NULL;
}


// �̹��� Ű������ ����
BOOL ImageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		//�̹��� ���� (�̹��� Ŭ�������� ����� �ҷ���)
		key->second->release();
		//�޸� ���� (���ΰ����� SAFE_DELETE�� ��ü��)
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//�̹��� ��ü ����
BOOL ImageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �ϳ��� ���� �����
	//�ݺ���(iter)�� begin���� �����ؼ� ��������
	mapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	//�ݺ���(iter)�� ������� �ݺ����ϸ鼭
	for (; iter != _mImageList.end();)
	{
		//second(�̹���)�� NULL�� �ƴϸ� �̹����� �ִ°��̴ϱ� ��������
		//�̹����� ������ �̹��� Ŭ���� ����
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else//�̹����� ������
		{
			++iter; //�̹����� ������ �ݺ��ڸ� ���������� �������Ѷ�
		}
	}

	//������ ����
	//�� ��ü�� ����
	_mImageList.clear();

	return TRUE;
}

//=============================================================
//	## �Ϲݷ��� ## 
//=============================================================
void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//=============================================================
//	## ���ķ��� ## 
//=============================================================
void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//=============================================================
//	## �����ӷ��� ## 
//=============================================================
void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->stretchRender(hdc, destX, destY, scale);
}

void ImageManager::stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	//�̹����� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� ������Ű�� ��
	Image* img = findImage(strKey);
	if (img) img->stretchFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}

void ImageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

//ADDED : ������ �ε��� �¿�� �������ִ� �Լ�
bool ImageManager::frameMake(Image * bmp, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir)
{
	if (renderDir)
	{
		//���ʹ������� ����
		count++;
		bmp->setFrameY(frameY1);
		if (count % cooltime == 0)
		{
			index--;
			if (index < 0)
			{
				index = bmp->getMaxFrameX();
				return true;
			}
			bmp->setFrameX(index);
		}
	}
	else //������ �������� ����
	{
		count++;
		bmp->setFrameY(frameY2);
		if (count % cooltime == 0)
		{
			index++;
			if (index > bmp->getMaxFrameX())
			{
				index = 0;
				return true;
			}
			bmp->setFrameX(index);
		}
	}
	return false;
}

bool ImageManager::frameMake(string strKey, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir)
{
	if (renderDir)
	{
		//���ʹ������� ����
		count++;
		findImage(strKey)->setFrameY(frameY1);
		if (count % cooltime == 0)
		{
			index--;
			if (index < 0)
			{
				index = findImage(strKey)->getMaxFrameX();
				return true;
			}
			findImage(strKey)->setFrameX(index);
		}
	}
	else //������ �������� ����
	{
		count++;
		findImage(strKey)->setFrameY(frameY2);
		if (count % cooltime == 0)
		{
			index++;
			if (index > findImage(strKey)->getMaxFrameX())
			{
				index = 0;
				return true;
			}
			findImage(strKey)->setFrameX(index);
		}
	}
	return false;
}