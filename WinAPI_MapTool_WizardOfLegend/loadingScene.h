#pragma once
#include "gameNode.h"
#include "tileMap.h"

class LoadingScene :
	public GameNode
{
	vector<string> _str;
	int _count, _index, _loadingImgIndex;

	string _fileName;
	tileMap *_tileMap;

	Image *_miniMap, *_loadingCircle;

	HBRUSH brush;
	HBRUSH oBrush;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LoadingScene() {}
	~LoadingScene() {}
};

