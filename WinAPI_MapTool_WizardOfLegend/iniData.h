#pragma once
#include "singletonBase.h"
//=============================================================
//	## INIData ## (INI 데이터)
//=============================================================
//ini데이터 구조체
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class INIData : public SingletonBase <INIData>
{
private:
	vector<tagIniData> _vIniData;

public:
	HRESULT init();
	void release();

	//데이터 추가하기(섹션, 키, 밸류)
	void addData(const char* section, const char* key, const char* value);
	//세이브(파일이름)
	void saveINI(const char* fileName);

	//문자로 값을 로드하기(파일이름, 섹션, 키)
	char* loadDataString(const char* fileName, const char* section, const char* key);
	//정수로 값을 로드하기(파일이름, 섹션, 키)
	int loadDataInteger(const char* fileName, const char* section, const char* key);
	//실수로 값을 로드하기
	float loadDataFloat(const char* fileName, const char* section, const char* key); // atof ascii to float으로 문자열을 실수로 형변환하자.

	INIData() {}
	~INIData() {}
};


//같은 키로 addData하면 값이 변경된다.

/* 예시
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	//섹션, 키, 밸류
	//[세원]
	//노력=99
	//집중=70
	//[기훈]
	//롤실력=20
	//코딩력=80
	INIDATA->addData("세원", "노력", "99");
	INIDATA->addData("세원", "집중", "70");
	INIDATA->addData("기훈", "롤실력", "20");
	INIDATA->addData("기훈", "코딩력", "80");
	//파일이름으로 세이브
	INIDATA->saveINI("ARVR");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
	int num = INIDATA->loadDataInteger("ARVR", "기훈", "롤실력");
	cout << "기훈이 롤실력: " << num << endl;
	}
*/