#pragma once
#include "singletonBase.h"
//이펙트 클래스 전방선언(뻥남 방지용)
class effect;

class effectManager : public SingletonBase <effectManager>
{
private:
	//이펙트 클래스를 담을 벡터 및 반복자
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//이펙트를 담아놓은 벡터를 담을 맵
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

private:
	mEffect _mEffect;		//이펙트벡터가 담겨있는 맵

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//이펙트 추가(이펙트키값, 이미지키값, 이펙트속도, 버퍼갯수)
	void addEffect(string effectName, const char* imageName, float effectFPS, int buffer);
	//이펙트 플레이
	void play(string effectName, int x, int y);
	void play(string effectName, int x, int y, float angle);
	void play(string effectName, int x, int y, int alpha);

	effectManager() {}
	~effectManager() {}
};

