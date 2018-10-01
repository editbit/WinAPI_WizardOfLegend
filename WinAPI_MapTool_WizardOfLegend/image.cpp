#include "stdafx.h"
#include "image.h"
#pragma comment (lib, "msimg32.lib")

Image::Image() : _imageInfo(NULL), _fileName(NULL),_isTrans(FALSE), _blendImage(NULL), _transColor(RGB(0, 0, 0)), _stretchImage(NULL) // Image 클래스 멤버변수 초기화
{
}


Image::~Image()
{
}

HRESULT Image::init(int width, int height, bool isTrans, COLORREF transColor)
{
	// 재 초기화 방지용, 이미지 정보에 값이 들어있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd); //윈도우창 dc가져옴

	// 이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //윈도우창 dc와 호환되는 memDC를 생성
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); //_imageInfo->hOBit = (HBITMAP)Sele;//메모리 DC에 비트맵을 담음
	_imageInfo->width = width;
	_imageInfo->height = height;

	_isTrans = isTrans;
	_transColor = transColor;

	// 파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0) //비트맵 정보가 제대로 들어오지 않으면
	{
		this->release(); //릴리즈 해버리고
		return E_FAIL; //리턴 FAIL
	}


	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->redID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	
	// DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor) //이미지 리소스id로 불러옴
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
// 이미지 파일로 초기화
HRESULT Image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor) //이미지 파일명,비트맵폭,비트맵높이,색상제거
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//로테이트 이미지 초기화
	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->redID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName); //문자열 복사함수를 사용해 _fileName에 fileName을 담음

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->redID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 이미지 파일로 초기화 이미지x,y위치값 지정
HRESULT Image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor) //이미지 파일명,렌더할 위치x,y,비트맵폭,비트맵높이,색상제거
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//로테이트 이미지 초기화
	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->redID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->redID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//ADDED
