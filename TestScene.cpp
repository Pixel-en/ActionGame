#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Field.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
}

//更新
void TestScene::Update()
{
	//SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
