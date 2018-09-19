#pragma once
#include "gameNode.h"
class BackgroundActor :
	public GameNode
{
protected:
	Image *_img;
	float _x, _y, _z;
	float _speed;

public:
	virtual HRESULT init(void) { return S_OK; }
	virtual void release(void) {}
	virtual void update(void) {}
	virtual void render(void) {}
	virtual void render(int x, int y);

	void setImage(Image *img) { _img = img; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setZ(float z) { _z = z; }
	void setSpeed(float speed) { _speed = speed; }
	
	Image* getImage() { return _img; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getSpeed() { return _speed; }

	BackgroundActor() {}
	~BackgroundActor() {}
};

