#include "ResultScene.h"
#include "ResultUI.h"
#include "BackGround.h"
#include "RankingsSystem.h"

ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

void ResultScene::Initialize()
{
	Instantiate<BackGround>(this);
	Instantiate<ResultUI>(this);
	Instantiate<RankingsSystem>(this);
}

void ResultScene::Update()
{
	//これに動く機能はついていない
	RankingsSystem* rank = FindGameObject<RankingsSystem>();
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
