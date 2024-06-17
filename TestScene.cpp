#include "TestScene.h"
#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Goal.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Field* f= Instantiate<Field>(this);
	Instantiate<Goal>(this);
	Instantiate<Player>(this);
	f->Reset();
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
