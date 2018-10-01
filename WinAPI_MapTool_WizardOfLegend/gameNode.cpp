#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT GameNode::init()
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화 // 10/1000초 마다 타이머 1번
		KEYMANAGER->init();					//키매니져 초기화
		RND->init();						//랜덤펑션 초기화
		IMAGEMANAGER->init();				//이미지매니져 초기화
		SAVEDATA->init();					//세이브데이터 초기화
		TXTDATA->init();					//TXT데이터 초기화
		INIDATA->init();					//INI데이터 초기화
		SCENEMANAGER->init();				//씬매니져 초기화
		CAM->init();
		EFFECT->init();
		RENDERMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		UIMANAGER->init();
		ASTAR->init();

		BULLETMANAGER->init();
	}

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void GameNode::release()
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);				//1번타이머 해제
		//키매니져 싱글톤 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 싱글톤 해제
		RND->release();
		RND->releaseSingleton();
		//이미지매니져 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//세이브데이터 싱글톤 해제
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//TXT데이터 싱글톤 해제
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->release();
		INIDATA->releaseSingleton();
		//씬매니져 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		// 타임매니져 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		// 사운드매니져 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		// 이펙트매니져 싱글톤 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		// 임시
		CAM->release();
		CAM->releaseSingleton();
		EFFECT->release();
		EFFECT->releaseSingleton();
		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();

		ASTAR->release();
		ASTAR->releaseSingleton();

		BULLETMANAGER->release();
		BULLETMANAGER->releaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void GameNode::update()
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다(true => false)
	//InvalidateRect(_hWnd, NULL, FALSE);
	//새로고침해주는 함수 - 인터넷익스플로어의 F5와 같다
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void GameNode::render() //이미지매니저를 추가하면서 HDC매개변수 제거
{
}

//=============================================================
//	## 메인프로시져 ##
//=============================================================
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;			//핸들DC 			
	PAINTSTRUCT ps;		//페인트구조체	

	switch (iMessage)
	{
	//case WM_TIMER:
	//	this->update();
	//	break;
	//case WM_PAINT:							//출력에 관한 모든것을 담당한다(문자, 그림, 도형등등 화면에 보이는 모든것)
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render();						//이미지 매니저를 추가하면서 HDC매개변수 제거
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_MOUSEWHEEL:
	{
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

		_angleWheel += (zDelta == 120) ? 0.01f : -0.01f;
	}
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:						//키보드 키가 눌렸을때 메세지 발생
		switch (wParam)
		{
		//case VK_ESCAPE:						//esc 키를 누르면 화면종료
		//	//PostMessage(hWnd, WM_DESTROY, 0, 0);
		//	//SCENEMANAGER->exit();
		//	if (!UIMANAGER->getIsBlockingUI())
		//		UIMANAGER->openUI(OPTION_MENU);
		//	else
		//		UIMANAGER->setIsBlockingUI(false);
		//	break;

			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	//윈도우 프로시져에서 처리되지 않은 나머지 메세지를 처리해준다
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}