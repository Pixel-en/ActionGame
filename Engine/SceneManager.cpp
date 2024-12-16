#include "sceneManager.h"

#include "../TestScene.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "../ClaerScene.h"
#include "../PlayPreparationScene.h"
#include "../TutorialScene.h"
#include "time.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	Time::Init();
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
	SE::InitSE();
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();
		InitGraph();

		std::string filename = "";

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this);	break;
		case SCENE_ID_TUTORIAL: Instantiate<TutorialScene>(this); break;
		case SCENE_ID_PREPARATION: Instantiate<PlayPreparationScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_CLEAR:Instantiate<ClearScene>(this); break;

		}
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
	Time::Refresh();
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
	StopMusic();
}