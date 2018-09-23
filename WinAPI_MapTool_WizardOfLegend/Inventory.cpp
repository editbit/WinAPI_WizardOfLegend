#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_img = IMAGEMANAGER->findImage("inventory");
	_iconBoxImg[0] = IMAGEMANAGER->findImage("iconBox");
	_iconBoxImg[1] = IMAGEMANAGER->findImage("selectedIconBox");

	if (_skillList.size() > 0)
		release();
	_x = 100;
	_y = 50;

	for (int i = 0; i < EQUIP_MAX; ++i)
		_currentSkill[i] = NULL;

	_isActive = false;

	_iceDash = new IceDash;
	_iceDash->setLinkPlayer(_player);
	_iceDash->setLinkEnemyManager(_enemyManager);
	_iceDash->init();

	_fireDash = new FireDash;
	_fireDash->setLinkPlayer(_player);
	_fireDash->setLinkPixelMap(_pixelMap);
	_fireDash->setLinkEnemyManager(_enemyManager);
	_fireDash->init();

	_stoneAttack = new StoneAttack;
	_stoneAttack->setLinkPlayer(_player);
	_stoneAttack->setLinkPixelMap(_pixelMap);
	_stoneAttack->setLinkEnemyManager(_enemyManager);
	_stoneAttack->init();

	_skillList.push_back(_fireDash);
	_skillList.push_back(_iceDash);
	_skillList.push_back(_stoneAttack);

	initSkillRECT();

	_selectIndex = -1;


	_currentSkill[1] = _fireDash;
	_currentSkill[0] = _stoneAttack;

	return S_OK;
}

void Inventory::release()
{
	for (int i = 0; i < _skillList.size(); ++i)
	{
		_skillList[i]->release();
		SAFE_DELETE(_skillList[i]);
	}
	_skillList.clear();
	_iconPos.clear();
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_isActive = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		selectSkill();

		if (_selectIndex != -1)
			changeSkill();
	}
}

void Inventory::render()
{
	_img->render(UIMANAGER->getUIDC(), _x, _y);

	for (int i = 0; i < EQUIP_MAX; ++i)
	{
		_iconBoxImg[0]->render(UIMANAGER->getUIDC(), _currentSkillPos[i].x - _iconBoxImg[0]->getWidth() / 2, _currentSkillPos[i].y - _iconBoxImg[0]->getHeight() / 2);
		if (_currentSkill[i] == NULL)
			continue;
		
		_currentSkill[i]->renderIcon(_currentSkillPos[i].x, _currentSkillPos[i].y);
	}

	for (int i = 0; i < _skillList.size(); ++i)
	{
		if(i == _selectIndex)
			_iconBoxImg[1]->render(UIMANAGER->getUIDC(), _iconPos[i].x - _iconBoxImg[1]->getWidth() / 2, _iconPos[i].y - _iconBoxImg[1]->getHeight() / 2);
		else
			_iconBoxImg[0]->render(UIMANAGER->getUIDC(), _iconPos[i].x - _iconBoxImg[0]->getWidth()/2, _iconPos[i].y - _iconBoxImg[0]->getHeight()/2);


		_skillList[i]->renderIcon(_iconPos[i].x, _iconPos[i].y);
	}

	if (KEYMANAGER->isToggleKey('9'))
	{
		char str[20];
		sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
		TextOut(UIMANAGER->getUIDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));
	}
}

void Inventory::renderEquipSkill()
{
	for (int i = 0; i < EQUIP_MAX; ++i)
	{
		_iconBoxImg[0]->render(UIMANAGER->getUIDC(), _equipkillPos[i].x - _iconBoxImg[0]->getWidth() / 2, _equipkillPos[i].y - _iconBoxImg[0]->getHeight() / 2);
		if (_currentSkill[i] == NULL)
			continue;

		_currentSkill[i]->renderIcon(_equipkillPos[i].x, _equipkillPos[i].y);
	}
}

void Inventory::initSkillRECT()
{
	for (int i = 0; i < EQUIP_MAX; ++i)
	{
		_currentSkillPos[i] = { (int)_x + 58 + 16 + i * 57, (int)_y + 80 + 16 };
		_equipkillPos[i] = {100 + i * 55, WINSIZEY - 100};
	}

	for (int i = 0; i < _skillList.size(); ++i)
	{
		_iconPos.push_back({ (int)_x + 58 + 16 + i * 55, (int)_y + 265 + 16});
	}
	//158 315
}

void Inventory::changeSkill()
{
	for (int i = 0; i < EQUIP_MAX; ++i)
	{
		if (PtInRect(&RectMakeCenter(_currentSkillPos[i].x, _currentSkillPos[i].y, _iconBoxImg[0]->getWidth(), _iconBoxImg[0]->getHeight()), _ptMouse))
		{
			if (_skillList[_selectIndex]->getSkillType() == DASH_SKILL && i != 1)
				continue;
			if (_skillList[_selectIndex]->getSkillType() == ATTACK_SKILL && i == 1)
				continue;

			_currentSkill[i] = _skillList[_selectIndex];

			break;
		}
	}
}

void Inventory::selectSkill()
{
	for (int i = 0; i < _skillList.size(); ++i)
	{
		if (PtInRect(&RectMakeCenter(_iconPos[i].x, _iconPos[i].y, _iconBoxImg[0]->getWidth(), _iconBoxImg[0]->getHeight()), _ptMouse))
		{
			_selectIndex = i;
		}
	}
}
