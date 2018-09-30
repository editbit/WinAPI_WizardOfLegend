#include "stdafx.h"
#include "Storage.h"

HRESULT Storage::init()
{
	_state = 1;
	_dir = 0;
	_index = 0;
	_power = 5;
	_isActive = true;



	///////////인벤
	_img = IMAGEMANAGER->findImage("inventory");
	_iconBoxImg[0] = IMAGEMANAGER->findImage("iconBox");
	_iconBoxImg[1] = IMAGEMANAGER->findImage("selectedIconBox");

	if (_skillList.size() > 0)
		release();
	_x = 100;
	_y = 50;

	_isActive = false;

	_iceDash = new IceDash;
	_iceDash->setLinkPlayer(_player);
	_iceDash->setLinkEnemyManager(_enemyManager);
	_iceDash->init();

	_fireDash = new FireDash;
	_fireDash->setLinkBulletList(BULLETMANAGER->getPlayerBullets());
	_fireDash->setLinkPlayer(_player);
	_fireDash->setLinkPixelMap(_pixelMap);
	//	_fireDash->setLinkEnemyManager(_enemyManager);
	_fireDash->init();

	_stoneAttack = new StoneAttack;
	_stoneAttack->setLinkBulletList(BULLETMANAGER->getPlayerBullets());
	_stoneAttack->setLinkPlayer(_player);
	_stoneAttack->setLinkPixelMap(_pixelMap);
	_stoneAttack->setLinkEnemyManager(_enemyManager);
	_stoneAttack->setMotion(0, IMAGEMANAGER->findImage("player_attack1"));
	_stoneAttack->setMotion(1, IMAGEMANAGER->findImage("player_attack2"));
	_stoneAttack->init();

	_waterThrowAttack = new WaterThrowAttack;
	_waterThrowAttack->setLinkBulletList(BULLETMANAGER->getPlayerBullets());
	_waterThrowAttack->setLinkPlayer(_player);
	_waterThrowAttack->setLinkPixelMap(_pixelMap);
	_waterThrowAttack->setLinkEnemyManager(_enemyManager);
	_waterThrowAttack->setMotion(0, IMAGEMANAGER->findImage("player_attack1"));
	_waterThrowAttack->setMotion(1, IMAGEMANAGER->findImage("player_attack2"));
	_waterThrowAttack->init();

	_stoneThrowAttack = new StoneThrowAttack;
	_stoneThrowAttack->setLinkBulletList(BULLETMANAGER->getPlayerBullets());
	_stoneThrowAttack->setLinkPlayer(_player);
	_stoneThrowAttack->setLinkPixelMap(_pixelMap);
	_stoneThrowAttack->setLinkEnemyManager(_enemyManager);
	_stoneThrowAttack->setMotion(0, IMAGEMANAGER->findImage("player_attack3"));
	_stoneThrowAttack->init();

	_waterCircleAttack = new WaterCircleAttack;
	_waterCircleAttack->setLinkBulletList(BULLETMANAGER->getPlayerBullets());
	_waterCircleAttack->setLinkPlayer(_player);
	_waterCircleAttack->setLinkPixelMap(_pixelMap);
	_waterCircleAttack->setLinkEnemyManager(_enemyManager);
	_waterCircleAttack->setMotion(0, IMAGEMANAGER->findImage("player_attack1"));
	_waterCircleAttack->setMotion(1, IMAGEMANAGER->findImage("player_attack2"));
	_waterCircleAttack->setMotion(2, IMAGEMANAGER->findImage("player_attack3"));
	_waterCircleAttack->init();


	_skillList.push_back(_fireDash);
	_skillList.push_back(_iceDash);
	_skillList.push_back(_stoneAttack);
	_skillList.push_back(_waterThrowAttack);
	_skillList.push_back(_stoneThrowAttack);
	_skillList.push_back(_waterCircleAttack);

	initSkillRECT();

	_selectIndex = -1;


	return S_OK;
}

void Storage::release()
{
	for (int i = 0; i < _skillList.size(); ++i)
	{
		_skillList[i]->release();
		SAFE_DELETE(_skillList[i]);
	}
	_skillList.clear();
	_iconPos.clear();
}

void Storage::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	selectSkill();
	//
	//	if (_selectIndex != -1)
	//		changeSkill();
	//}
}

void Storage::render()
{
	_img->render(getMemDC(), _renderPos.x - CAM->getX(), _renderPos.y - CAM->getY());

	for (int i = 0; i < _skillList.size(); ++i)
	{
		if (i == _selectIndex)
			_iconBoxImg[1]->render(UIMANAGER->getUIDC(), _iconPos[i].x - _iconBoxImg[1]->getWidth() / 2, _iconPos[i].y - _iconBoxImg[1]->getHeight() / 2);
		else
			_iconBoxImg[0]->render(UIMANAGER->getUIDC(), _iconPos[i].x - _iconBoxImg[0]->getWidth() / 2, _iconPos[i].y - _iconBoxImg[0]->getHeight() / 2);

		_skillList[i]->renderIcon(_iconPos[i].x, _iconPos[i].y);
	}

	if (_selectIndex >= 0)
	{
		SetTextColor(UIMANAGER->getUIDC(), RGB(255, 255, 255));
		SetTextAlign(UIMANAGER->getUIDC(), TA_LEFT);
		char str[500];
		sprintf_s(str, "%s", _skillList[_selectIndex]->getDescription().c_str());
		TextOut(UIMANAGER->getUIDC(), 150, 500, str, strlen(str));
		SetTextAlign(UIMANAGER->getUIDC(), TA_CENTER); //텍스트 중앙정렬
	}


	if (KEYMANAGER->isToggleKey('9'))
	{
		char str[20];
		sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
		TextOut(UIMANAGER->getUIDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
	}

}

void Storage::initSkillRECT()
{
	
	for (int i = 0; i < _skillList.size(); ++i)
	{
		_iconPos.push_back({ (int)_x + 58 + 16 + i * 55, (int)_y + 265 + 16 });
	}
}

void Storage::selectSkill()
{
	for (int i = 0; i < _skillList.size(); ++i)
	{
		if (PtInRect(&RectMakeCenter(_iconPos[i].x, _iconPos[i].y, _iconBoxImg[0]->getWidth(), _iconBoxImg[0]->getHeight()), _ptMouse))
		{
			_selectIndex = i;
		}
	}
}

Storage::Storage(Image * img, POINT renderPos)
	: Stuff(img, renderPos)
{

	init();
	_x = renderPos.x + img->getWidth() / 2;
	_y = renderPos.y + img->getHeight() / 2;

	_attackBox = RectMakeCenter(_x, _y, 200, 200);

}
