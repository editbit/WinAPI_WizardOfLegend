#pragma once
#include "actor.h"

//��ũ�ʿ� ���� �����ϵ��� Ŭ���� ���漱��
class tileMap;

//��ũ 4����
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

	TANKDIRECTION _direction;	//��ũ ����
	Image* _image;				//��ũ �̹���
	RECT _rc;					//��ũ ��Ʈ
	float _x, _y;				//��ũ ��ġ��ǥ
	float _speed;				//��ũ �ӵ�
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


	//��ũ�� �޸� ��ũ
	void setTankMapLink(tileMap* tm) { _tankMap = tm; }

	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRC() { return _rc; }
	POINT getPos() { return { (int)_x, (int)_y }; }
	void setSpeed(float speed) { _speed = speed; }

	tank() {}
	~tank() {}
};