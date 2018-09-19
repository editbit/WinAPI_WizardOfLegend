#pragma once
#include "singletonBase.h"

class BackgroundActor;
class Actor;
class tileMap;

class RenderManager : public SingletonBase<RenderManager>
{
private:
	multimap<float, Actor *> renderList;
	multimap<float, BackgroundActor *> backgroundList;

	tileMap * _tileMap;
public:
	HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	void release();
	void render(HDC hdc);
	void backgroundRender(HDC hdc);
	
	void setLinkTileMap(tileMap *tiles) { _tileMap = tiles; }

	void addRender(float z, Actor *name);
	//void addActor(float z, Actor *name);
	void addBackground(float z, BackgroundActor *backActor);
	void clearBackground();


	RenderManager() :_tileMap(NULL) {}
	~RenderManager() {}
};

