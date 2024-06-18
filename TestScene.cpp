#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
}

//更新
void TestScene::Update()
{
	SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PLAY);
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
