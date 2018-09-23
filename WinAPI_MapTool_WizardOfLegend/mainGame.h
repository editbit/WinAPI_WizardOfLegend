#pragma once
#include "gameNode.h"
#include "tankGameScene.h"
#include "maptoolScene.h"
#include "StartLoadingScene.h"
#include "StartScene.h"
#include "GamePlayScene.h"
#include "LoadingScene.h"

//#include "enemyManager.h"
class mainGame : public GameNode
{
private:
	tileMap *_tileMap;

public:
	HRESULT init();			//부모가 virtual이므로 자식은 자동으로 virtual이 된다.
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

