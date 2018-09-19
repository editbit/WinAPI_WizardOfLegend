#include "stdafx.h"
#include "iniData.h"

HRESULT INIData::init()
{
	return S_OK;
}

void INIData::release(void)
{
	for (int i = 0; i < _vIniData.size(); ++i)
	{
		delete[] _vIniData[i].value;
	}
}
//ini저장할 데이터들을 벡터에 추가 섹션,키,값
void INIData::addData(const char * section, const char * key, const char * value)
{
	//ini데이터 구조체 선언후 초기화
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	//data.value = (char*)value;

	int len = strlen(value);
	char * temp = new char[len + 1];
	for (int i = 0; i < len; ++i)
	{
		temp[i] = value[i];
	}
	temp[len] = '\0';
	data.value = temp;

	//벡터에 ini데이터 구조체 담기
	_vIniData.push_back(data);
}
//fileName.ini 파일로 저장
void INIData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/박성우/~~/windowApi/fileName.ini
	strcat_s(dir, str);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}
//문자열로 데이터 로드
char * INIData::loadDataString(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/박성우/~~/windowApi/fileName.ini
	strcat_s(dir, str);
	//dir = 불러올 ini파일의 경로

	char data[64] = { NULL }; //불러온 데이터를 문자형 변수 data에 담는다 (버퍼)
	GetPrivateProfileString(section, key, "NOT_FOUND", data, 64, dir);

	return data; // 불러온 데이터 반환
}
//정수로 데이터 로드
int INIData::loadDataInteger(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/박성우/~~/windowApi/fileName.ini
	strcat_s(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}
//실수로 데이터 로드
float INIData::loadDataFloat(const char * fileName, const char * section, const char * key)
{
	return (atof)(loadDataString(fileName, section, key)); //atof 문자열을 실수로 반환한다.
}
