#include "stdafx.h"
#include "TerrainCard.h"

void TerrainCard::init(float x, float y)
{
	MaptoolCard::init(x, y);

	cardType = CTRL_TERRAINDRAW;

	_maxPage = 3;
	_drawNum = 3;

	int xPos = 0, yPos = 0;
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			////지형세팅
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}

	int index = 0;

	for (int k = 0; k < _maxPage; ++k)
	{
		for (int i = k * _drawNum; i < k * _drawNum + 3; ++i)
		{
			xPos = 0;
			yPos = i % _drawNum;
			for (int j = 0; j < 9; ++j)
			{
				index = i * SAMPLETILEX + j;
				_sampleTiles[i * SAMPLETILEX + j].rc = RectMake(xPos * (SAMPLETILESIZE + 2), yPos * (SAMPLETILESIZE + 2), SAMPLETILESIZE, SAMPLETILESIZE);
				xPos = (xPos + 1) % 9;
			}

			xPos = 0;
			yPos += 1;
			for (int j = 9; j < 18; ++j)
			{
				index = i * SAMPLETILEX + j;
				_sampleTiles[i * SAMPLETILEX + j].rc = RectMake( xPos * (SAMPLETILESIZE + 2), (yPos + 3) * (SAMPLETILESIZE + 2), SAMPLETILESIZE, SAMPLETILESIZE);
				xPos = (xPos + 1) % 9;
			}


			xPos = 0;
			yPos += 1;
			for (int j = 18; j < 21; ++j)
			{
				index = i * SAMPLETILEX + j;
				_sampleTiles[i * SAMPLETILEX + j].rc = RectMake((SAMPLETILESIZE + 2) * 3 + xPos * (SAMPLETILESIZE + 2), (yPos + 6) * (SAMPLETILESIZE + 2), SAMPLETILESIZE, SAMPLETILESIZE);
				xPos = (xPos + 1) % 3;
			}
		}
	}

}

void TerrainCard::update()
{
	MaptoolCard::update();
}

void TerrainCard::render()
{
	MaptoolCard::render();

	int startX = CAM->getX() / SAMPLETILESIZE, startY = CAM->getY() / SAMPLETILESIZE;

	for (int i = _currentPage * _drawNum * SAMPLETILEX; i < _currentPage * _drawNum * SAMPLETILEX + _drawNum * SAMPLETILEX; i++)
	{
		//IMAGEMANAGER->frameRender("tilemap", getMemDC(), _sampleTiles[i].rc.left, _sampleTiles[i].rc.top, _sampleTiles[i].terrainFrameX, _sampleTiles[i].terrainFrameY);
		IMAGEMANAGER->frameRender("sampletilemap", getMemDC(),
			(rc.left + 55) + _sampleTiles[i].rc.left,
			(rc.top + 90) + _sampleTiles[i].rc.top - _sampleTiles[_currentPage * _drawNum * SAMPLETILEX].rc.top,
			_sampleTiles[i].terrainFrameX, _sampleTiles[i].terrainFrameY);
	}

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//이미지타일 렉트 렌더
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			Rectangle(getMemDC(), RectMake((rc.left + 55) + _sampleTiles[i].rc.left,
				(rc.top + 90) + _sampleTiles[i].rc.top - _sampleTiles[_currentPage * _drawNum * SAMPLETILEX].rc.top, SAMPLETILESIZE, SAMPLETILESIZE));
		}
	}


	effectRender();
}
