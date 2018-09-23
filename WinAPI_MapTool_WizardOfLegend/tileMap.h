#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "ObjectCard.h"

class tileMap : public GameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//Ÿ��
	DWORD _attribute[TILEX * TILEY];	//�Ӽ�
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

	//Ÿ�ϸ� �ε�
	void load(const char * fileName);
	void load();

	//Ÿ�� ��������
	tagTile* getTiles() { return _tiles; }
	//�Ӽ� ��������
	DWORD* getAttribute() { return _attribute; }

	tileMap() {}
	~tileMap() {}
};