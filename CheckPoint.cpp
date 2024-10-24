#include "CheckPoint.h"
#include "Camera.h"

namespace {
	const SIZE IMAGESIZE{ 16,16 };
}

CheckPoint::CheckPoint(GameObject* parent)
	:Object(parent,"CheckPoint")
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Rune.png");
	assert(hImage_ > 0);

	hitobj_ = new HitObject(IMAGESIZE, this);
}

void CheckPoint::Update()
{
	framecnt_++;
	if (framecnt_ > 15) {
		framecnt_ = 0;
		animframe_ = (animframe_ + 1) % 4;
	}
}

void CheckPoint::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE.cx, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);
}

void CheckPoint::Release()
{
}
