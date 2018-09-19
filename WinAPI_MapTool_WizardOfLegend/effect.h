#pragma once
#include "gameNode.h"

class effect : public GameNode
{
private:
	Image * _effectImg;		//이펙트 이미지(반드시 프레임이미지 사용하자)
	Animation* _effectAni;	//이펙트 애니메이션

	int _x, _y;				//이펙트 터트릴 위치좌표
	float _angle;
	int _alpha;
	float _effectFPS;		//이펙트 속도
	bool _isRunning;		//이펙트 재생중이냐?

public:
	HRESULT init(Image* effectImg, float effectFPS);
	void release(void);
	void update(void);
	void render(void);

	//내가 원하는 좌표에 이펙트 시작하기
	void startEffect(int x, int y);
	//내가 원하는 좌표에 이펙트 시작하기
	void startEffect(int x, int y, float angle);
	//내가 원하는 좌표에 이펙트 시작하기
	void startEffect(int x, int y, int alpha);
	//이펙트 멈추기
	void stopEffect();

	//이펙트가 재생중인지 상태값 가져오기
	bool getIsRunning() { return _isRunning; }

	effect() : _effectImg(NULL), _effectAni(NULL), _isRunning(false), _x(0), _y(0) {}
	~effect() {}
};

