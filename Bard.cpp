#include "Bard.h"
#include "Player.h"

namespace {
	const VECTOR IMAGESIZE{ 80,80 };
	const VECTOR LUPOINT{ 10,10 };
	const VECTOR HITBOXSIZE{ 60,60 };
	const float IDOLTIME{ 3.0f };
	const float ATTACKRANGE{ 70.0f };
}

Bard::Bard(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Idoltimer_ = 0.0;
	sinangle_ = 0.0;
	Eanim_.animtype_ = IDOL;
	SetLUPOINT(LUPOINT);
	SetHitBox(HITBOXSIZE);
}

Bard::~Bard()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Bard::Initialize()
{
}

void Bard::Update()
{
	Eanim_.animloop_ = true;

	XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	SetCenterTransPos(pos, HITBOXSIZE);

	switch (Eanim_.animtype_)
	{
	case Enemy::NONE:
		AFmax_ = 0;
		FCmax_ = 0;
		break;
	case Enemy::IDOL:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 25;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
		UpdateMove();
		break;
	case Enemy::RUN:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
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

void Bard::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, Eanim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true,Eanim_.Rdir_);

	DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(255, 255, 255), false);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(255, 0, 0), false);
}

void Bard::Release()
{
}

void Bard::UpdateIdol()
{
	sinangle_ += 3.0f;
	float sinval = sinf(sinangle_ * DX_PI_F / 180.0f);
	transform_.position_.y = transform_.position_.y + sinval;
	dirchenge_ = false;
	Eanim_.animSkip_ = false;
	if (Idoltimer_ > 0) {
		Idoltimer_ -= Time::DeltaTime();
	}
	else {
		Idoltimer_ = IDOLTIME;
		Eanim_.animtype_ = EAnimation::MOVE;
	}
}

void Bard::UpdateAttack()
{

	transform_.position_.x -= targetvec_.x * speed * Time::DeltaTime();
	transform_.position_.y -= targetvec_.y * speed * Time::DeltaTime();
	if (GetCenterTransPos().x > targetpos_.x - 10 &&
		GetCenterTransPos().x<targetpos_.x + 10 &&
		GetCenterTransPos().y>targetpos_.y - 10 &&
		GetCenterTransPos().y < targetpos_.y + 10&&!dirchenge_) {
		targetvec_.x *= -1;
		targetvec_.y *= -1;
		dirchenge_ = true;
		SetCenterTransPos(targetpos_);
	}
	
	if (GetCenterTransPos().x > attackpos_.x - 10 &&
		GetCenterTransPos().x<attackpos_.x + 10 &&
		GetCenterTransPos().y>attackpos_.y - 10 &&
		GetCenterTransPos().y < attackpos_.y + 10&&dirchenge_) {
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		SetCenterTransPos(attackpos_);
		originpos_ = transform_.position_;
	}


}

void Bard::UpdateMove()
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
	if (originpos_.x - transform_.position_.x > Eparam_.moverange_ || moveLmax_) {
		if (!moveLmax_)
			transform_.position_.x = originpos_.x - Eparam_.moverange_;
		Eanim_.Rdir_ = true;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveLmax_ = false;
	}

	//右進行
	if (originpos_.x - transform_.position_.x < -Eparam_.moverange_ || moveRmax_) {
		if (!moveRmax_)
			transform_.position_.x = originpos_.x + Eparam_.moverange_;
		Eanim_.Rdir_ = false;
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		moveRmax_ = false;
	}
}

void Bard::UpdateRun()
{
	if (IsExistPlayer(HITBOXSIZE.x / 2.0f + ATTACKRANGE)) {
		Eanim_.animtype_ = EAnimation::ATTACK;
		Player* p = GetParent()->FindGameObject<Player>();
		targetvec_ = VGet(GetCenterTransPos().x - p->GetHitBoxCenterPosition().x, GetCenterTransPos().y - p->GetHitBoxCenterPosition().y, 0);
		targetvec_ = VNorm(targetvec_);
		targetpos_ = p->GetHitBoxCenterPosition();
		speed = Eparam_.runspeed_;
		attackpos_ = GetCenterTransPos();
		originpos_ = transform_.position_;
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

void Bard::UpdateDamege()
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

void Bard::UpdateDeath()
{
	Eanim_.animloop_ = true;
	Effect* e;
	e = Instantiate<Effect>(GetParent());
	e->Reset(transform_, e->KILL);
	e->SetEffectObjectName("EKillEffect");
	KillMe();
}