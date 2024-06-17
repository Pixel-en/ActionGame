#include "Goal.h"
#include "Camera.h"

Goal::Goal(GameObject* parent)
	:GameObject(parent,"Goal"),hImage_(-1)
{
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	hImage_ = LoadGraph("Assets\\Goal\\Goal_test.png");
	assert(hImage_ > 0);
}

void Goal::Update()
{
}

void Goal::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawRectGraph(xpos, ypos, 0, 0, 64, 64, hImage_, true);

}

void Goal::Release()
{
}
