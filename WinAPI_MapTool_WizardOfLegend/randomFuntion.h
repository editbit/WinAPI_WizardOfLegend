#pragma once
#include "singletonBase.h"
#include <time.h>

//=============================================================
//	## ·£´ýÆã¼Ç
//=============================================================
class randomFuntion : public SingletonBase <randomFuntion>
{
public:
	randomFuntion()
	{
		//srand(time(NULL));
		srand(GetTickCount());
	}
	~randomFuntion() {}

	HRESULT init() { return S_OK; }
	void release() {}

	//GetInt
	inline int getInt(int num) { return rand() % num; }
	//ADDED
	//GetFromIntTo
	inline int getFromIntTo(int fromNum, int toNum)
	{
		if(fromNum > toNum)
			return rand() % (fromNum - toNum + 1) + toNum;
		else
			return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	//ADDED
	//GetFromFloatTo
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		if (fromNum > toNum)
			return (rnd * (fromNum - toNum) + toNum);
		else
			return (rnd * (toNum - fromNum) + fromNum);
	}
};

