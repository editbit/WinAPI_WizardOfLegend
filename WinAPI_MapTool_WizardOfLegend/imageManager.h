#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## ImageManager ## (�̹��� �Ŵ���)
//=============================================================
//ADDED �̹����Ŵ������� �ʱ�ȭ,map �����̳ʿ� ���, �������� ���

class ImageManager : public SingletonBase <ImageManager>
{
private:
	//ADDED ������,�������� ��� ���ؼ��� �ڷ���(����������)�� �ʿ��ѵ� �̷� Ÿ���� ���� �ٸ��̸����� �����ؼ� �� �̸����� ����ϰڴ�.
	/*typedef int INT;
	int a;
	INT b;
	vector<int>
	*/
	typedef map<string, Image*> mapImageList;				// ������ ���� �̹������
	typedef map<string, Image*>::iterator mapImageIter;		// ������ ���� �̹�������� �ݺ���
	
	mapImageList _mImageList;		// ���� �̹���Ŭ������ ���� STL��
	// (typedef���п�) map<string, Image*> _mImageList;�� mapImageList _mImageList;�� ���� �ִ�.

public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init();
	//�̹��� �Ŵ��� ����
	void release();

	// �� ��Ʈ������ �ʱ�ȭ
	Image* addImage(string strKey, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���)
	Image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	Image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	// �̹��� Ű������ ã��
	Image* findImage(string strKey);
	// �̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll ();

// ���� �Է¹��� Ű������ find�ؼ� ����
//=============================================================
//	## �Ϲݷ��� ## 
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0); //���� ���ϴ� ��ǥ(dest)�� ����
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //�̹����� �Ϻκи� ����(��Ʈ���� sour��ǥ�κи�)

//=============================================================
//	## ���ķ��� ## 
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## �����ӷ��� ## 
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//=============================================================
//	## ��Ʈ��ġ���� ## (�̹��� �����ϸ�)
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);
//=============================================================
//	## ���������ӷ��� ## (���)
//=============================================================
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//ADDED : �����Ӹ���Ŀ
//=============================================================
//	## �����Ӹ���Ŀ ## 
//=============================================================
	bool frameMake(Image * bmp, int &count, int &index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	bool frameMake(string strKey, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	
	//ImageManager();
	//~ImageManager();
};
