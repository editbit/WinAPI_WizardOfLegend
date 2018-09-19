#pragma once

//����� �̹����� ���������� ����� �α�
//ADDED ������ ����ϴ� ����� ���� ��ü���� �̹����Ŵ����� ������
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode
{
private:
	HDC _hdc;				//ȭ�� HDC
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �߳�?

public:
	virtual HRESULT init(bool managerInit);	//�����ε��� �̰����� �ʱ�ȭ�ϵ��� ����
	virtual HRESULT init();				//void�� �ᵵ�Ǵµ� �ʱ�ȭ�� ������ ����� �ٷ� �˷���
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void exit() {}

	//����� �̹��� ���
	Image* getBackBuffer() { return _backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//HDC ��� (ȭ��DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} //�Ҹ��ڿ� virtual Ű���带 ���̴� ���� ������ �ܰ�������
};

