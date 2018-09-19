#pragma once
#include "actor.h"

class tileMap;



class TankEnemy :
	public Actor
{
private:
	tileMap * _tankMap;

	DIRECTION _direction;	//��ũ ����
	Image* _image;				//��ũ �̹���
	RECT _rc;					//��ũ ��Ʈ
	float _x, _y;				//��ũ ��ġ��ǥ
	float _speed;				//��ũ �ӵ�
	int tileIndex[2];

	int _count;
	int _curFrameX, _curFrameY;

	bool _isTrace;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void enemyMove(void);
	void setEnemyPosition(int index);

	void setTankMapLink(tileMap* tm) { _tankMap = tm; }

	float getX() { return _x; }
	float getY() { return _y; }
	POINT getPos() { return {(int)_x, (int)_y}; }
	RECT getRC() { return _rc; }
	void setSpeed(float speed) { _speed = speed; }
	void setDirection(DIRECTION dir) { _direction = dir; }

	TankEnemy() {}
	~TankEnemy() {}
};
