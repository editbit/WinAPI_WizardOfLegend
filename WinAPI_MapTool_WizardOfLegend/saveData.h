#pragma once
#include "singletonBase.h"
//�� ��ȯ� ����ϵ��� ����

class SaveData : public SingletonBase <SaveData>
{
private:
	HANDLE _saveHandle;
	DWORD _result;
	int _hp;
	char _data[128];

public:
	HRESULT init();
	void release();

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	SaveData() {}
	~SaveData() {}
};


//����
//ü�� ����
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	SAVEDATA->setHp(_currentHp);
//}
////ü�� �ε�
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	_currentHp = SAVEDATA->getHp();
//}

