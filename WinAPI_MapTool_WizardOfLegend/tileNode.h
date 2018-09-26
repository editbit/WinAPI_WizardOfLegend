#pragma once

#define MINIMAP_RATE 8

#define CARDBOARD_NUM 3

#define TILE_RENDER_RANGE 30
#define TILE_RENDER_RANGE_X 18
#define TILE_RENDER_RANGE_Y 11


//게임화면타일 (화면 왼쪽) 
#define TILESIZE 64
#define SAMPLETILESIZE 32
#define TILEX 200
#define TILEY 200
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//이미지타일 (화면 오른쪽상단)
#define SAMPLETILEX 21
#define SAMPLETILEY 9
#define SAMPLETILE_SCALE 1

//지형속성을 내맘대로 정의하기
//비트연산을 할경우 속도가 빠르기때문에 사용한다
//하지만 사용안하고 불변수로 처리해도 된다

//||(or), &&(and)
//|(or), &(and)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
#define ATTR_UNMOVAL 0x00000001
#define ATTR_POISON	0x00000002

class Stuff;

//맵툴에서 사용할 이넘문
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER, CTRL_ENEMYDRAW,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};


//지형
//enum TERRAIN
//{
//	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
//};
enum TERRAIN
{
	TR_CLIFF,

	TR_WALL, TR_GROUND, TR_END, TR_NONE
};


//오브젝트
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

//위치좌표
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

enum TRAP_TYPE
{
	BOMB_TRAP = 30, AWL_TRAP = 35
};

/*타일구조체*/
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

//이미지 타일구조체
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//현재타일 구조체
struct tagCurrentTile
{
	int x, y;
};