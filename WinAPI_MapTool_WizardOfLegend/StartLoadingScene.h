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

	//�ε��̹��� �Լ�
	void loadingImage();
	//�ε����� �Լ�
	void loadingSound();
	//�ε�����Ʈ �Լ�
	void loadingEffect();


	void loadingObjectImage();

	StartLoadingScene() {}
	~StartLoadingScene() {}
};

