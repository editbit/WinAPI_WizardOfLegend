#pragma once
#include "MaptoolCard.h"
#include "tileNode.h"

class TerrainCard : public MaptoolCard
{
public:
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ȭ�� Ÿ��(�� 160��)

public:
	void init(float x, float y);
	void update();
	void render();

	TerrainCard() {}
	~TerrainCard() {}
};

