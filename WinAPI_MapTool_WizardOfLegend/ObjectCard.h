#pragma once
#include "MaptoolCard.h"
/*
��� 1
�� 4
��ü 11
��� 1
�ٴ� 1
����� 5
���� 7
���� 2
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

