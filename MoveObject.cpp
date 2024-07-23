#include "MoveObject.h"
#include "Camera.h"
#include "ImGui/imgui.h"

namespace {
	const SIZE IMAGESIZE{ 48,48 };

}

MoveObject::MoveObject(GameObject* parent)
	:Object(parent,"MoveObject"),sinAngle_(0)
{

	VECTOR LUPOINT{ 0.0f,0.0f };
	VECTOR RUPOINT{ IMAGESIZE.cx,0.0f };
	VECTOR LDPOINT{ 0.0f,IMAGESIZE.cy };
	VECTOR RDPOINT{ IMAGESIZE.cx,IMAGESIZE.cy };

	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);
	ins = 0b000;

	left = nullptr;
	right = nullptr;
	center = nullptr;
}

MoveObject::~MoveObject()
{
}

void MoveObject::Initialize()
{
}

void MoveObject::Update()
{
	if (!(ins & 0b111))
		return;

	sinAngle_ += 1.0f;
	float sinValue = sinf(sinAngle_ * DX_PI_F / 180.0f);
	float move = baseY_ + sinValue * 100.0f;
	left->SetPosY(move);
	right->SetPosY(move);
	center->SetPosY(move);
	transform_.position_ = center->GetPosition();
}

void MoveObject::Draw()
{
	if (!(ins & 0b111))
		return;

	left->Draw();
	right->Draw();
	center->Draw();
}

void MoveObject::Release()
{
}

short MoveObject::CollisionCheck(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, Player* _obj,SIZE _boxsize)
{
	short temp = 0b0000;

	if (!(ins & 0b111))
		return temp;

	Transform trans_;
	trans_.position_ = _obj->GetPosition();

	VECTOR LUPOINT{ left->GetPosition().x,left->GetPosition().y };
	VECTOR RUPOINT{ right->GetPosition().x + IMAGESIZE.cx,right->GetPosition().y };
	VECTOR LDPOINT{ left->GetPosition().x,left->GetPosition().y + IMAGESIZE.cy / 2 };
	VECTOR RDPOINT{ right->GetPosition().x + IMAGESIZE.cx,right->GetPosition().y + IMAGESIZE.cy / 2 };
	SIZE BOXSIZE{ fabs(LUPOINT.x - RUPOINT.x),fabs(LUPOINT.y - LDPOINT.y) };
	
	if (_obj->HitCheck(LUPOINT.x, LUPOINT.y, BOXSIZE)) {
		//down
		if (max(abs(trans_.position_.y+ _Ld.y + 1 - LUPOINT.y),
			abs(trans_.position_.y + _Rd.y + 1 - RUPOINT.y)) >= 1
			
			&& max(abs(trans_.position_.y + _Ld.y + 1 - LUPOINT.y),
			abs(trans_.position_.y + _Rd.y + 1 - RUPOINT.y)) < BOXSIZE.cy) {
			
			int push = max(abs(trans_.position_.y + _Ld.y + 1 - LUPOINT.y), abs(trans_.position_.y +_Rd.y + 1 - RUPOINT.y));
			trans_.position_.y -= push - 1;
			temp |= 0b1000;
		}
		//up
		if (max(abs(trans_.position_.y + _Ld.y - 1 - LUPOINT.y),
			abs(trans_.position_.y + _Rd.y - 1 - RUPOINT.y)) >= 1

			&& max(abs(trans_.position_.y + _Ld.y - 1 - LUPOINT.y),
				abs(trans_.position_.y + _Rd.y - 1 - RUPOINT.y)) < BOXSIZE.cy) {

			int push = max(abs(trans_.position_.y + _Ld.y - 1 - LUPOINT.y), abs(trans_.position_.y + _Rd.y - 1 - RUPOINT.y));
			trans_.position_.y += push + 1;
			temp |= 0b0100;
		}
		//left
		if (abs(trans_.position_.y + _Ld.x - RDPOINT.x) >= 1 && abs(trans_.position_.y + _Ld.x - RDPOINT.x) < _boxsize.cx) {
			int push = abs(trans_.position_.y + _Ld.x - RDPOINT.x);
			transform_.position_.x += push;
			temp |= 0b0010;
		}
		//right
		if (abs(trans_.position_.y + _Rd.x - LDPOINT.x) >= 1 && abs(trans_.position_.y + _Rd.x - LDPOINT.x) < _boxsize.cx) {
			int push = abs(trans_.position_.y + _Rd.x - LDPOINT.x);
			transform_.position_.x -= push;
			temp |= 0b0001;
		}

		_obj->SetPosition(trans_.position_);
	}

	return temp;
}

MoveObject::Left::Left(GameObject* parent)
	:Object(parent, "Left")
{
	Invisible();
}

MoveObject::Left::~Left()
{
}

void MoveObject::Left::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Lift1.png");
	assert(hImage_ > 0);
}

void MoveObject::Left::Update()
{
}

void MoveObject::Left::Draw()
{

	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);
}

MoveObject::Right::Right(GameObject* parent)
	:Object(parent,"Right")
{
	Invisible();
}

MoveObject::Right::~Right()
{
}

void MoveObject::Right::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Lift3.png");
	assert(hImage_ > 0);
}

void MoveObject::Right::Update()
{
}

void MoveObject::Right::Draw()
{

	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);
}

MoveObject::Center::Center(GameObject* parent)
	:Object(parent,"Center")
{
	Invisible();
}

MoveObject::Center::~Center()
{
}

void MoveObject::Center::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Lift2.png");
	assert(hImage_ > 0);
}

void MoveObject::Center::Update()
{
}

void MoveObject::Center::Draw()
{

	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr){
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);
}
