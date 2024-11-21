#include "OpenObject.h"
#include"Camera.h"
#include "ScoreAndTimeAndMap.h"

namespace Set {
	const float ANIM_TIME(0.1);
	const int FRAME_MAX(12);
	const int SizeX(48);
	const int SizeY(48);
	const int Score(10);
}

OpenObject::OpenObject(GameObject* parent)
	:GameObject(parent, "OpenObject")
{
}

OpenObject::~OpenObject()
{
}

void OpenObject::Initialize()
{
	transform_.position_ = { 200,700,0 };
	transform_.position_ = { 200,800,0 };
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Present2_Open.png");

	GetGraphSize(hImage_, &weight, &hight);
	GetGraphSize(hImage_, &weight, &height);
	weight = weight / Set::FRAME_MAX;
	isAnim = true;
	isAnim = false;
	frame = 0;
	timer = Set::ANIM_TIME;
}

void OpenObject::Update()
{
	if (isAnim) {
		if (timer < 0) {
			frame = (frame + 1) % Set::FRAME_MAX;
			if (frame == 0) {
				ScoreAndTimeAndMap::AddScore(Set::Score);
				KillMe();
			}
			timer = Set::ANIM_TIME;
		}
		else {
			timer -= Time::DeltaTime();
		}
	}
}

void OpenObject::Draw()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int tX = transform_.position_.x - cam->GetValue();
	int tY = transform_.position_.y - cam->GetValueY();

	DrawRectGraph(tX, tY,
		weight * frame, 0, weight, hight, hImage_, true);

	DrawBox(tX, tY + height - Set::SizeY,
		tX + Set::SizeX, tY + height,
		GetColor(255, 0, 0), false);
	
	DrawBox(tX, tY + Set::SizeY,
		tX+GetHitBox().x, tY+ GetHitBox().y, GetColor(0, 255, 0), false);
}

void OpenObject::Release()
{
}
XMFLOAT3 OpenObject::GetHitTransPos()
{
	return XMFLOAT3({ transform_.position_.x,transform_.position_.y + Set::SizeY,transform_.position_.z });
}
VECTOR OpenObject::GetHitBox()
{
	return VECTOR({ Set::SizeX,Set::SizeY,0 });
}
void OpenObject::Open()
{
	isAnim = true;
}

void OpenObject::SetPos(int x, int y)
{
	transform_.position_.x = x - Set::SizeX/2;
	transform_.position_.y = y - Set::SizeY*1.5;
}
