#include "PlayPreparationScene.h"
#include "PlayPreparationPlayer.h"
#include "Engine/SceneManager.h"

PlayPreparationScene::PlayPreparationScene(GameObject* parent)
	:GameObject(parent,"PlayPreparationScene")
{
}

void PlayPreparationScene::Initialize()
{
	Instantiate<PlayPreparationPlayer>(this);
	hImage_ = LoadGraph("Assets\\Image\\PlayPreparationState.png");
}

void PlayPreparationScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PLAY);
}

void PlayPreparationScene::Draw()
{
	DrawGraph(100, 100, hImage_, true);
}

void PlayPreparationScene::Release()
{
}
