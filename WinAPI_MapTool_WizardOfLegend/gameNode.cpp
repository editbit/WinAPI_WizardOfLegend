#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
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
		SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ // 10/1000�� ���� Ÿ�̸� 1��
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹����Ŵ��� �ʱ�ȭ
		SAVEDATA->init();					//���̺굥���� �ʱ�ȭ
		TXTDATA->init();					//TXT������ �ʱ�ȭ
		INIDATA->init();					//INI������ �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		CAM->init();
		EFFECT->init();
		RENDERMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		UIMANAGER->init();
		ASTAR->init();
	}

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void GameNode::release()
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);				//1��Ÿ�̸� ����
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� �̱��� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//���̺굥���� �̱��� ����
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//TXT������ �̱��� ����
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();
		//���Ŵ��� �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		// Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		// ����Ŵ��� �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		// ����Ʈ�Ŵ��� �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		// �ӽ�
		CAM->release();
		CAM->releaseSingleton();
		EFFECT->release();
		EFFECT->releaseSingleton();
		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();

		ASTAR->release();
		ASTAR->releaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void GameNode::update()
{
	//���ΰ�ħ (���߿� ������ Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//�������۸� ���� ������� �ʴ´�(true => false)
	//InvalidateRect(_hWnd, NULL, FALSE);
	//���ΰ�ħ���ִ� �Լ� - ���ͳ��ͽ��÷ξ��� F5�� ����
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void GameNode::render() //�̹����Ŵ����� �߰��ϸ鼭 HDC�Ű����� ����
{
}

//=============================================================
//	## �������ν��� ##
//=============================================================
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;			//�ڵ�DC 			
	PAINTSTRUCT ps;		//����Ʈ����ü	

	switch (iMessage)
	{
	//case WM_TIMER:
	//	this->update();
	//	break;
	//case WM_PAINT:							//��¿� ���� ������ ����Ѵ�(����, �׸�, ������� ȭ�鿡 ���̴� ����)
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render();						//�̹��� �Ŵ����� �߰��ϸ鼭 HDC�Ű����� ����
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
	case WM_KEYDOWN:						//Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_ESCAPE:						//esc Ű�� ������ ȭ������
			//PostMessage(hWnd, WM_DESTROY, 0, 0);
			SCENEMANAGER->exit();
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	//������ ���ν������� ó������ ���� ������ �޼����� ó�����ش�
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}