#pragma once

//백버퍼 이미지를 정적변수로 만들어 두기
//ADDED 기존에 사용하던 백버퍼 관련 객체등은 이미지매니져가 실행함
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode
{
private:
	HDC _hdc;				//화면 HDC
	bool _managerInit;		//매니져 초기화 했냐?

public:
	virtual HRESULT init(bool managerInit);	//오버로딩된 이걸통해 초기화하도록 하자
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void exit() {}

	//백버퍼 이미지 얻기
	Image* getBackBuffer() { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//HDC 얻기 (화면DC)
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} //소멸자에 virtual 키워드를 붙이는 이유 면접시 단골질문임
};

