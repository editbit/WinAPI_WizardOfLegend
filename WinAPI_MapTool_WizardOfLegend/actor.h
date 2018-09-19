#pragma once
#include "gameNode.h"
#include "tileMap.h"

class Actor : public GameNode
{
protected:
	float _x, _y, _z;
	float _oldX, _oldY, _oldZ;

	float _gravity;
	float _speed;
	float _power;
	float _angle;

	int _hp;
	int _maxHp;

	int _state;
	int _dir;		// 방향: 상화에 따라 사용

	//int _curFrameX, _curFrameY;
	unsigned int _count;			// 프레임 인덱스 값 더하기
	int _index;			// 프레임 돌리기
	RECT _hitBox, _moveBox, _attackBox;

	bool _isLiftable;
	bool _isActive;

	tileMap * _tileMap;
	tagTile *tiles;		//타일
	DWORD *attribute;	//속성
	Image * _pixelMap;
public:		// 멤버 함수
	virtual void attack() {}
	virtual void damaged(Actor *e) {}	// 체력 감소, 넉백, 동료 떨어트리기(오투스), 서있을 때 피격시 사라짐(게디, 알폰스)
	virtual void move();
	virtual void collide(){}
	virtual bool collide(Actor* a);
	virtual void throwed(float speed, float angle);
	virtual void drawUI() {}

	void changeState(int state);
	virtual bool checkMovable(COLORREF color);
	void setLinkTileMap(tileMap *tile);
	void setPixelMap(Image * pixelMap) { _pixelMap = pixelMap; }

	void setIsLiftable(bool isLiftable) { _isLiftable = isLiftable; }
	void setIsActive(bool isActive) { _isActive = isActive; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setZ(float z) { _z = z; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setSpeed(float speed) { _speed = speed; }
	void setPower(float power) { _power = power; }
	void setAngle(float angle) { _angle = angle; }

	void setHp(int hp) { _hp = hp; }
	void setMaxHp(int maxHp) { _maxHp = maxHp; }
	void setState(int state) { _state = state; }
	void setDir(int dir) { _dir = dir; }
	void setHitBox(RECT hitBox) { _hitBox = hitBox; }
	void setMoveBox(RECT moveBox) { _moveBox = moveBox; }
	void setAttackBox(RECT attackBox) { _attackBox = attackBox; }

	void setCount(int count) { _count = count; }
	void setIndex(int index) { _index = index; }

	bool getIsActive() { return _isActive; }
	bool getIsLiftable() { return _isLiftable; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getGravity() { return _gravity; }
	float getSpeed() { return _speed; }
	float getPower() { return _power; }
	float getAngle() { return _angle; }
	RECT getHitBox() { return _hitBox; }
	RECT getMoveBox() { return _moveBox; }
	RECT getAttackBox() { return _attackBox; }

	int getHp() { return _hp; }
	int getMaxHp() { return _maxHp; }
	int getState() { return _state; }
	int getDir() { return _dir; }
	int getCount() { return _count; }
	int getIndex() { return _index; }

	virtual float getCenterY() { return 0.0f; };

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();
public:
	Actor();
	virtual ~Actor() {}
};

