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

// 빈 비트맵으로 초기화
Image * ImageManager::addImage(string strKey, int width, int height, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지않고 바로 리턴
	if (img) return img;

	// 없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->init(width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//맵에 담아야 나중에 키값으로 접근가능
	/* STL 맵의 핵심 */
	// 키, 값을 잊지 말도록 해
	// 첫번째 = 키 -> first
	// 두번째 = 값(밸류) ->second;
	//데이터를 추가할 때 키,밸류를 "쌍(pair)"으로 집어넣어야 한다.
	//pair, make_pair를 사용해서 추가한다.
	//insert사용 앞에넣든 뒤에넣든 레드블랙트리 구조로 정렬해버리므로 pushback 등의 자료추가타입이 없이 insert를 사용
	//_mImageList.insert(pair<string, Image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

// 이미지 파일로 초기화 (주로 사용)
Image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 이미지 파일로 초기화 (주로 사용), 초기화할때 렌더할 위치(float)지정
Image * ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 프레임 이미지 파일로 초기화 (주사용)
Image * ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 프레임 이미지 파일로 초기화 (주사용), 초기화할때 렌더할 위치(float)지정
Image * ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//STL 맵안에 이미지를 담아놓기
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 이미지 키값으로 찾기
Image * ImageManager::findImage(string strKey)
{
	// map 내부에 find라는 함수가 있다. 반복자를 통해 사용할 수 있다.
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);
	// _mImageList를 strKey로 검색해서 mapImageIter key에 대입

	//검색한 키를 찾았다면 이미지클래스 리턴
	// begin은 시작 end는 끝 find함수는 begin부터 end까지 검색하여 검색한 키가 없으면 end가 나오게 되어있다.
	if (key != _mImageList.end())
	{
		return key->second;		// 이미지는 second에 담겨있다.
	}

	//검색한 키로 end까지 이미지를 못찾았다면 NULL;
	return NULL;
}


// 이미지 키값으로 삭제
BOOL ImageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지클래스 삭제
	if (key != _mImageList.end())
	{
		//이미지 해제 (이미지 클래스에서 릴리즈를 불러옴)
		key->second->release();
		//메모리 해제 (메인게임의 SAFE_DELETE를 대체함)
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//이미지 전체 삭제
BOOL ImageManager::deleteAll()
{
	//맵 전체를 돌면서 하나씩 전부 지운다
	//반복자(iter)를 begin부터 시작해서 삭제하자
	mapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	//반복자(iter)를 엔드까지 반복문하면서
	for (; iter != _mImageList.end();)
	{
		//second(이미지)가 NULL이 아니면 이미지가 있는것이니까 삭제하자
		//이미지가 있으니 이미지 클래스 삭제
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else//이미지가 없으면
		{
			++iter; //이미지가 없으면 반복자를 다음것으로 증가시켜라
		}
	}

	//안전을 위해
	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}

//=============================================================
//	## 일반렌더 ## 
//=============================================================
void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//=============================================================
//	## 알파렌더 ## 
//=============================================================
void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//=============================================================
//	## 프레임렌더 ## 
//=============================================================
void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->stretchRender(hdc, destX, destY, scale);
}

void ImageManager::stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수로 렌더시키면 됨
	Image* img = findImage(strKey);
	if (img) img->stretchFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}

void ImageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

//ADDED : 프레임 인덱스 좌우로 움직여주는 함수
bool ImageManager::frameMake(Image * bmp, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir)
{
	if (renderDir)
	{
		//왼쪽방향으로 렌더
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
	else //오른쪽 방향으로 렌더
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
		//왼쪽방향으로 렌더
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
	else //오른쪽 방향으로 렌더
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