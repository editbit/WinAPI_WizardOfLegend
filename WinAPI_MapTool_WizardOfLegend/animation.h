#pragma once
//=============================================================
//	## Animation ## (애니메이션 클래스)
//=============================================================

class Animation
{
public:
	typedef vector<POINT> _vFrameList;	//프레임 임의접근이 가능하도록 퍼블릭선언
	typedef vector<int>	_vPlayList;		//프레임 플레이 목록(인덱스)

private:
	_vFrameList _frameList;		//프레임 위치 벡터
	_vPlayList _playList;		//플레이 목록 (인덱스)
	int _frameNum;				//프레임 갯수
	int _frameWidth;			//한프레임 가로길이
	int _frameHeight;			//한프레임 세로길이
	bool _loop;					//루프시킬거냐?

	float _frameUpdateSec;		//프레임 업데이트초
	float _elapsedSec;			//프레임 경과초
	DWORD _nowPlayIdx;			//현재 플레이 인덱스(플레이 목록값 참조)
	bool _play;					//플레이 중이냐?

public:
	//초기화(이미지 전체 가로길이, 세로길이, 가로갯수, 세로갯수)
	HRESULT init(int totalW, int totalH, int frameX, int frameY);
	void release();

	//처음부터 끝까지 애니메이션 설정
	void setPlayFrame(bool reverse = false, bool loop = false);
	//배열에 담아서 담겨있는것만 애니메이션 설정
	void setPlayFrame(int* playArr, int arrLen, bool loop = false);
	//시작, 끝 구간을 정해서 애니메이션 설정
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	//초당 갱신횟수
	void setFPS(int framePerSec);
	//프레임 업데이트
	void frameUpdate(float elapsedTime);

	//플레이 시작
	void start();
	//플레이 정지
	void stop();
	//일시정지
	void pause();
	//다시재생
	void resume();

	//필요한 겟터함수
	bool isPlay() { return _play; }
	POINT getFramePos() { return _frameList[_playList[_nowPlayIdx]]; }
	int getFrameWidth() { return _frameWidth; }
	int getFrameHeight() { return _frameHeight; }

	Animation() : _frameNum(0), _frameWidth(0), _frameHeight(0), _loop(false), _elapsedSec(0), _nowPlayIdx(0), _play(false) {}
	~Animation() {}
};

