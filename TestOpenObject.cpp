#include "TestOpenObject.h"
#include"Camera.h"

namespace Set{
	const float ANIM_TIME(0.1);
	const int FRAME_MAX(12);
	const int SizeX(64);
	const int SizeY(64);
}

TestOpenObject::TestOpenObject(GameObject* parent)
	:GameObject(parent,"OpenObject")
{
}

TestOpenObject::~TestOpenObject()
{
}

void TestOpenObject::Initialize()
{
	transform_.position_ = { 200,700,0 };
	hImage_ = LoadGraph("Assets\\Image\\Objects\\Present2_Open.png");
	
	GetGraphSize(hImage_, &weight, &hight);
	weight = weight / Set::FRAME_MAX;
	isAnim = true;
	frame = 0;
	timer = Set::ANIM_TIME;
}

void TestOpenObject::Update()
{
	if (isAnim) {
		if (timer < 0) {
			frame = (frame + 1) % Set::FRAME_MAX;
			if (frame == 0) {
				//KillMe();
			}
			timer = Set::ANIM_TIME;
		}
		else {
			timer -= Time::DeltaTime();
		}
	}

	//“–‚½‚è”»’è
	//if()
}

void TestOpenObject::Draw()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int tX = transform_.position_.x - cam->GetValue();
	int tY = transform_.position_.y - cam->GetValueY();

	DrawRectGraph(tX, tY,
		weight * frame, 0, weight, hight, hImage_, true);
	
	DrawBox(tX, tY,
		transform_.position_.x - cam->GetValue()+weight, tY+hight,
		255, false);
	DrawBox(tX, tY+hight-Set::SizeY,
		tX + Set::SizeX, tY+hight,
		GetColor(255,0,0), false);
}

void TestOpenObject::Release()
{
}
