#pragma once
#include "gameNode.h"
#include "tankGameScene.h"
#include "maptoolScene.h"
#include "loadingScene.h"
#include "StartScene.h"
#include "GamePlayScene.h"

//#include "enemyManager.h"
class mainGame : public GameNode
{
private:

public:
	HRESULT init();			//�θ� virtual�̹Ƿ� �ڽ��� �ڵ����� virtual�� �ȴ�.
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

