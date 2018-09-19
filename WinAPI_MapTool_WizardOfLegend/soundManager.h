#pragma once
#include "singletonBase.h"
/*FMOD ����ϱ� ����*/
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;
//=============================================================
//	## SoundManager ## (���� �Ŵ���)
//=============================================================

//����� ������� (���尹���� 30���� �Ѿ�� ũ�⸦ �� �÷���� �Ѵ�)
#define SOUNDBUFFER 30

class SoundManager : public SingletonBase <SoundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//�ý��� Ŭ����
	Sound** _sound;			//���� Ŭ����
	Channel** _channel;		//ä�� Ŭ����

	arrSound _mTotalSound;	//�ʿ� ��Ƶ� �����

	string _currentSound;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	//���� �߰�(Ű��, �����̸�, BGM?, ������ų����?)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	void playBgm(string keyName, float volume = 1.0f);
	void playBgm(float volume = 1.0f);
	//���� ���
	void play(string keyName, float volume = 1.0f);//������ 0.0f ~ 1.0f
	void setVolume(float volume = 1.0f);//������ 0.0f ~ 1.0f
	//���� ����
	void stop(string keyName);
	//���� �Ͻ�����
	void pause(string keyName);
	//���� �ٽ����
	void resume(string keyName);

	//�÷��� ���̳�?
	bool isPlaySound(string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound(string keyName);

	SoundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~SoundManager() {}
};
