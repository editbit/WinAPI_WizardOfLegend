#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT SceneManager::init(void)
{
	return S_OK;
}

void SceneManager::release(void)
{
	//정석적인 방법
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
	//현재씬이 존재하면 해당하는 현재씬을 업데이트해라
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	//현재씬이 존재하면 해당하는 현재씬을 렌더해라
	if (_currentScene) _currentScene->render();
}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//씬이 없으면 그냥 널 리턴
	if (!scene) return NULL;

	//씬이 있으면 맵에 담기
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았다면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같다면 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	if(_currentScene != NULL)
		_currentScene->release();
	//여기까지 왔으면 문제없이 씬 초기화 하고 변경해준다
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
