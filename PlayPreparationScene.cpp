#include "PlayPreparationScene.h"
#include "PlayPreparationPlayer.h"
#include "PlayPreparationState.h"
#include "Engine/SceneManager.h"

PlayPreparationScene::PlayPreparationScene(GameObject* parent)
	:GameObject(parent,"PlayPreparationScene")
{
}

void PlayPreparationScene::Initialize()
{
	Instantiate<PlayPreparationPlayer>(this);
	Instantiate<PlayPreparationState>(this);

}

void PlayPreparationScene::Update()
{
	PlayPreparationState* s = FindGameObject<PlayPreparationState>();
	if (s->GetStartFlag())
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PLAY);
}

void PlayPreparationScene::Draw()
{
	
}

void PlayPreparationScene::Release()
{
}