//프레임 이미지 파일로 초기화
HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor) //파일명,bmp폭,bmp높이,프레임갯수x,프레임갯수y,색상제거
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//로테이트 이미지 초기화
	int size;
	(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->redID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->redID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//ADDED
//프레임 이미지 파일로 초기화
HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor) //파일명,렌더할위치x,렌더할위치y,bmp폭,bmp높이,프레임갯수x,프레임갯수y,색상제거
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//로테이트 이미지 초기화
	int size;
	(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->redID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//스트레치 이미지 초기화
	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->redID = 0;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->redID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc); //윈도우창 dc와 호환되는 memDC를 생성
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release(void)
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}

	if (_stretchImage)
	{
		SelectObject(_stretchImage->hMemDC, _stretchImage->hOBit);
		DeleteObject(_stretchImage->hBit);
		DeleteDC(_stretchImage->hMemDC);

		SAFE_DELETE(_stretchImage);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, //메모리DC destX,destY위치의 이미지를 hdc의 0,0위치에 이미지 가로세로 길이만큼 고속복사
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}	
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight) // memDC, 출력할 위치(dest), 복사시작점(sourX,Y), 일부분(sourW,H)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC - memDC
			destX,					//복사될 좌표 시작점 X - hdc의 좌표
			destY,					//복사될 좌표 시작점 Y - hdc의 좌표
			sourWidth,				//복사될 이미지 가로크기 - 
			sourHeight,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC

			sourX, sourY,			//복사 시작지점
			sourWidth,				//복사 영역 가로크기 - 이미지의 sourX기준으로 sourW만큼
			sourHeight,				//복사 영역 세로크기 - 이미지의 sourY기준으로 sourH만큼
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, //메모리DC destX,destY위치의 이미지를 hdc의 0,0위치에 이미지 가로세로 길이만큼 고속복사
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파블렌드를 처음사용하니?
	//알파블렌드를 사용할수 있게 초기화해
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤뒤 알파블랜딩 하니?
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

		//3. 블렌드이미지를 화면에 그린다
		//알파블렌드
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할래?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, //메모리DC destX,destY위치의 이미지를 hdc의 0,0위치에 이미지 가로세로 길이만큼 고속복사
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드를 처음사용하니?
	//알파블렌드를 사용할 수 있도록 초기화해
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤후 알파블렌딩 하니?
	{

		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									//알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할꺼냐?
	{
		//알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{	//알파블렌드를 처음사용하니?
	//알파블렌드를 사용할 수 있도록 초기화해
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤후 알파블렌딩 하니?
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,					//복사될 좌표 시작점 X
			0,					//복사될 좌표 시작점 Y
			sourWidth,				//복사될 이미지 가로크기
			sourHeight,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,			//복사 시작지점
			sourWidth,				//복사 영역 가로크기
			sourHeight,				//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									//알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할꺼냐?
	{
		//알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY) // memDC, 출력할 위치(dest)
{
	if (_isTrans) //배경색 없앨꺼니?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC - memDC
			destX,						//복사될 좌표 시작점 X - hdc의 좌표
			destY,						//복사될 좌표 시작점 Y - hdc의 좌표
			_imageInfo->frameWidth,		//한개 프레임 가로크기 
			_imageInfo->frameHeight,	//한개 프레임 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);				//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY) // memDC, 출력할 위치(dest)
{
	//이미지 예외처리
	//int hp; if(hp < 0) hp = 0; 기억해 hp는 음수값없어

	//현재프레임 좌표가 맥스프레임보다 커지면 일안해
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC - memDC
			destX,						//복사될 좌표 시작점 X - hdc의 좌표
			destY,						//복사될 좌표 시작점 Y - hdc의 좌표
			_imageInfo->frameWidth,		//복사될 1 프레임당 가로크기 
			_imageInfo->frameHeight,	//복사될 1 프레임당 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX *_imageInfo->frameWidth,	//복사 시작지점, 출력할 프레임 시작지점(인덱스처럼 사용)
			_imageInfo->currentFrameY *_imageInfo->frameHeight,	//복사 시작지점
			_imageInfo->frameWidth,		//복사 영역 가로크기 (1프레임크기)
			_imageInfo->frameHeight,	//복사 영역 세로크기 (1프레임크기)
			_transColor);				//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{			
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);	//currentFrameX * frameWidth ->가로세로*인덱스
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC - memDC
			destX,						//복사될 좌표 시작점 X - hdc의 좌표
			destY,						//복사될 좌표 시작점 Y - hdc의 좌표
			sourWidth,		//복사될 1 프레임당 가로크기 
			sourHeight,	//복사될 1 프레임당 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX *_imageInfo->frameWidth + sourX,	//복사 시작지점, 출력할 프레임 시작지점(인덱스처럼 사용)
			_imageInfo->currentFrameY *_imageInfo->frameHeight + sourY,	//복사 시작지점
			sourWidth,		//복사 영역 가로크기 (1프레임크기)
			sourHeight,	//복사 영역 세로크기 (1프레임크기)
			_transColor);				//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth + sourX,
			_imageInfo->currentFrameY * _imageInfo->frameHeight + sourY, SRCCOPY);	//currentFrameX * frameWidth ->가로세로*인덱스
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(알파렌더-이미지잘라서붙이기)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void Image::stretchRender(HDC hdc, int destX, int destY, float scale)
{
	_stretchImage->width = _imageInfo->width * scale;
	_stretchImage->height = _imageInfo->height * scale;

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		StretchBlt(hdc, destX, destY, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void Image::stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	_stretchImage->width = _imageInfo->width * scale;
	_stretchImage->height = _imageInfo->height * scale;
	_stretchImage->frameWidth = _stretchImage->width / (_imageInfo->maxFrameX + 1);
	_stretchImage->frameHeight = _stretchImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,							//복사할 장소의 DC
			destX,							//복사될 좌표 시작점 X
			destY,							//복사될 좌표 시작점 Y
			_stretchImage->frameWidth,		//복사될 이미지 가로크기
			_stretchImage->frameHeight,		//복사될 이미지 세로크기
			_stretchImage->hMemDC,			//복사될 대상 DC
			0, 0,							//복사 시작지점
			_stretchImage->frameWidth,		//복사 영역 가로크기
			_stretchImage->frameHeight,		//복사 영역 세로크기
			_transColor);					//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		StretchBlt(hdc, destX, destY, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY)
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,                    //복사할 장소의 DC
			0,                        //복사될 좌표 시작점 X
			0,                        //복사될 좌표 시작점 Y
			_imageInfo->frameWidth,                                    //복사될 이미지 가로크기
			_imageInfo->frameHeight,                                //복사될 이미지 세로크기
			_imageInfo->hMemDC,                                        //복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,        //X축 복사 시작 지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,    //Y축 복사 시작 지점
			_imageInfo->frameWidth,                                    //복사 영역 가로크기
			_imageInfo->frameHeight,                                //복사 영역 세로크기
			_transColor);            //복사할때 제외할 색상 (마젠타)

									 //3. 블렌드이미지를 화면에 그린다
									 // 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void Image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			rPoint[i].x += centerX / 2;
			rPoint[i].y += centerY / 2;
		}
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void Image::rotateFrameRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->currentFrameX, _imageInfo->currentFrameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void Image::rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, currentFrameX, currentFrameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}


void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
void Image::aniAlphaRender(HDC hdc, int destX, int destY, Animation * ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

