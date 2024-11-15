#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Clear.h"
#include "BackGround.h"
#include "MoveObject.h"
#include "PlayGUI.h"

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

	Filename_ = "Test.csv";

	//おそらくマップリストの読み込み
	CsvReader* csv = new CsvReader("Assets\\Map\\MapList.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		for (int j = 0; j < csv->GetColumns(0); j++) {
			maplist.push_back(csv->GetString(i, j));
		}
	}
	Filename_ = maplist[listnum];

	Reset();

	
}

void PlayScene::Reset()
{

	KillAllChildren();

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
	ScoreAndTime::Reset(PTIME);
	//playtimer_ = PTIME;
	state = PlayScene::STAY;

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
}

void PlayScene::UpdatePlay()
{
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		counttimer_ -= Time::DeltaTime();
		if (counttimer_ < 0) {
			state = PlayScene::CLEAR;
		}
	}
	else {
		ScoreAndTime::SubTime(Time::DeltaTime());
		//playtimer_ -= Time::DeltaTime();
		if (ScoreAndTime::GetTime() < 0) {
			ScoreAndTime::SetTime(0.0);
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
	listnum++;
	if (listnum >= maplist.size()) {
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_CLEAR);
		return;
	}
	Filename_ = maplist[listnum];
	Reset();
}

void PlayScene::UpdateDeath()
{
	deathtimer_ -= Time::DeltaTime();
	if (deathtimer_ < 0) {
		Reset();
	}
}
