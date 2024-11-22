#include "Zombie.h"
#include "ImGui/imgui.h"

namespace {
	const VECTOR IMAGESIZE{ 80,80 };
	const VECTOR LUPOINT{ 10,10 };
	const VECTOR HITBOXSIZE{ 60,70 };
	const float ATTACKRANGE{ 50.0f };

}

Zombie::Zombie(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
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

	//èdóÕ
	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	if (hitobj_->DownCollisionCheck())
		Gaccel = 0.0f;

	XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	SetCenterTransPos(pos, HITBOXSIZE);

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
		Eanim_.AFmax_ = 2;
		Eanim_.AFCmax_ = 10;
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
	if (Eanim_.animtype_ < 0)
		DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, 0 * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, Eanim_.Rdir_);
	else
		DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, Eanim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, Eanim_.Rdir_);

	//DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(255, 255, 255), false);
	//DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(255, 0, 0), false);
	////à⁄ìÆîÕàÕ
	//DrawCircle(originpos_.x - cam->GetValue(), originpos_.y - cam->GetValueY(), Eparam_.moverange_, GetColor(255, 255, 255), false);
	////çıìGîÕàÕ
	//DrawCircle(xpos + LUPOINT.x + HITBOXSIZE.x / 2, ypos + LUPOINT.y + HITBOXSIZE.y / 2, Eparam_.range_, GetColor(0, 255, 0), false);
	////çUåÇîÕàÕ
	//DrawCircle(xpos + LUPOINT.x + HITBOXSIZE.x / 2, ypos + LUPOINT.y + HITBOXSIZE.y / 2, HITBOXSIZE.x / 2.0f + ATTACKRANGE, GetColor(255, 0, 0), false);
	////çUåÇîªíËîÕàÕ
	//DrawBox(xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x + ATTACKRANGE, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(0, 0, 255), false);
	//DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x - ATTACKRANGE, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(0, 0, 255), false);
}

void Zombie::Release()
{
}

bool Zombie::EnemyAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox)
{
	if (!isattack_) {
		return false;
	}

	XMFLOAT3 attacktrans_;
	VECTOR attackhitbox_;

	if (Eanim_.Rdir_) {
		attacktrans_ = { transform_.position_.x + LUPOINT.x + HITBOXSIZE.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
		attackhitbox_ = VGet(ATTACKRANGE, HITBOXSIZE.y, 0);
	}
	else {
		attacktrans_ = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
		attackhitbox_ = VGet(-ATTACKRANGE, HITBOXSIZE.y, 0);
	}

	bool set = hitobj_->HitObjectANDObject(attacktrans_, attackhitbox_, _trans, _hitbox);
	return set;
}

void Zombie::UpdateIdol()
{
	isattack_ = false;

	if (Idoltimer_ > 0) {
		Idoltimer_ -= Time::DeltaTime();
	}
	else {
		if (IsExistPlayer(Eparam_.range_)) {
			Eanim_.animtype_ = Enemy::RUN;
		}
		else
			Eanim_.animtype_ = Enemy::MOVE;
	}
}

void Zombie::UpdateAttack()
{
	if (Eanim_.animframe_ == 2)
	{
		if(Eanim_.Rdir_)
		transform_.position_.x += Eparam_.runspeed_ * Time::DeltaTime();
		else
			transform_.position_.x -= Eparam_.runspeed_ * Time::DeltaTime();

	}
	Eanim_.animloop_ = false;
	isattack_ = true;
	Idoltimer_ = Eparam_.movetimer_;
	originpos_ = transform_.position_;
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
	//ç∂êiçs
	if (originpos_.x - transform_.position_.x > Eparam_.moverange_ || moveLmax_) {
		if (!moveLmax_)
			transform_.position_.x = originpos_.x - Eparam_.moverange_;
		Eanim_.Rdir_ = true;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveLmax_ = false;
	}

	//âEêiçs
	if (originpos_.x - transform_.position_.x < -Eparam_.moverange_ || moveRmax_) {
		if (!moveRmax_)
			transform_.position_.x = originpos_.x + Eparam_.moverange_;
		Eanim_.Rdir_ = false;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveRmax_ = false;
	}

}

void Zombie::UpdateRun()
{
	if (IsExistPlayer(HITBOXSIZE.x / 2.0f + ATTACKRANGE)) {
		Eanim_.animtype_ = EAnimation::ATTACK;
		return;
	}

	if (!IsExistPlayer(Eparam_.range_)) {
		Eanim_.animtype_ = Enemy::IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		originpos_ = transform_.position_;
		return;
	}

	PlayerDir();

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
}

void Zombie::UpdateDamege()
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

void Zombie::UpdateDeath()
{
	Eanim_.animloop_ = true;
	Effect* e;
	e = Instantiate<Effect>(GetParent());
	e->Reset(transform_, e->KILL);
	e->SetEffectObjectName("EKillEffect");
	KillMe();
}
