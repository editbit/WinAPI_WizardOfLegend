#pragma once
#include "MaptoolCard.h"

#define SAMPLE_ENEMY_MAX 4
#define SAMPLE_ENEMY_RC_SIZE 80

struct SampleEnemy
{
	Image * img;
	RECT rc;

	int width, height;
};

class EnemyCard :
	public MaptoolCard
{
public:
	vector<SampleEnemy> _sampleEnemy;

public:
	void init(float x, float y);
	void update();
	void render();

	void settingSample();

	EnemyCard() {}
	~EnemyCard() {}
};

