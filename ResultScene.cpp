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
	//‚±‚ê‚É“®‚­‹@”\‚Í‚Â‚¢‚Ä‚¢‚È‚¢
	RankingsSystem* rank = FindGameObject<RankingsSystem>();
	ResultUI* ui = FindGameObject<ResultUI>();
	rank->DrawOK(ui->DrawRankOK());
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
