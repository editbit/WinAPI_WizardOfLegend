#include "stdafx.h"
#include "MyEffectManager.h"


HRESULT MyEffectManager::init()
{
	return S_OK;
}

void MyEffectManager::release()
{
	list<MyEffect>::iterator iter = effectList.begin();

	effectList.clear();
}


void MyEffectManager::render(HDC hdc)
{
	list<MyEffect>::iterator iter;

	if (!effectList.empty())
	{
		iter = effectList.begin();
		while( iter != effectList.end())
		{
			iter->count = (iter->count + 1) % 10;
			if (iter->count == 0)
			{
				iter->index++;
				if (iter->index > iter->eImage->getMaxFrameX())
				{
					iter = effectList.erase(iter);
					continue;
				}
			}
			iter->eImage->frameRender(hdc, iter->x - CAM->getX() - iter->eImage->getFrameWidth()/2,
				iter->y - CAM->getY() - iter->eImage->getFrameHeight()/2, iter->index, iter->frameY);

			++iter;
		}
	}
}



void MyEffectManager::generateEffect(const char * effectName, float x, float y, int frameY)
{
	MyEffect e;
	e.eImage = IMAGEMANAGER->findImage(effectName);
	e.x = x;
	e.y = y;
	e.index = e.count = 0;
	e.frameY = frameY;

	effectList.push_back(e);
}



MyEffectManager::MyEffectManager()
{
}


MyEffectManager::~MyEffectManager()
{
}
