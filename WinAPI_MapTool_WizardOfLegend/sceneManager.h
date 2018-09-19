#pragma once
#include "singletonBase.h"
//=============================================================
//	## SceneManager ## (�� �Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧���� (���� �޸𸮰���)
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//���ӳ�� Ŭ���� ���漱��
class GameNode;

class SceneManager : public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	GameNode* _currentScene;	//�����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���߰�
	GameNode* addScene(string sceneName, GameNode* scene);
	//������ (�ش�� �ε�)
	HRESULT loadScene(string sceneName);

	// ���� �� �ʱ�ȭ
	HRESULT initScene();

	void exit();

	SceneManager() : _currentScene(NULL) {}
	~SceneManager() {}
};

//����
/*���߰�*/
//SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
//SCENEMANAGER->addScene("�׽�Ʈ��", new sceneTest);

/*����� ����*/
//SCENEMANAGER->loadScene("�׽�Ʈ��");
