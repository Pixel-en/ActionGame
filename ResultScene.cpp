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

	PlayMusic("Assets\\Sounds\\BGM\\Result.mp3",DX_PLAYTYPE_LOOP);
	SetVolumeMusic(200);
}

void ResultScene::Update()
{
	//これに動く機能はついていない
	RankingsSystem* rank = FindGameObject<RankingsSystem>();
	ResultUI* ui = FindGameObject<ResultUI>();
	if (rank != nullptr) {
		rank->DrawOK(ui->DrawRankOK());
		ui->isRecvok_(rank->RecvOK());
	}
	//シーン移動とBGMのストップはResultUIについてる
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
