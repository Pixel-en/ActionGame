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
}

void PlayScene::Update()
{
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		c->Reset();
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
