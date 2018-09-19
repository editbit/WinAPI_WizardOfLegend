#include "stdafx.h"
#include "backgroundActor.h"

void BackgroundActor::render(int x, int y)
{
	_img->render(getMemDC(), x, y);

	if (KEYMANAGER->isToggleKey(VK_F12))
	{
		char str[20];
		sprintf_s(str, "%.0f", _z);
		TextOut(getMemDC(), x + _img->getWidth() / 2, y + _img->getHeight() / 2, str, strlen(str));
	}
}
