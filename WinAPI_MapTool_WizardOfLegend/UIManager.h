#pragma once
#include "singletonBase.h"
#include "image.h"

enum UI_TYPE
{
	EXIT_MENU, OPTION_MENU
};

class ProgressBar;

class OptionUI
{
public:
	int x, y;

	Image *optionBtnImg;
	Image *optionImg;

	RECT volumeRect[2];
	bool selectVolumeBtn;

	RECT effectVolumeRect[2];
	bool selectEffectVolumeBtn;


	OptionUI();
};

class ExitUI
{
public:
	int x, y;
	Image *exitMenuImg;

	RECT btnRect[4];
	int selectBtnIndex;

	ExitUI();
};

class UIManager :
	public SingletonBase<UIManager>
{
private:
	Image * _flickeringImg;
	Image * _uiDC;
	

	bool _isDrawUI;

	HBRUSH brush, oBrush;

	////// flickering
	
	int _alpha;
	int _count;
	int _speed;
	COLORREF _color;

	
	///////
	bool _isBlockingUI;
	int _uiType;
	OptionUI _optionUI;
	ExitUI _exitUI;

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

	void updateOptionUI();
	void renderOptionUI(HDC hdc);

	void updateExitUI();
	void renderExitUI(HDC hdc);

	void openUI(int uiType) { _uiType = uiType; _isBlockingUI = true; }

	/////////////


	UIManager() : _isDrawUI(false), _isBlockingUI(false) {}
	~UIManager() {}
};

