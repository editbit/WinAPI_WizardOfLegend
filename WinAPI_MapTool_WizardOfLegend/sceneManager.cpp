#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT SceneManager::init(void)
{
	return S_OK;
}

void SceneManager::release(void)
{
	//�������� ���
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//for each(auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}
}

void SceneManager::update(void)
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ�ض�
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	//������� �����ϸ� �ش��ϴ� ������� �����ض�
	if (_currentScene) _currentScene->render();
}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//���� ������ �׳� �� ����
	if (!scene) return NULL;

	//���� ������ �ʿ� ���
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ���ٸ� E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	if(_currentScene != NULL)
		_currentScene->release();
	//������� ������ �������� �� �ʱ�ȭ �ϰ� �������ش�
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}
	
	return E_FAIL;
}

HRESULT SceneManager::initScene()
{
	_currentScene->release();
	_currentScene->init();
	return S_OK;
}

void SceneManager::exit()
{
	_currentScene->exit();
}
