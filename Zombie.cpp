#include "Zombie.h"

namespace{
	const VECTOR IMAGESIZE{ 80,80 };
	const VECTOR LUPOINT{10,10};
	const VECTOR HITBOXSIZE{ 60,70 };
	const float MOVEXRANGE{ 200.0f };
}

Zombie::Zombie(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Eanim_.animtype_ = IDOL;
	SetLUPOINT(LUPOINT);
	SetHitBox(HITBOXSIZE);
	Idoltimer_ = Eparam_.movetimer_;

}

Zombie::~Zombie()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Zombie::Initialize()
{
}

void Zombie::Update()
{

	Eanim_.animloop_ = true;
	
	//重力
	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;
	
	if (hitobj_->DownCollisionCheck())
		Gaccel = 0.0f;

	switch (Eanim_.animtype_)
	{
	case Enemy::NONE:
		Eanim_.AFmax_ = 0;
		Eanim_.AFCmax_ = 0;
		break;
	case Enemy::IDOL:
		Eanim_.AFmax_ = 3;
		Eanim_.AFCmax_ = 25;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		Eanim_.AFmax_ = 5;
		Eanim_.AFCmax_ = 20;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		Eanim_.AFmax_ = 6;
		Eanim_.AFCmax_ = 25;
		UpdateMove();
		break;
	case Enemy::RUN:
		Eanim_.AFmax_ = 6;
		Eanim_.AFCmax_ = 20;
		UpdateRun();
		break;
	case Enemy::DAMEGE:
		Eanim_.AFmax_ = 1;
		Eanim_.AFCmax_ = 1;
		UpdateDamege();
		break;
	case Enemy::DEATH:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 20;
		UpdateDeath();
		break;
	}

	AnimationCalculation();
}

void Zombie::Draw()
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
	DrawCircle(originpos_.x-cam->GetValue(), originpos_.y-cam->GetValueY(), MOVEXRANGE, GetColor(255, 255, 255), false);
}

void Zombie::Release()
{
}

void Zombie::UpdateIdol()
{
	if (Idoltimer_ > 0) {
		Idoltimer_ -= Time::DeltaTime();
	}
	else {
		XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
		SetCenterTransPos(pos, HITBOXSIZE);
		if (IsExistPlayer(Eparam_.range_)) {
			Eanim_.animtype_ = Enemy::RUN;
		}
		else
			Eanim_.animtype_ = Enemy::MOVE;
	}
}

void Zombie::UpdateAttack()
{
}

void Zombie::UpdateMove()
{
	if (IsExistPlayer(Eparam_.range_)) {
		Eanim_.animtype_ = Enemy::RUN;
		return;
	}

	if (Eanim_.Rdir_) {
		transform_.position_.x += Eparam_.speed_ * Time::DeltaTime();
		if (hitobj_->RightCollisionCheck())
			moveRmax_ = true;
	}
	else {
		transform_.position_.x -= Eparam_.speed_ * Time::DeltaTime();
		if (hitobj_->LeftCollisionCheck())
			moveLmax_ = true;
	}
	//左進行
	if (originpos_.x - transform_.position_.x > MOVEXRANGE||moveLmax_) {
		if (!moveLmax_)
			transform_.position_.x = originpos_.x - MOVEXRANGE;
		Eanim_.Rdir_ = true;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveLmax_ = false;
	}
	
	//右進行
	if (originpos_.x - transform_.position_.x < -MOVEXRANGE||moveRmax_) {
		if (!moveRmax_)
			transform_.position_.x = originpos_.x + MOVEXRANGE;
		Eanim_.Rdir_ = false;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveRmax_ = false;
	}

}

void Zombie::UpdateRun()
{

	if (Eanim_.Rdir_) {
		transform_.position_.x += Eparam_.runspeed_ * Time::DeltaTime();
		if (hitobj_->RightCollisionCheck())
			moveRmax_ = true;
	}
	else {
		transform_.position_.x -= Eparam_.runspeed_ * Time::DeltaTime();
		if (hitobj_->LeftCollisionCheck())
			moveLmax_ = true;
	}
	//左進行
	if (originpos_.x - transform_.position_.x > MOVEXRANGE || moveLmax_) {
		if (!moveLmax_)
			transform_.position_.x = originpos_.x - MOVEXRANGE;
		Eanim_.Rdir_ = true;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveLmax_ = false;
	}

	//右進行
	if (originpos_.x - transform_.position_.x < -MOVEXRANGE || moveRmax_) {
		if (!moveRmax_)
			transform_.position_.x = originpos_.x + MOVEXRANGE;
		Eanim_.Rdir_ = false;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveRmax_ = false;
	}
}

void Zombie::UpdateDamege()
{
}

void Zombie::UpdateDeath()
{
}
