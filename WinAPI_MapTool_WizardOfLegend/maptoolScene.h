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

	tagTile _tiles[TILEX * TILEY];	//����ȭ�� Ÿ��(�� 400��)
	//tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ȭ�� Ÿ��(�� 160��)
	tagCurrentTile _currentTile;	//����Ÿ��

	ObjectCard _objectCard;
	TerrainCard _terrainCard;
	EnemyCard _enemyCard;

	MaptoolCard * _currentCard;
	Image * _cardDeck;
	RECT _cardDeckRect;
	POINT _cardPos;

									//��ư 5��(���̺�, �ε�, ����, ������Ʈ, ���찳)
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

	//��������
	void maptoolSetup();//�ʼ���
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

	//���̺�
	void save();
	//�ε�
	void load();


	void moveCard();
	void cameraMove();
	void settingControl();

	//����, ������Ʈ ����
	TERRAIN getTerrainType(int frameX, int frameY);
	OBJECT getObjectType(int frameX, int frameY = 0);
	ENEMY_TYPE getEnemyType(int frameX);

	maptoolScene() {}
	~maptoolScene() {}
};