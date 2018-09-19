#pragma once
#include "gameNode.h"
#include "loading.h"
#include "tileNode.h"

class LoadingScene : public GameNode
{
private:
	Loading * _loading;

	Image* _background;
	ProgressBar* _loadingBar;
	Image* _numbers;

	int _count, _index;
	float _height;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�ε��̹��� �Լ�
	void loadingImage();
	//�ε����� �Լ�
	void loadingSound();
	//�ε�����Ʈ �Լ�
	void loadingEffect();


	void loadingObjectImage();

	LoadingScene() {}
	~LoadingScene() {}
};

