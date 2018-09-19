#pragma once
//=============================================================
//	## SingletonBase ## (싱글톤 패턴)
//=============================================================

template <typename T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//싱글톤 가져오기
	static T* getSingleton(void);
	//싱글톤 메모리에서 해제하기
	void releaseSingleton(void);
};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

//싱글톤 가져오기
template<typename T>
inline T * SingletonBase<T>::getSingleton(void)
{
	//싱글톤이 없으면 새로 생성하자
	if (!singleton) singleton = new T;
	return singleton;
}
//싱글톤 메모리에서 해제하기
template<typename T>
inline void SingletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면 메모리에서 해제하자
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
