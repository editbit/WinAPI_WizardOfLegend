#pragma once
#include "gameNode.h"
#include "progressBar.h"
//=============================================================
//	## LoadItem ## (로드아이템 클래스)
//=============================================================

//로드아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//빈비트맵 이미지
	LOAD_KIND_IMAGE_1,			//일반 이미지
	LOAD_KIND_IMAGE_2,			//일반 이미지(위치좌표)
	LOAD_KIND_FRAMEIMAGE_0,		//프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,		//프레임 이미지(위치좌표)
	LOAD_KIND_SOUND,			//사운드
	LOAD_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			//이미지 키값
	const char* fileName;	//파일이름
	int x, y;				//위치좌표
	int width, height;		//가로, 세로크기
	int frameX, frameY;		//프레임 x, y
	bool trans;				//배경지울꺼임?
	COLORREF transColor;	//어떤색으로?
};

//사운드 리소스 구조체
struct tagSoundResource
{
	string keyName;			//사운드 키값
	string soundName;		//파일이름
	bool bgm;				//bgm이니?
	bool loop;				//loop할래?
};

//LoadItem 클래스로 로딩할 이미지,사운드의 데이터값 (파일이름,사이즈,마젠타 등)
class LoadItem 
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;

public:
	//빈 비트맵으로 초기화
	HRESULT init(string keyName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화 (주사용)
	HRESULT init(string keyName, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 초기화 (주사용)
	HRESULT init(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//사운드 파일로 초기화
	HRESULT init(string keyName, string soundName, bool bgm = false, bool loop = false);

	//로딩아이템 종류 가져오기
	LOAD_KIND getLoadingKind() { return _kind; }
	//이미지 리소스 가져오기
	tagImageResource getImageResource() { return _imageResource; }
	tagSoundResource getSoundResource() { return _soundResource; }

	LoadItem() {}
	~LoadItem() {}
};

//=============================================================
//	## Loading ## (로딩클래스)
//=============================================================
class Loading : public GameNode
{
private:
	//로드아이템 클래스를 담을 벡터 및 반복자
	typedef vector<LoadItem*> arrLoadItem;
	typedef vector<LoadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//이곳에 로딩화면에서 사용할 이미지와 로딩바 수정할것!!!
	int _currentGauge;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//빈 비트맵으로 로딩
	void loadImage(string keyName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 로딩 (주사용)
	void loadImage(string keyName, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 로딩 (주사용)
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	//사운드 파일로 로딩
	void loadSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	/*중요함*/
	//로딩완료 됐냐?(로딩완료후 화면전환)
	BOOL loadingDone();

	//로드아이템 클래스를 담은 벡터 가져오기
	arrLoadItem getLoadItem() { return _vLoadItem; }
	int getCurrnetGauge() { return _currentGauge; }

	Loading() {}
	~Loading() {}
};

