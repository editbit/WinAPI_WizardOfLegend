#pragma once
#include "singletonBase.h"
//=============================================================
//	## SceneManager ## (씬 매니져)
//=============================================================

//싱글톤은 상속받은 아이들은 static으로 만들어 지기때문에 (스택 메모리공간)
//일반클래스인 게임노드를 사용하려고 하면 터진다

//게임노드 클래스 전방선언
class GameNode;

class SceneManager : public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//각각의 씬(화면)들을 담아둘 맵
	GameNode* _currentScene;	//현재씬

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬추가
	GameNode* addScene(string sceneName, GameNode* scene);
	//씬변경 (해당씬 로드)
	HRESULT loadScene(string sceneName);

	// 현재 씬 초기화
	HRESULT initScene();

	void exit();

	SceneManager() : _currentScene(NULL) {}
	~SceneManager() {}
};

//예시
/*씬추가*/
//SCENEMANAGER->addScene("픽셀충돌", new pixelCollision);
//SCENEMANAGER->addScene("테스트씬", new sceneTest);

/*현재씬 설정*/
//SCENEMANAGER->loadScene("테스트씬");
