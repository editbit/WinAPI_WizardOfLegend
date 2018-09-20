#pragma once
//=============================================================
//	## commonMacroFunction ## (�ʿ��� �κ��� ���� ���� �߰��Ұ�)
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

//�� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT �߽����� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//���ʱ��Լ� �̿��ؼ� �׸���
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

//�ϸ����Լ� �̿��ؼ� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//�ϸ����Լ� �̿��ؼ� ������ �߽����� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//�ϸ����Լ� �����ε�
inline void Ellipse(HDC hdc, RECT _rc)
{
	Ellipse(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

inline void Ellipse(HDC hdc, RECT _rc, int camX, int camY)
{
	Ellipse(hdc, _rc.left - camX, _rc.top - camY, _rc.right - camX, _rc.bottom - camY);
}

//ADDED
//�簢���� �׸���
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