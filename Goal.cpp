#include "Goal.h"
#include "Camera.h"

namespace {
	const int IMAGESIZE{ 48 };
}

Goal::Goal(GameObject* parent)
	:Object(parent,"Goal")
{
	hitsize_ = { IMAGESIZE,IMAGESIZE };
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Flag.png");
	assert(hImage_ > 0);
	hitobj_ = new HitObject({ 0.0f,0.0f }, { IMAGESIZE,0.0f }, { 0.0f,IMAGESIZE }, { IMAGESIZE,IMAGESIZE }, this);
}

void Goal::Update()
{
	framecnt_++;
	if (framecnt_ > 15) {
		framecnt_ = 0;
		animframe_ = (animframe_ + 1) % 4;
	}
}

void Goal::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, 0, IMAGESIZE, IMAGESIZE, hImage_, true);
}

void Goal::Release()
{
}
