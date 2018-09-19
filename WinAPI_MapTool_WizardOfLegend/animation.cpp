#include "stdafx.h"
#include "animation.h"

HRESULT Animation::init(int totalW, int totalH, int frameX, int frameY)
{
	//한프레임의 가로크기
	_frameWidth = totalW / frameX;

	//한프레임의 세로크기
	_frameHeight = totalH / frameY;

	//총프레임의 갯수
	_frameNum = frameX * frameY;

	//이미지 위치 세팅
	_frameList.clear();
	for (int i = 0; i < frameY; i++)
	{
		for (int j = 0; j < frameX; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 목록 벡터에 담기
			_frameList.push_back(framePos);
		}
	}

	//기본 프레임으로 세팅
	setPlayFrame();

	return S_OK;
}

void Animation::release()
{
}

//처음부터 끝까지 애니메이션 설정
void Animation::setPlayFrame(bool reverse, bool loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	if (reverse)
	{
		if (loop)
		{
			//정방향
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//정방향
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else//리버스가 아니다
	{
		//정방향
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}
//배열에 담아서 담겨있는것만 애니메이션 설정 (가장 많이 사용)
void Animation::setPlayFrame(int * playArr, int arrLen, bool loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//시작, 끝 구간을 정해서 애니메이션 설정
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	//시작과 끝 프레임 구간이 같은경우 재생할 필요 없다
	if (start == end)
	{
		stop();
		_playList.clear();
		return;
	}

	//시작프레임이 종료프레임보다 큰경우
	if (start > end)
	{
		int temp = start;
		start = end;
		end = temp;
	}

	if (reverse)
	{
		if (loop)
		{
			//정방향
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = end - 1; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//정방향
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = end - 1; i >= start; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else//리버스 아님
	{
		//정방향
		for (int i = start; i <= end; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	//플레이 중이냐?
	if (_play)
	{
		_elapsedSec += elapsedTime;
		//프레임 업데이트 시간이 다되었다면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_play = false;
				}
			}
		}
	}
}

void Animation::start()
{
	_play = true;
	_nowPlayIdx = 0;
}

void Animation::stop()
{
	_play = false;
	_nowPlayIdx = 0;
}

void Animation::pause()
{
	_play = false;
}

void Animation::resume()
{
	_play = true;
}
