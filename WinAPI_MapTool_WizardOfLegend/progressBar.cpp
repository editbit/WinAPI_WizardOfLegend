#include "stdafx.h"
#include "progressBar.h"

HRESULT ProgressBar::init(const char * frontImageKey, const char * backImageKey, int x, int y, int width, int height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;
	//체력바 가로, 세로길이 초기화
	_width = width;
	_height = height;
	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//키값으로 이미지이름(~.bmp)으로 바로 초기화
	char frontImage[128];
	char backImage[128];
	//메모리 깔끔하게 밀어주기
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp로 만들기
	//키, 파일이름 IMAGEMANAGER->ADDIMAGE("background", "background.bmp",,,,)
	_stprintf_s(frontImage, "Texture/PrograssBar/%s.bmp", frontImageKey);
	_stprintf_s(backImage, "Texture/PrograssBar/%s.bmp", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));
	

	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void ProgressBar::render(void)
{
	//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_progressBarBack->render(UIMANAGER->getUIDC(), _rcProgress.left, _y);
	//앞에 보여지는 체력바 이미지
	_progressBarFront->render(UIMANAGER->getUIDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

void ProgressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}
