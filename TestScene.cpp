#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Field.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
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
