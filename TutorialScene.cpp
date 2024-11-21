#include "TutorialScene.h"
#include "Field.h"
#include "Player.h"
#include "Camera.h"
#include "BackGround.h";
#include "Clear.h"
#include "Engine/SceneManager.h"
#include "TutorialUI.h"

namespace {
	const float CLEARTIME{ 1.0f };
}

TutorialScene::TutorialScene(GameObject* parent)
	:GameObject(parent,"TutorialScene"),cleartimer_(CLEARTIME)
{
}

void TutorialScene::Initialize()
{
	Clear* c = Instantiate<Clear>(this);
	Camera* cam = Instantiate<Camera>(this);

	Instantiate<BackGround>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName("Tutorial.csv");
	cam->SetValue(0);

	Instantiate<Player>(this);
	f->Reset();
	Instantiate<TutorialUI>(this);
}

void TutorialScene::Update()
{
	Clear* c = FindGameObject<Clear>();
	if (c->GetFlag()) {
		cleartimer_ -= Time::DeltaTime();
		if (cleartimer_ < 0) {
			SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
		}
	}
}

void TutorialScene::Draw()
{
}

void TutorialScene::Release()
{
}
