#pragma once
#include "singletonBase.h"
/*FMOD 사용하기 위해*/
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;
//=============================================================
//	## SoundManager ## (사운드 매니져)
//=============================================================

//사용할 사운드버퍼 (사운드갯수가 30개가 넘어가면 크기를 더 늘려줘야 한다)
#define SOUNDBUFFER 30

class SoundManager : public SingletonBase <SoundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//시스템 클래스
	Sound** _sound;			//사운드 클래스
	Channel** _channel;		//채널 클래스

	arrSound _mTotalSound;	//맵에 담아둘 사운드들

	string _currentSound;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	//사운드 추가(키값, 파일이름, BGM?, 루프시킬꺼냐?)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	void playBgm(string keyName, float volume = 1.0f);
	void playBgm(float volume = 1.0f);
	//사운드 재생
	void play(string keyName, float volume = 1.0f);//볼륨은 0.0f ~ 1.0f
	void setVolume(float volume = 1.0f);//볼륨은 0.0f ~ 1.0f
	//사운드 정지
	void stop(string keyName);
	//사운드 일시정지
	void pause(string keyName);
	//사운드 다시재생
	void resume(string keyName);

	//플레이 중이냐?
	bool isPlaySound(string keyName);
	//일시정지 중이냐?
	bool isPauseSound(string keyName);

	SoundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~SoundManager() {}
};

