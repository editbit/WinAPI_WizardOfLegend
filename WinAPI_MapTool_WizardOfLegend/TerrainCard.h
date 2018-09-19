#pragma once
#include "MaptoolCard.h"
#include "tileNode.h"

class TerrainCard : public MaptoolCard
{
public:
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽화면 타일(총 160개)

public:
	void init(float x, float y);
	void update();
	void render();

	TerrainCard() {}
	~TerrainCard() {}
};

