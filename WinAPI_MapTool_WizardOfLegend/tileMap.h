#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "ObjectCard.h"

class tileMap : public GameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
	DWORD _attribute[TILEX * TILEY];	//속성
	ObjectCard _objectCard;

	RoomList _roomList;
	vector<EnemyInfo> _enemyList;

	int i;

	HANDLE file;
	DWORD read;
public:
	HRESULT init(const char * fileName);
	HRESULT init();
	void release();
	void update();
	void render();

	RoomList& getRoomList() { return _roomList; }
	vector<EnemyInfo>& getEnemyList() { return _enemyList; }

	bool prepareLoading(const char* fileName);
	bool loadingDone();
	bool endLoading();

	//타일맵 로드
	void load(const char * fileName);
	void load();

	//타일 가져오기
	tagTile* getTiles() { return _tiles; }
	//속성 가져오기
	DWORD* getAttribute() { return _attribute; }

	tileMap() {}
	~tileMap() {}
};