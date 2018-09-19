#include "stdafx.h"
#include "Camera.h"

void Camera::setRoomSize(RECT room)
{
	roomRange = room;

	if (maxWidth == 0)
		maxWidth = roomRange.right;

	if (maxHeight == 0)
		maxHeight = roomRange.bottom;


}

void Camera::setMaxRange(int width, int height)
{
	maxWidth = width;
	maxHeight = height; 

	roomRange = RectMake(0, 0, width, height);
}

void Camera::videoShooting(int _x, int _y, float _speed)
{
	speed = _speed;
	if (speed != 0)
	{
		destX = _x - camWidth / 2;
		destY = _y - camHeight / 2;
		if (destX < 0)
		{
			destX = 0;
		}
		else if (destX + camWidth > maxWidth)
		{
			destX = maxWidth - camWidth;
		}
		if (destY < 0)
		{
			destY = 0;
		}
		else if (destY + camHeight > maxHeight)
		{
			destY = maxHeight - camHeight;
		}

	}
	else
	{
		x = destX = _x - camWidth / 2;
		y = destY = _y - camHeight / 2;
	}
	videoShooting();
}

void Camera::videoShooting()
{
	float angle;
	delay = 30;

	if(speed != 0)
		delayCount++;
	if (delayCount >= delay)
	{
		if ((x != destX || y != destY))
		{
			angle = getAngle(x, y, destX, destY);
			oldX = x;
			oldY = y;

			if(x != destX)
				x += cos(angle)*speed;
			if(y != destY)
				y += -sin(angle)*speed;

			if ((oldX < destX && destX < x) ||
				(oldX > destX && destX > x))
			{
				x = destX;
			}
			if ((oldY < destY && destY < y) ||
				(oldY > destY && destY > y))
			{
				y = destY;
			}
		}
		else
		{
			delayCount = 0;
		}
	}

	if (roomRange.right - roomRange.left < camWidth)
	{
		x = (roomRange.left + roomRange.right - camWidth) * 0.5f;
	}
	else
	{
		if (x < roomRange.left)
		{
			x = roomRange.left;
		}
		else if (x + camWidth > roomRange.right)
		{
			x = roomRange.right - camWidth;
		}
	}

	if (roomRange.bottom - roomRange.top < camHeight)
	{
		y = (roomRange.top + roomRange.bottom - camHeight) * 0.5f;
	}
	else
	{
		if (y < roomRange.top)
		{
			y = roomRange.top;
		}
		else if (y + camHeight > roomRange.bottom)
		{
			y = roomRange.bottom - camHeight;
		}
	}

	sX = sY = 0;
	if (count > 0)
	{
		count--;
		sX = RND->getInt(shakingPower) - shakingPower / 2;
		sY = RND->getInt(shakingPower) - shakingPower / 2;
	}

}

HRESULT Camera::init()
{
	x = 0;
	y = 0;
	oldX = oldY = 0;
	startX = startY = 0;
	camWidth = maxWidth = camHeight;
	camHeight = maxHeight = camHeight;
	count = 0;
	sX = sY = shakingPower = 0;
	delayCount = 0;
	return S_OK;
}

void Camera::release()
{
}
