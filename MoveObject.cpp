#include "MoveObject.h"
#include "Camera.h"

namespace {
	const SIZE IMAGESIZE{ 192,32 };

}

MoveObject::MoveObject(GameObject* parent)
	:Object(parent,"MoveObject"),sinAngle_(0)
{

	VECTOR LUPOINT{ 0.0f,0.0f };
	VECTOR RUPOINT{ IMAGESIZE.cx,0.0f };
	VECTOR LDPOINT{ 0.0f,IMAGESIZE.cy };
	VECTOR RDPOINT{ IMAGESIZE.cx,IMAGESIZE.cy };

	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);
}

MoveObject::~MoveObject()
{
}

void MoveObject::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Lift.png");
	assert(hImage_ > 0);

}

void MoveObject::Update()
{
	sinAngle_ += 3.0f;
	float sinValue = sinf(sinAngle_ * DX_PI_F / 180.0f);
	//transform_.position_.y = baseY_ + sinValue * 50.0f;
}

void MoveObject::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);
}

void MoveObject::Release()
{
}

void MoveObject::Setpos(float x, float y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	baseY_ = y;
}
