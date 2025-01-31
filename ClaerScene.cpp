#include "ClaerScene.h"
#include "Engine/SceneManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Camera.h"
#include "ClearPlayer.h"
#include "CleraLogo.h"
#include "OutText.h"
#include"RankingsSystem.h"
#include "Clear.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent,"ClearScene"),hImage_(0)
{
}

void ClearScene::Initialize()
{

	Camera* cam=Instantiate<Camera>(this);

	Instantiate<BackGround>(this);
	Instantiate<Clear>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName("Clear.csv");
	cam->SetValue(100);
	cam->SetValueY(300);
	f->Reset();
	Clearplayer* cp = Instantiate<Clearplayer>(this);
	ClearLogo* logo = Instantiate<ClearLogo>(this);
	OutText* tt = Instantiate<OutText>(this);

	PlayMusic("Assets\\Sounds\\BGM\\Clear.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(255);
}

void ClearScene::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &pad);

	ClearLogo* logo = FindGameObject<ClearLogo>();
	if (logo->GetOutput()) {
		StopMusic();
		if(pad.Buttons[XINPUT_BUTTON_START]||CheckHitKey(KEY_INPUT_RETURN))
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
	}
}


void ClearScene::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_, true);

}

void ClearScene::Release()
{
}
