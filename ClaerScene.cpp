#include "ClaerScene.h"
#include "Engine/SceneManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Camera.h"
#include "ClearPlayer.h"
#include "CleraLogo.h"
#include "TitleText.h"
#include "PlaySound.h"

#include"RankingsSystem.h"

char* Name;

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent,"ClearScene"),hImage_(0)
{
}

void ClearScene::Initialize()
{
	Playsound* pc = Instantiate<Playsound>(this);
	pc->PlayMusics("Clear");

	Camera* cam=Instantiate<Camera>(this);

	Instantiate<BackGround>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName("Clear.csv");
	cam->SetValue(100);
	cam->SetValueY(300);
	f->Reset();
	Clearplayer* cp = Instantiate<Clearplayer>(this);
	ClearLogo* logo = Instantiate<ClearLogo>(this);
	TitleText* tt = Instantiate<TitleText>(this);
}

void ClearScene::Update()
{

	KeyInputString(300, 300, 10, Name,TRUE);
	if(CheckHitKey(KEY_INPUT_RETURN)) {
		StopSound();
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
	}
	RankingsSystem::SetRankings(GetKeyInputString(Name,),);
}

void ClearScene::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_, true);

	DrawString(300, 350, "–¼‘O‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢", GetColor(255, 255, 255));


}

void ClearScene::Release()
{
}
