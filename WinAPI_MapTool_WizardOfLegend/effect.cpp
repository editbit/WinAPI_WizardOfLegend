#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(Image * effectImg, float effectFPS)
{
	//���� �ʱ�ȭ
	_effectImg = effectImg;
	_effectFPS = effectFPS;
	_isRunning = false;

	//����Ʈ �ִϸ��̼� ���� �� �ʱ�ȭ
	_effectAni = new Animation;
	_effectAni->init(_effectImg->getWidth(), _effectImg->getHeight(), _effectImg->getMaxFrameX() + 1, _effectImg->getMaxFrameY() + 1);
	_effectAni->setPlayFrame();
	_effectAni->setFPS(1);

	_alpha = _angle = 0;

	return S_OK;
}

void effect::release(void)
{
	//����Ʈ�ִ� ����
	_effectAni->release();
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunning)
	{
		_effectAni->frameUpdate(_effectFPS);
	}
	//����Ʈ �ִϸ��̼� ���ᰡ �Ǹ� ���߱�(_isRunning = false;)
	if (!_effectAni->isPlay()) this->stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		if (_angle > 0)
		{
			_effectImg->rotateFrameRender(getMemDC(),
				_x  - CAM->getX(), // + _effectImg->getFrameWidth()/2,
				_y - CAM->getY() , //+ _effectImg->getFrameHeight()/2,
				_effectAni->getFramePos().x / _effectAni->getFrameWidth(),
				_effectAni->getFramePos().y / _effectAni->getFrameHeight(),
				_angle);
		}
		else
		{
			if (_alpha == 255)
			{
				_effectImg->aniRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _effectAni);
			}
			else
			{
				_effectImg->alphaFrameRender(getMemDC(),
					_x - CAM->getX(), // + _effectImg->getFrameWidth() / 2,
					_y - CAM->getY(), // + _effectImg->getFrameHeight() / 2,
					_effectAni->getFramePos().x / _effectAni->getFrameWidth(),
					_effectAni->getFramePos().y / _effectAni->getFrameHeight(),
					_alpha);
			}
			
		}
	}
}

void effect::startEffect(int x, int y)
{
	//��ġ�� ������ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
	_angle = -1;
	_alpha = 255;
}

void effect::startEffect(int x, int y, float angle)
{
	//��ġ�� ������ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
	_angle = angle;
	_alpha = 255;
}

void effect::startEffect(int x, int y, int alpha)
{
	//��ġ�� ������ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
	_angle = 0;
	_alpha = alpha;
}

void effect::stopEffect()
{
	_isRunning = false;
}
