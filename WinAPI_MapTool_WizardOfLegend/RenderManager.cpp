#include "stdafx.h"
#include "RenderManager.h"
#include "actor.h"
#include "backgroundActor.h"
#include "tileMap.h"

HRESULT RenderManager::init()
{
	return S_OK;
}

void RenderManager::release()
{
	renderList.clear();
}

void RenderManager::render(HDC hdc)
{
	multimap<float, Actor *>::iterator iter;

	tagTile *tiles = NULL;
	//if(tiles != NULL)
		tiles= _tileMap->getTiles();

	int x, y;
	if (!renderList.empty())
	{
		for (iter = renderList.begin(); iter != renderList.end(); ++iter)
		{
			iter->second->render();	

			if (iter->second->getState() == FALL_STATE)// && tiles != NULL)
			{
				Image * tileMap = IMAGEMANAGER->findImage("tilemap");
				for (int i = (iter->second->getY()) / TILESIZE + 1; i < (iter->second->getY()) / TILESIZE + 5; ++i)
				{
					for (int j = iter->second->getX() / TILESIZE - 1; j < iter->second->getX() / TILESIZE + 1; ++j)
					{
						if (tiles[i * TILEX + j].terrain == TR_CLIFF) continue;

						tileMap->frameRender(hdc,
							tiles[i * TILEX + j].rc.left - CAM->getX(),
							tiles[i * TILEX + j].rc.top - CAM->getY(),
							tiles[i * TILEX + j].terrainFrameX, tiles[i * TILEX + j].terrainFrameY);
					}
				}
			}
		}
	}

	renderList.clear();
}

void RenderManager::backgroundRender(HDC hdc)
{
	multimap<float, BackgroundActor *>::iterator iter;
	float centerX = CAM->getX() + WINSIZEX / 2, centerY = CAM->getY() + WINSIZEY / 2;
	float x, y, z;
	float width, height;
	if (!backgroundList.empty())
	{
		for (iter = backgroundList.begin(); iter != backgroundList.end(); ++iter)
		{
			iter->second->update();
			width = iter->second->getImage()->getWidth();
			height = iter->second->getImage()->getHeight();
			z = iter->second->getZ();

			x = WINSIZEX / 2 + (iter->second->getX() - centerX) / (5 - z);
			y = WINSIZEY / 2 + (iter->second->getY() - centerY) / (5 - z);
			if (KEYMANAGER->isToggleKey(VK_F11))
			{
				if (300 < x + width && x < WINSIZEX - 300 &&
					300 < y + height && y < WINSIZEY - 300)
				{
					iter->second->render(x, y);
				}
			}
			else
			{
				if (0 < x + width && x < WINSIZEX &&
					0 < y + height && y < WINSIZEY)
				{
					iter->second->render(x, y);
				}
			}
		}
	}

}

void RenderManager::addRender(float z, Actor * name)
{
	renderList.insert(make_pair(z, name));
}


void RenderManager::addBackground(float z, BackgroundActor *backActor)
{
	backgroundList.insert(make_pair(z, backActor));
}

void RenderManager::clearBackground()
{
	multimap<float, BackgroundActor *>::iterator iter;
	if (!backgroundList.empty())
	{
		for (iter = backgroundList.begin(); iter != backgroundList.end(); ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	backgroundList.clear();
}
