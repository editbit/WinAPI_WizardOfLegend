#pragma once
#include "gameNode.h"
#include "loading.h"
#include "tileNode.h"

class StartLoadingScene : public GameNode
{
private:
	Loading * _loading;

	Image* _background;
	ProgressBar* _loadingBar;
	Image* _numbers;

	int _count, _index;
	float _height;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//로딩이미지 함수
	void loadingImage();
	//로딩사운드 함수
	void loadingSound();
	//로딩이펙트 함수
	void loadingEffect();


	void loadingObjectImage();

	StartLoadingScene() {}
	~StartLoadingScene() {}
};

