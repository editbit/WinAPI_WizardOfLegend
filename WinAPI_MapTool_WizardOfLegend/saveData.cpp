#include "stdafx.h"
#include "saveData.h"
#include "Wizard.h"
#include "EnemyManager.h"

HRESULT SaveData::init()
{
	return S_OK;
}

void SaveData::release()
{
	if (_player != NULL)
	{
		_player->release();
		SAFE_DELETE(_player);
	}
	if (_enemyManager != NULL)
	{
		_enemyManager->release();
		SAFE_DELETE(_enemyManager);
	}
	
}

