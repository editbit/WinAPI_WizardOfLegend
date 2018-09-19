#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## ImageManager ## (이미지 매니져)
//=============================================================
//ADDED 이미지매니저에서 초기화,map 컨테이너에 담기, 해제까지 담당

class ImageManager : public SingletonBase <ImageManager>
{
private:
	//ADDED 데이터,변수들을 담기 위해서는 자료형(데이터형태)이 필요한데 이런 타입을 내가 다른이름으로 선언해서 그 이름으로 사용하겠다.
	/*typedef int INT;
	int a;
	INT b;
	vector<int>
	*/
	typedef map<string, Image*> mapImageList;				// 맵으로 만든 이미지목록
	typedef map<string, Image*>::iterator mapImageIter;		// 맵으로 만든 이미지목록의 반복자
	
	mapImageList _mImageList;		// 실제 이미지클래스를 담을 STL맵
	// (typedef덕분에) map<string, Image*> _mImageList;를 mapImageList _mImageList;로 쓸수 있다.

public:
	//이미지 매니져 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	// 빈 비트맵으로 초기화
	Image* addImage(string strKey, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화 (주로 사용)
	Image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화 (주로 사용), 초기화할때 렌더할 위치(float)지정
	Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 파일로 초기화 (주사용)
	Image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	// 프레임 이미지 파일로 초기화 (주사용), 초기화할때 렌더할 위치(float)지정
	Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	// 이미지 키값으로 찾기
	Image* findImage(string strKey);
	// 이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll ();

// 이제 입력받은 키값으로 find해서 쓰자
//=============================================================
//	## 일반렌더 ## 
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0); //내가 원하는 좌표(dest)에 렌더
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //이미지의 일부분만 렌더(비트맵의 sour좌표부분만)

//=============================================================
//	## 알파렌더 ## 
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## 프레임렌더 ## 
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//=============================================================
//	## 스트레치렌더 ## (이미지 스케일링)
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);
//=============================================================
//	## 알파프레임렌더 ## (상균)
//=============================================================
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//ADDED : 프레임메이커
//=============================================================
//	## 프레임메이커 ## 
//=============================================================
	bool frameMake(Image * bmp, int &count, int &index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	bool frameMake(string strKey, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	
	//ImageManager();
	//~ImageManager();
};
