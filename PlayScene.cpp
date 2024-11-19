#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Clear.h"
#include "BackGround.h"
#include "MoveObject.h"
#include "PlayGUI.h"
#include "ScoreAndTimeAndMap.h"

#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"
#include "Engine/CsvReader.h"

namespace {
	const float STIME{ 2.0f };
	const float CDTIME{ 5.0f };
	const float DTIME{ 1.0f };
	const float PTIME{ 180.0f };
}

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene"), Filename_("Test.csv"), starttimer_(STIME), state(PlayState::STAY), counttimer_(CDTIME),
	deathtimer_(DTIME), listnum(0)
{
}

void PlayScene::Initialize()
{

	Filename_ = "1-1.csv";

	//おそらくマップリストの読み込み

	Reset();

	
}

void PlayScene::Reset()
{

	KillAllChildren();

	Filename_ = ScoreAndTimeAndMap::NextMap();

	Clear* c = Instantiate<Clear>(this);
	Instantiate<Camera>(this);

	Instantiate<BackGround>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName(Filename_);
	Camera* cam = FindGameObject<Camera>();
	cam->SetValue(0);
	Instantiate<MoveObject>(this);

	Instantiate<Player>(this);

	f->Reset();
	//c->Reset();
	starttimer_ = STIME;
	counttimer_ = CDTIME;
	deathtimer_ = DTIME;
	ScoreAndTimeAndMap::Reset(PTIME);
	//playtimer_ = PTIME;
	state = PlayScene::STAY;
	isstart = false;

	Instantiate<PlayGUI>(this);
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

	if(CheckHitKey(KEY_INPUT_ESCAPE))
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
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
	if (starttimer_ < 0) {
		state = PlayScene::PLAY;
	}
	isstart = false;
}

void PlayScene::UpdatePlay()
{
	isstart = true;
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		counttimer_ -= Time::DeltaTime();
		if (counttimer_ < 0) {
			state = PlayScene::CLEAR;
		}
	}
	else {
		ScoreAndTimeAndMap::SubTimer(Time::DeltaTime());
		//playtimer_ -= Time::DeltaTime();
		if (ScoreAndTimeAndMap::GetTimer() < 0) {
			ScoreAndTimeAndMap::SetTimer(0.0);
			//playtimer_ = 0;
			state = PlayScene::DEATH;
		}
	}

	Player* p = FindGameObject<Player>();
	if (p->IsAnimState(p->RESET))
		state = PlayScene::DEATH;
}

void PlayScene::UpdateClear()
{
	if (ScoreAndTimeAndMap::IsLastMap()) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_CLEAR);
		return;
	}

	SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_RESULT);
	return;

}

void PlayScene::UpdateDeath()
{
	deathtimer_ -= Time::DeltaTime();
	if (deathtimer_ < 0) {
		Reset();
	}
}
