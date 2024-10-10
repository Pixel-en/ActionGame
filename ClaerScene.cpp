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

#if 0
#include"RankingsSystem.h"

int InputHandle;
char Name[256];
std::string PlayerName;
#endif


ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent,"ClearScene"),hImage_(0)
{
}

void ClearScene::Initialize()
{
	/*Playsound* pc = Instantiate<Playsound>(this);
	pc->PlayMusics("Clear");*/

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
	RankingsSystem* pR = Instantiate<RankingsSystem>(this);
}

void ClearScene::Update()
{
}


void ClearScene::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_, true);

}

void ClearScene::Release()
{
}
