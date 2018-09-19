#pragma once
#include "animation.h"
//=============================================================
//	## Image ## (앞으로 계속 업데이트 된다)
//=============================================================
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		// 리소스로 로딩
		LOAD_FILE,				// 파일로 로딩
		LOAD_EMPTY,				// 빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage		// 타입 디파인 구조체
	{
		DWORD		redID;					// 리소스 ID
		HDC			hMemDC;					// 백버퍼로 사용할 메모리DC
		HBITMAP		hBit;					// 비트맵
		HBITMAP		hOBit;					// 올드비트맵
		float		x;						// 이미지 x좌표 - 화면에 띄울 위치
		float		y;						// 이미지 y좌표 - 화면에 띄울 위치
		int			width;					// 이미지 가로크기
		int			height;					// 이미지 세로크기
		int			currentFrameX;			// 현재 프레임 x		(한개 이미지 가지고 개별프레임으로 돌아가는걸 만들수 있다)(봄버맨폭탄)   
		int			currentFrameY;			// 현재 프레임 y
		int			maxFrameX;				//최대 x프레임 갯수
		int			maxFrameY;				//최대 y프레임 갯수
		int			frameWidth;				// 1프레임당 가로길이
		int			frameHeight;			// 1프레임당 세로길이
		BYTE		loadType;				// 이미지 로드타입

		tagImage()					// 구조체 생성자 -> 초기화
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;	// 태그 이미지와 같은 의미 포인터를 넘겨줄땐 LP~를 사용하면 된다

private:
	LPIMAGE_INFO	_imageInfo;		// 이미지 정보
	CHAR*			_fileName;		// 이미지 이름
	BOOL			_isTrans;		// 배경색 없음? (마젠타)
	COLORREF		_transColor;	// 배경색 없을 RGB ( 마젠타 = RGB(255.0.255) )

	LPIMAGE_INFO	_blendImage;	// 알파블렌드 이미지		알파블렌딩
	BLENDFUNCTION	_blendFunc;		// 알파블랜드 기능 		memDC의 이미지를 blendDC로 옮기고 그걸 hdc로 옮김

	LPIMAGE_INFO	_stretchImage;	//스트레치이미지
	LPIMAGE_INFO	_rotateImage;	//로테이트이미지

public:
	Image();
	~Image();

	// 빈 비트맵으로 초기화
	HRESULT init(int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 빈 비트맵으로 초기화
	// 이미지 리소스로 초기화(사용안함)
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0)); // 디폴트 매개변수
	// 이미지 파일로 초기화 (주로 사용)
	HRESULT init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화 (주로 사용), 초기화할때 렌더할 위치(float)지정
	HRESULT init(const char* fileName, float x, float y, int width, int height,bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 파일로 초기화 (주사용)
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	// 프레임 이미지 파일로 초기화 (주사용), 초기화할때 렌더할 위치(float)지정
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	// 알파블렌드 초기화
	HRESULT initForAlphaBlend(void);

	//해제
	void release(void);

//=============================================================
//	## 일반렌더 ## 
//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0); //내가 원하는 좌표(dest)에 렌더
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //이미지의 일부분만 렌더(비트맵의 sour좌표부분만)

//=============================================================
//	## 알파렌더 ## 
//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## 프레임렌더 ## 
//=============================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int currentFrameX, int currentFrameY);

//=============================================================
//	## 루프렌더 ##
//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//=============================================================
//	## 스트레치렌더 ## (이미지 스케일링)
//=============================================================
	void stretchRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

//=============================================================
//	## 알파프레임렌더 ## (made by 상균)
//=============================================================
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//=============================================================
//	## 로테이트렌더 ## (이미지 회전)
//=============================================================
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);
	
//=============================================================
//	## 애니렌더 ## 
//=============================================================
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha);


//=============================================================
//	## inline ## (인라인 함수들 - 겟터, 셋터)
//=============================================================

	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 x좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x =x; }
	//이미지 y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y =y; }
	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	//바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->width,(int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->frameWidth,(int)_imageInfo->y + _imageInfo->frameHeight };
		return rc;
	}
	
	// 프레임 x
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)	//맥스프레임을 넘지않게해준다.
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임 y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)	//맥스프레임을 넘지않게해준다.
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 한프레임당 가로, 세로크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//맥스프레임 갯수 x(가로), y(세로)
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


};

