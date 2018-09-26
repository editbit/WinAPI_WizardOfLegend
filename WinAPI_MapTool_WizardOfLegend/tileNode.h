#pragma once

#define MINIMAP_RATE 8

#define CARDBOARD_NUM 3

#define TILE_RENDER_RANGE 30
#define TILE_RENDER_RANGE_X 18
#define TILE_RENDER_RANGE_Y 11


//����ȭ��Ÿ�� (ȭ�� ����) 
#define TILESIZE 64
#define SAMPLETILESIZE 32
#define TILEX 200
#define TILEY 200
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//�̹���Ÿ�� (ȭ�� �����ʻ��)
#define SAMPLETILEX 21
#define SAMPLETILEY 9
#define SAMPLETILE_SCALE 1

//�����Ӽ��� ������� �����ϱ�
//��Ʈ������ �Ұ�� �ӵ��� �����⶧���� ����Ѵ�
//������ �����ϰ� �Һ����� ó���ص� �ȴ�

//||(or), &&(and)
//|(or), &(and)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
#define ATTR_UNMOVAL 0x00000001
#define ATTR_POISON	0x00000002

class Stuff;

//�������� ����� �̳ѹ�
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER, CTRL_ENEMYDRAW,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};


//����
//enum TERRAIN
//{
//	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
//};
enum TERRAIN
{
	TR_CLIFF,

	TR_WALL, TR_GROUND, TR_END, TR_NONE
};


//������Ʈ
//enum OBJECT
//{
//	OBJECT_BLOCK1, OBJECT_BLOCK3, OBJECT_BLOCKS,
//	OBJECT_TANK1, OBJECT_TANK2,
//	OBJECT_FLAG1, OBJECT_FLAG2,
//	OBJECT_NONE
//};
enum OBJECT
{
	OBJECT_ITEM, OBJECT_COIN,

	OBJECT_WALL,

	OBJECT_BLOCK1, OBJECT_BLOCK3, OBJECT_BLOCKS,
	OBJECT_TANK1, OBJECT_TANK2,
	OBJECT_FLAG1, OBJECT_FLAG2,
	OBJECT_NONE,

	OBJECT_DECO, OBJECT_BREAKABLE, OBJECT_TRAP, OBJECT_ATTACKABLE
};

enum ENEMY_TYPE
{
	ENEMY_NONE = -1, SHADOW = 0, MAGE, ROGUE
};

//��ġ��ǥ
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

enum TRAP_TYPE
{
	BOMB_TRAP = 30, AWL_TRAP = 35
};

/*Ÿ�ϱ���ü*/
struct tagTile
{
	TERRAIN terrain;
	OBJECT objType;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	/*int objFrameX;
	int objFrameY;*/
	int objIndex;
	Stuff * obj = NULL;
};

//�̹��� Ÿ�ϱ���ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};