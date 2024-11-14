#include "Skeleton.h"

namespace {
	const VECTOR IMAGESIZE{ 64,64 };
	const VECTOR LUPOINT{ 10,8 };
	const VECTOR HITBOXSIZE{ 44,50 };
	const float MOVEXRANGE{ 200.0f };
}


Skeleton::Skeleton(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Eanim_.animtype_ = IDOL;
}

Skeleton::~Skeleton()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Skeleton::Initialize()
{
}

void Skeleton::Update()
{

}

void Skeleton::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, Eanim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, Eanim_.Rdir_);
	
	DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(255, 255, 255), false);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(255, 0, 0), false);

}

void Skeleton::Release()
{
}

bool Skeleton::EnemyAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox)
{
	return false;
}


void Skeleton::UpdateIdol()
{
}

void Skeleton::UpdateAttack()
{
}

void Skeleton::UpdateMove()
{
}

void Skeleton::UpdateRun()
{
}

void Skeleton::UpdateDamege()
{
}

void Skeleton::UpdateDeath()
{
}