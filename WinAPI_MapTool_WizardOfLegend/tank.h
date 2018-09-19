#pragma once
#include "actor.h"

//탱크맵에 접근 가능하도록 클래스 전방선언
class tileMap;

//탱크 4방향
enum TANKDIRECTION
{
	TANKDIRECTION_DOWN,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_LEFT
};

class tank : public Actor
{
private:
	tileMap * _tankMap;

	TANKDIRECTION _direction;	//탱크 방향
	Image* _image;				//탱크 이미지
	RECT _rc;					//탱크 렉트
	float _x, _y;				//탱크 위치좌표
	float _speed;				//탱크 속도
	int tileIndex[4];
	int collisionRange;


	int _index, _count;

	int _curFrameX, _curFrameY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void tankMove(void);
	void setTankPosition(int index);


	//탱크맵 메모리 링크
	void setTankMapLink(tileMap* tm) { _tankMap = tm; }

	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRC() { return _rc; }
	POINT getPos() { return { (int)_x, (int)_y }; }
	void setSpeed(float speed) { _speed = speed; }

	tank() {}
	~tank() {}
};