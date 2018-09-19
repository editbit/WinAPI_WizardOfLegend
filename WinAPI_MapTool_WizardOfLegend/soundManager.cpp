#include "stdafx.h"
#include "soundManager.h"

HRESULT SoundManager::init(void)
{
	//FMOD �ý����� �����Ѵ�
	System_Create(&_system);

	//����, ä�μ� ����
	_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� Ŭ���� �����Ҵ�
	_sound = new Sound*[SOUNDBUFFER];
	_channel = new Channel*[SOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * SOUNDBUFFER);

	return S_OK;
}

void SoundManager::release(void)
{
	//���� �� ä�� ����
	if (_sound != NULL || _channel != NULL)
	{
		for (int i = 0; i < SOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	//�ý��� �ݱ�
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update(void)
{
	//���ΰ��ӿ��� ����Ŵ����� ������Ʈ ����� �Ѵ�
	//���� ���� �Ѱ������ �Ѵ�
	//���� �ý����� ������ ����ǰų�, ����� ������ ���带 �����ϴµ�
	//���� ���������� ������ �̷����� �ﰢ������ ó�����ش�
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			//���� ������ �̸� ���ε��صΰ� ����Ѵ�
			//�Ѱ��� ���ϸ� �������
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);

		}
		else//ȿ����
		{
			//���� ������ �׶��׶� �ǽð����� �ε��Ѵ�
			//���� ȿ������ ���� ũ�Ⱑ Ŭ��� ���۰� �����
			//�������� ���� ������� �����ϱ⶧���� ȿ������ �����ϴ�
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
	}
	else//�ݵ�� ȿ����
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ��Ƶд�
	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));
}

void SoundManager::playBgm(string keyName, float volume)
{
	//if(_currentSound != "" && isPlaySound(_currentSound))
		stop(_currentSound);

	_currentSound = keyName;

	play(keyName, volume);
}

void SoundManager::playBgm(float volume)
{
	playBgm(_currentSound, volume);
}

void SoundManager::play(string keyName, float volume)
{
	int count = 0;

	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
		
			//��������
			_channel[count]->setVolume(volume);
		}
	}
}

void SoundManager::setVolume(float volume)
{
	int count = 0;

	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (_currentSound == iter->first)
		{
			//���� �÷���
			//_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//��������
			_channel[count]->setVolume(volume);
		}
	}
}

void SoundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
		}
	}
}

void SoundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �ٽ����
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷������̳�?
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷������̳�?
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}