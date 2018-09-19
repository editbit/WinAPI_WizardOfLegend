#pragma once
#include "actor.h"
class Bullet : public Actor
{
	Image* _image;		// 불릿이미지
	Image* _pixelMap;	// 픽셀맵 받아오기
	float _radius;		// 불릿 반지름
	float _range;		// 불릿사거리

	float _fireX, _fireY;
public:
	virtual HRESULT init(float radius, float speed, float power, float range, const char* imageName = "없음");
	virtual HRESULT init(float radius, float speed, float range, const char* imageName = "없음");
	virtual HRESULT init();
	virtual void update();
	virtual void render(bool rotate = false);
	virtual void release();

	virtual bool collide(Image * pixelImage);

	void setPixelMap(Image* pixelMap) { _pixelMap = pixelMap; }
	float getRange() { return _range; }
	//bool getIsActive() { return _isActive; }

	float getEffectAngle() { return getAnglef(_x, _y, _fireX, _fireY); }

	void setIsActive(bool isActive) { _isActive = isActive; }
	void setFireCenter(float fireX, float fireY) { _fireX = fireX; _fireY = fireY; _x = fireX; _y = fireY; }

	Bullet() {}
	~Bullet() {}
};

