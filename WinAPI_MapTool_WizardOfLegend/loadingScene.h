#pragma once
#include "gameNode.h"
#include "tileMap.h"

class LoadingScene :
	public GameNode
{
	string _str[6];
	int _count, _index;

	string _fileName;
	tileMap *_tileMap;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LoadingScene() {}
	~LoadingScene() {}
};

