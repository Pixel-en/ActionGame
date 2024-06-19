#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Goal.h"
#include "Clear.h"

#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"

namespace {
	const float STIME{ 1.0f };
	const float CDTIME{ 5.0f };
}

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),Filename_("alphamap.csv"),starttimer_(STIME),state(PlayState::STAY),counttimer_(CDTIME)
{
}

void PlayScene::Initialize()
{
	Instantiate<Camera>(this);
	Instantiate<Field>(this);
	Instantiate<Player>(this);

	Filename_ = "tutorial1.csv";
	Reset();

	Clear* c = Instantiate<Clear>(this);
}

void PlayScene::Reset()
{
	Field* f = FindGameObject<Field>();
	f->SetFileName(Filename_);
	f->Reset();
	Camera* cam = FindGameObject<Camera>();
	cam->SetValue(0);
	starttimer_ = STIME;
	counttimer_ = CDTIME;
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
}

void PlayScene::UpdateClear()
{
	Clear* c = FindGameObject<Clear>();
	c->Reset();
	Filename_ = "alphamap.csv";
	Reset();
}

void PlayScene::UpdateDeath()
{
}
