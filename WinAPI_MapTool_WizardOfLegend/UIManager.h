#pragma once
#include "singletonBase.h"
#include "image.h"

class ProgressBar;

class UIManager :
	public SingletonBase<UIManager>
{
private:
	Image * _flickeringImg;
	Image * _uiDC;
	
	int _uiType;

	bool _isDrawUI;

	HBRUSH brush, oBrush;

	////// flickering
	
	int _alpha;
	int _count;
	int _speed;
	COLORREF _color;

	
	///////
	bool _isBlockingUI;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void flickering(COLORREF color, int speed, int count);

	bool checkBlocking() { return _isBlockingUI; }
	bool checkDrawingUI() { return _isDrawUI; }
	void clear();
	HDC getUIDC() { return _uiDC->getMemDC(); }


	/////////////

	bool getIsBlockingUI() { return _isBlockingUI; }
	void setIsBlockingUI(bool isBlocking) { _isBlockingUI = isBlocking; }

	void updateVolumeUI();
	void renderVolumeUI();

	/////////////


	UIManager() : _isBlockingUI(false), _isDrawUI(false) {}
	~UIManager() {}
};

