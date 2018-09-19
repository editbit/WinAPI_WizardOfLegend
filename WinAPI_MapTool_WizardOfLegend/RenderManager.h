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
	HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
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

