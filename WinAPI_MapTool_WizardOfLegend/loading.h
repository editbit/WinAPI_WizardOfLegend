#pragma once
#include "gameNode.h"
#include "progressBar.h"
//=============================================================
//	## LoadItem ## (�ε������ Ŭ����)
//=============================================================

//�ε������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//���Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,			//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,			//�Ϲ� �̹���(��ġ��ǥ)
	LOAD_KIND_FRAMEIMAGE_0,		//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,		//������ �̹���(��ġ��ǥ)
	LOAD_KIND_SOUND,			//����
	LOAD_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;			//�̹��� Ű��
	const char* fileName;	//�����̸�
	int x, y;				//��ġ��ǥ
	int width, height;		//����, ����ũ��
	int frameX, frameY;		//������ x, y
	bool trans;				//������ﲨ��?
	COLORREF transColor;	//�������?
};

//���� ���ҽ� ����ü
struct tagSoundResource
{
	string keyName;			//���� Ű��
	string soundName;		//�����̸�
	bool bgm;				//bgm�̴�?
	bool loop;				//loop�ҷ�?
};

//LoadItem Ŭ������ �ε��� �̹���,������ �����Ͱ� (�����̸�,������,����Ÿ ��)
class LoadItem 
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;

public:
	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT init(string keyName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT init(string keyName, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT init(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//���� ���Ϸ� �ʱ�ȭ
	HRESULT init(string keyName, string soundName, bool bgm = false, bool loop = false);

	//�ε������� ���� ��������
	LOAD_KIND getLoadingKind() { return _kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource() { return _imageResource; }
	tagSoundResource getSoundResource() { return _soundResource; }

	LoadItem() {}
	~LoadItem() {}
};

//=============================================================
//	## Loading ## (�ε�Ŭ����)
//=============================================================
class Loading : public GameNode
{
private:
	//�ε������ Ŭ������ ���� ���� �� �ݺ���
	typedef vector<LoadItem*> arrLoadItem;
	typedef vector<LoadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//�̰��� �ε�ȭ�鿡�� ����� �̹����� �ε��� �����Ұ�!!!
	int _currentGauge;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� ��Ʈ������ �ε�
	void loadImage(string keyName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ε� (�ֻ��)
	void loadImage(string keyName, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ε� (�ֻ��)
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//���� ���Ϸ� �ε�
	void loadSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	/*�߿���*/
	//�ε��Ϸ� �Ƴ�?(�ε��Ϸ��� ȭ����ȯ)
	BOOL loadingDone();

	//�ε������ Ŭ������ ���� ���� ��������
	arrLoadItem getLoadItem() { return _vLoadItem; }
	int getCurrnetGauge() { return _currentGauge; }

	Loading() {}
	~Loading() {}
};
