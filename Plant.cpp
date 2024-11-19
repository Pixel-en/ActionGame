#include "Plant.h"
#include "Bullet.h"
#include "ImGui/imgui.h"

namespace {
	const VECTOR IMAGESIZE{ 80,80 };
	const VECTOR LUPOINT{ 10,10 };
	const VECTOR HITBOXSIZE{ 60,70 };
	const int ATTACKRANGE{ 200 };
}

Plant::Plant(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	SetLUPOINT(LUPOINT);
	SetHitBox(HITBOXSIZE);
	Idoltimer_ = Eparam_.movetimer_;
}

Plant::~Plant()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Plant::Initialize()
{
}

void Plant::Update()
{
	Eanim_.animloop_ = true;

	if (hitobj_->DownCollisionCheck())
		Gaccel = 0.0f;

	switch (Eanim_.animtype_)
	{
	case Enemy::NONE:
		Eanim_.AFmax_ = 3;
		Eanim_.AFCmax_ = 25;
		UpdateNone();
		break;
	case Enemy::IDOL:
		Eanim_.AFmax_ = 3;
		Eanim_.AFCmax_ = 25;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 20;
		UpdateAttack();
		break;
	case Enemy::DAMEGE:
		Eanim_.AFmax_ = 2;
		Eanim_.AFCmax_ = 10;
		UpdateDamege();
		break;
	case Enemy::DEATH:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 10;
		UpdateDeath();
		break;
	}

	AnimationCalculation();
}

void Plant::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	if (Eanim_.animtype_ < 0)
		DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, 0 * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, Eanim_.Rdir_);
	else
	DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, Eanim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true,Eanim_.Rdir_);

	DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(255, 255, 255), false);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(255, 0, 0), false);
}

void Plant::Release()
{
}


void Plant::UpdateIdol()
{
	if (Idoltimer_ > 0) {
		Idoltimer_ -= Time::DeltaTime();
	}
	else {
		XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
		SetCenterTransPos(pos, HITBOXSIZE);
		if (IsExistPlayer(Eparam_.range_)) {
			Eanim_.animtype_ = Enemy::ATTACK;
		}
	}
}

void Plant::UpdateAttack()
{
	PlayerDir();

	XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	Eanim_.animloop_ = false;
	if (Eanim_.animframe_ == 1 && Eanim_.animframecount_ == 1) {
		Bullet* b = GetParent()->FindGameObject<Bullet>("PlantBullet");
		if (b == nullptr) {
			b = Instantiate<Bullet>(GetParent());
			if (Eanim_.Rdir_)
				b->Set(1, BULLET_TYPE::FIRE, pos, ATTACKRANGE, "Player");
			else
				b->Set(-1, BULLET_TYPE::FIRE, pos, ATTACKRANGE, "Player");
			b->SetBulletObjectName("PlantBullet");
		}
		Idoltimer_ = Eparam_.movetimer_;
	}
}

void Plant::UpdateDamege()
{
	Eanim_.animloop_ = true;
	if (damegetimer_ > 0) {
		damegetimer_ -= Time::DeltaTime();
	}
	else {
		damegetimer_ = DAMEGETIME;
		Eanim_.animtype_ = IDOL;
	}
}

void Plant::UpdateDeath()
{
	Eanim_.animloop_ = true;
	Effect* e;
	e = Instantiate<Effect>(GetParent());
	e->Reset(transform_, e->KILL);
	e->SetEffectObjectName("EKillEffect");
	KillMe();

}
