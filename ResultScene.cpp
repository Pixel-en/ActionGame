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
	//����ɓ����@�\�͂��Ă��Ȃ�
	RankingsSystem* rank = FindGameObject<RankingsSystem>();
	ResultUI* ui = FindGameObject<ResultUI>();
	if (rank != nullptr) {
		rank->DrawOK(ui->DrawRankOK());
		ui->isRecvok_(rank->RecvOK());
	}
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
