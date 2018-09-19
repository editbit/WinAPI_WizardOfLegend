#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "TerrainCard.h"
#include "ObjectCard.h"
#include "EnemyCard.h"


enum CARD_TYPE
{
	TERRAIN_CARD, OBJECT_CARD, ENEMY_CARD
};

struct DragInfo
{
	POINT tile;
	bool isDragged;
};


class maptoolScene : public GameNode
{
private:
	int _enemyCount;
	EnemyInfo _enemyList[TILEX * TILEY];

	tagTile _tiles[TILEX * TILEY];	//왼쪽화면 타일(총 400개)
	//tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽화면 타일(총 160개)
	tagCurrentTile _currentTile;	//현재타일

	ObjectCard _objectCard;
	TerrainCard _terrainCard;
	EnemyCard _enemyCard;

	MaptoolCard * _currentCard;
	Image * _cardDeck;
	RECT _cardDeckRect;
	POINT _cardPos;

									//버튼 5개(세이브, 로드, 지형, 오브젝트, 지우개)
	RECT _rcSave, _rcLoad, _rcTerrain, _rcObject, _rcEraser, _rcEnemy;
	CTRL _ctrlSelect;
	POINT _camPos, _clickPos, _mouseFromCard;


	int _currentSampleTile;

	int _currentDrawNum;

	DragInfo _draggedInfo[TILEX * TILEY];
	bool _isDrag, _isSelect, _checkActive;

	Image * _tileImg, *_sampleTileImg;

	Image * _tileImg2[3];

	HBRUSH brush;
	HBRUSH oBrush;
	HPEN pen;
	HPEN oPen;

	Image * _totalMap;
	bool _drawMiniMap;
	POINT _miniMapCamPos;
	POINT _ptMouseCam;

	int _moveCount;

	RoomList _roomList;
	RECT _room;
	int roomX, roomY;


	RECT _rightBoard;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	virtual void exit();

	//맵툴세팅
	void maptoolSetup();//맵세팅
	bool selectTerrain();
	bool selectObject();
	bool selectEnemy();
	void drawTile();
	void dragTile();
	void setMap();
	void createRoom();
	void renderRoomRange();

	void locateEnemy();
	void setBlock();

	//세이브
	void save();
	//로드
	void load();


	void moveCard();
	void cameraMove();
	void settingControl();

	//지형, 오브젝트 셋터
	TERRAIN getTerrainType(int frameX, int frameY);
	OBJECT getObjectType(int frameX, int frameY = 0);
	ENEMY_TYPE getEnemyType(int frameX);

	maptoolScene() {}
	~maptoolScene() {}
};