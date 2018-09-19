#pragma once
#include "singletonBase.h"
//=============================================================
//	## KeyManager ## (키 매니져)
//=============================================================

#define KEYMAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	//키매니져 초기화
	HRESULT init();
	//키매니져 해제
	void release();

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렸다 띄어졌냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려있냐?
	bool isStayKeyDown(int key);
	//토글키냐?
	bool isToggleKey(int key);

	KeyManager() {}
	~KeyManager() {}
};

