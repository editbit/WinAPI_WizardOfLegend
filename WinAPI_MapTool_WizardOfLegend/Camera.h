#pragma once
#include "singletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:

	RECT roomRange;

	int maxWidth, maxHeight;
	int camWidth, camHeight;
	int x, y, oldX, oldY, startX, startY;
	int sX, sY, shakingPower;

	int destX, destY;
	float speed;

	int count, delay, delayCount;

public:
	void setRoomSize(RECT room);
	void setMaxRange(int width, int height);
	void setDrawRange(int width, int height) { camWidth = width; camHeight = height; }
	void setDrawPosition(int x, int y) { startX = x; startY = y; }
	void setPosition(int _x, int _y) { x = _x; y = _y; }
	void setShakeInfo(int shakingTime, int _shakingPower) { count = shakingTime; shakingPower = _shakingPower; }
	void videoShooting(int _x, int _y, float _speed = 0);
	void videoShooting();

	int getMaxWidth() { return maxWidth; }
	int getMaxHeight() { return maxHeight; }
	POINT getDrawRange() { return { camWidth, camHeight }; }
	int getX() { return x - sX; }
	int getY() { return y - sY; }
	int getSourX() { return x; }
	int getSourY() { return y; }
	int getSX() { return sX; }
	int getSY() { return sY; }

	int getCamWidth() { return camWidth; }
	int getCamHeight() { return camHeight; }


	HRESULT init();
	void release();

	Camera() : maxWidth(0), maxHeight(0) {}
	~Camera() {}
};

