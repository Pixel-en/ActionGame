#include "Goal.h"
#include "Camera.h"

namespace {
	const VECTOR IMAGESIZE{ 48,48 };
}

Goal::Goal(GameObject* parent)
	:Object(parent,"Goal")
{
	SIZE temp;
	temp.cx = IMAGESIZE.x;
	temp.cy = IMAGESIZE.y;
	hitsize_ = temp;
	
}

Goal::~Goal()
{
	if (hitobj_ != nullptr)
		delete hitobj_;
	hitobj_ = nullptr;
}

void Goal::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Flag.png");
	assert(hImage_ > 0);
	//hitobj_ = new HitObject({ 0.0f,0.0f }, { IMAGESIZE,0.0f }, { 0.0f,IMAGESIZE }, { IMAGESIZE,IMAGESIZE }, this);
	hitobj_ = new HitObject({ IMAGESIZE }, this);
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
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE.x, 0, IMAGESIZE.x, IMAGESIZE.x, hImage_, true);
}

void Goal::Release()
{
}
