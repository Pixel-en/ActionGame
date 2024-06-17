#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Goal.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Field* f= Instantiate<Field>(this);
	Instantiate<Goal>(this);
	Instantiate<Player>(this);
	f->Reset();
}

//�X�V
void TestScene::Update()
{
	//SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
