#include "BackGround.h"
#include "Camera.h"

BackGround::BackGround(GameObject* parent)
	:GameObject(parent,"BackGround"),hImage_(0),hImagemove_(0)
{
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\BackGround4.png");
	assert(hImage_ > 0);

	hImagemove_ = LoadGraph("Assets\\Image\\forest.png");
	assert(hImagemove_ > 0);
}

void BackGround::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawGraph(0, 0, hImage_,false);


	for (int i = 0; i < 10; i++)
		DrawGraph(xpos + i * 1280, ypos, hImagemove_, true);

}

void BackGround::Release()
{
}
