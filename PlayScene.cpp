#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Clear.h"

#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"

namespace {
	const float STIME{ 1.0f };
	const float CDTIME{ 5.0f };
	const float DTIME{ 1.0f };
	const float PTIME{ 60.0f };
}

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),Filename_("alphamap.csv"),starttimer_(STIME),state(PlayState::STAY),counttimer_(CDTIME),
	deathtimer_(DTIME),playtimer_(PTIME)
{
}

void PlayScene::Initialize()
{

	//Filename_ = "tutorial1.csv";
	Reset();
}

void PlayScene::Reset()
{
	KillAllChildren();

	Clear* c = Instantiate<Clear>(this);

	Instantiate<Camera>(this);
	Instantiate<Player>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName(Filename_);
	Camera* cam = FindGameObject<Camera>();
	cam->SetValue(0);

	f->Reset();
	starttimer_ = STIME;
	counttimer_ = CDTIME;
	deathtimer_ = DTIME;
	playtimer_ = PTIME;
	state = PlayScene::STAY;
	

}

void PlayScene::Update()
{

	switch (state)
	{
	case PlayScene::STAY:
		UpdateStay();
		break;
	case PlayScene::PLAY:
		UpdatePlay();
		break;
	case PlayScene::CLEAR:
		UpdateClear();
		break;
	case PlayScene::DEATH:
		UpdateDeath();
		break;
	default:
		break;
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

void PlayScene::DeadState()
{
	state = PlayState::DEATH;
}

void PlayScene::UpdateStay()
{
	starttimer_ -= Time::DeltaTime();
	if (starttimer_ < 0)
		state = PlayScene::PLAY;
}

void PlayScene::UpdatePlay()
{
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		counttimer_ -= Time::DeltaTime();
		if(counttimer_<0)
			state = PlayScene::CLEAR;
	}
	else {
		playtimer_ -= Time::DeltaTime();
		if (playtimer_ < 0) {
			playtimer_ = 0;
			state = PlayScene::DEATH;
		}
	}

	ImGui::Begin("timer");
	ImGui::InputFloat("timer", &playtimer_);
	float temp = Time::DeltaTime();
	ImGui::InputFloat("timer", &temp);
	ImGui::End();
}

void PlayScene::UpdateClear()
{

	Filename_ = "alphamap.csv";
	Reset();
}

void PlayScene::UpdateDeath()
{
	deathtimer_ -= Time::DeltaTime();
	if (deathtimer_ < 0)
		Reset();
}
