#pragma once
#include "MaptoolCard.h"
/*
기둥 1
문 4
물체 11
배경 1
바닥 1
벽장식 5
석상 7
함정 2
*/

#define SAMPLE_OBJECT_TYPE 8
#define SAMPLE_OBJECT_MAX 37
#define SAMPLE_OBJECT_RC_SIZE 80

struct SampleObject
{
	Image * objImg;
	RECT rc;

	int width, height;
};
class ObjectCard : public MaptoolCard
{
public:
	SampleObject _sampleObject[SAMPLE_OBJECT_MAX];
	int frameImangeIndex;

public:
	void init(float x, float y);
	void update();
	void render();

	void settingSample();

	int getFrameImageIndex() { return frameImangeIndex; }

	ObjectCard() {}
	~ObjectCard() {}
};

