#pragma once
//=============================================================
//	## commonMacroFunction ## (필요한 부분은 직접 만들어서 추가할것)
//=============================================================

struct fPOINT
{
	float x, y;
};

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 중심점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//렉탱글함수 이용해서 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void Rectangle(HDC hdc, RECT _rc)
{
	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

inline void Rectangle(HDC hdc, RECT _rc, int camX, int camY)
{
	Rectangle(hdc, _rc.left - camX, _rc.top - camY, _rc.right - camX, _rc.bottom - camY);
}

//일립스함수 이용해서 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//일립스함수 이용해서 센터점 중심으로 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//일립스함수 오버로딩
inline void Ellipse(HDC hdc, RECT _rc)
{
	Ellipse(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

inline void Ellipse(HDC hdc, RECT _rc, int camX, int camY)
{
	Ellipse(hdc, _rc.left - camX, _rc.top - camY, _rc.right - camX, _rc.bottom - camY);
}

//ADDED
//사각라인 그리기
inline void RectangleLine(HDC hdc, RECT _rc)
{
	MoveToEx(hdc, _rc.left, _rc.top, NULL);
	LineTo(hdc, _rc.left, _rc.bottom);
	LineTo(hdc, _rc.right, _rc.bottom);
	LineTo(hdc, _rc.right, _rc.top);
	LineTo(hdc, _rc.left, _rc.top);
}

//GetInt
inline int getInt(int num) { return rand() % num; }
//ADDED
//GetFromIntTo
inline int getFromIntTo(int fromNum, int toNum)
{
	if (fromNum > toNum)
		return rand() % (fromNum - toNum + 1) + toNum;
	else
		return rand() % (toNum - fromNum + 1) + fromNum;
}