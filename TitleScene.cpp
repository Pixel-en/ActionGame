#include "TitleScene.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent) : GameObject(parent)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	DrawString(0, 0, "TitleScene", GetColor(255, 0, 0));
}
