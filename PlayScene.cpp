#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Goal.h"
#include "Clear.h"

#include "ImGui/imgui.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),Filename_("alphamap.csv")
{
}

void PlayScene::Initialize()
{

	Filename_ = "tutorial1.csv";
	Reset();
}

void PlayScene::Reset()
{
	Instantiate<Camera>(this);
	Field* f = Instantiate<Field>(this);
	Instantiate<Goal>(this);
	Instantiate<Player>(this);
	f->SetFileName(Filename_);
	f->Reset();

	Clear* c = Instantiate<Clear>(this);
}

void PlayScene::Update()
{
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		Filename_ = "alphamap.csv";
		Reset();
	}

}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
