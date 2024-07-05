#include "BackGround.h"

BackGround::BackGround(GameObject* parent)
	:GameObject(parent,"BackGround"),hImage_(0)
{
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\middleground.png");
	assert(hImage_ > 0);
}

void BackGround::Draw()
{
	DrawGraph(0, 0, hImage_,false);
}

void BackGround::Release()
{
}
