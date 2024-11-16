#include "ClaerScene.h"
#include "Engine/SceneManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Camera.h"
#include "ClearPlayer.h"
#include "CleraLogo.h"
#include "OutText.h"
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

	Camera* cam=Instantiate<Camera>(this);

	Instantiate<BackGround>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName("Clear.csv");
	cam->SetValue(100);
	cam->SetValueY(300);
	f->Reset();
	Clearplayer* cp = Instantiate<Clearplayer>(this);
	ClearLogo* logo = Instantiate<ClearLogo>(this);
	OutText* tt = Instantiate<OutText>(this);
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
