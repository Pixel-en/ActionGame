#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "TitleText.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hImage_(0)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Title.png");
	assert(hImage_ > 0);

	Instantiate<TitleText>(this);
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	DrawGraph(0, 0, hImage_, true);


	TitleText* tt = FindGameObject<TitleText>();
	tt->DrawString("Play", 700, 500);
	tt->DrawString("Tutorial", 700, 550);
}
