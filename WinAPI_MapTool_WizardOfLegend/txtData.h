#pragma once
#include "singletonBase.h"

//저장할 데이터들을 벡터에 담아서 텍스트 파일로 만들어준다.

class TXTData : public SingletonBase <TXTData>
{
public:
	HRESULT init(void);
	void release(void);

	//세이브
	void txtSave(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);
	//1,2,100
	
	//로드
	vector<string> txtLoad(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	TXTData() {}
	~TXTData() {}
};

//예시
//세이브
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	//itoa => 정수를 문자로 integral to ascii
//	char temp[128];
//	vector<string> vStr;
//	vStr.push_back(itoa(_rocket->getX(), temp, 10));
//	vStr.push_back(itoa(_rocket->getY(), temp, 10));
//	vStr.push_back(itoa(_currentHp, temp, 10));
//
//	TXTDATA->txtSave("save.txt", vStr);
//}
//
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	vector<string> vStr;
//	vStr = TXTDATA->txtLoad("save.txt");
//	//atoi => 문자를 숫자로 ascii to integral
//	_rocket->setX(atoi(vStr[0].c_str()));
//	_rocket->setY(atoi(vStr[1].c_str()));
//	_currentHp = (atoi(vStr[2].c_str()));
//}

