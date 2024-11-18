#include "Slime.h"
#include "Player.h"

namespace {
	const VECTOR IMAGESIZE{ 48,48 };
	const VECTOR LUPOINT{ 0,15 };
	const VECTOR HITBOXSIZE{ 48,33 };
	const float ATTACKTIME{ 0.5f };
	const float ATTACKRANGE{ 50.0f };
	const float SPEEDDOWN{ 30.0f };
}

Slime::Slime(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Eanim_.animtype_ = IDOL;
	SetLUPOINT(LUPOINT);
	SetHitBox(HITBOXSIZE);
}

Slime::~Slime()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Slime::Initialize()
{
}

void Slime::Update()
{
	Eanim_.animloop_ = true;

	//重力
	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	if (hitobj_->DownCollisionCheck())
		Gaccel = 0.0f;

	XMFLOAT3 pos = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	SetCenterTransPos(pos, HITBOXSIZE);

	switch (Eanim_.animtype_)
	{
	case Enemy::NONE:
		Eanim_.AFmax_ = 0;
		Eanim_.AFCmax_ = 0;
		break;
	case Enemy::IDOL:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 25;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		Eanim_.AFmax_ = 5;
		Eanim_.AFCmax_ = 11;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		Eanim_.AFmax_ = 5;
		Eanim_.AFCmax_ = 20;
		UpdateMove();
		break;
	case Enemy::RUN:
		Eanim_.AFmax_ = 5;
		Eanim_.AFCmax_ = 11;
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

void Slime::Draw()
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

void Slime::Release()
{
}

void Slime::UpdateIdol()
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

void Slime::UpdateAttack()
{
	if (attacktimer_ > 0) {
		attacktimer_ -= Time::DeltaTime();
		Eanim_.animframe_ = 0;
		return;
	}

	Eanim_.animloop_ = true;
	transform_.position_.x -= targetvec_.x * speed * Time::DeltaTime();
	transform_.position_.y -= targetvec_.y * speed * Time::DeltaTime();
	speed -= SPEEDDOWN;
	if (speed < 0) {
		Eanim_.animtype_ = IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		originpos_ = transform_.position_;
	}
}

void Slime::UpdateMove()
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
		originpos_ = transform_.position_;
		Idoltimer_ = Eparam_.movetimer_;
		moveLmax_ = false;
	}

	//右進行
	if (originpos_.x - transform_.position_.x < -Eparam_.moverange_ || moveRmax_) {
		if (!moveRmax_)
			transform_.position_.x = originpos_.x + Eparam_.moverange_;
		Eanim_.Rdir_ = false;
		Eanim_.animtype_ = IDOL;
		originpos_ = transform_.position_;
		Idoltimer_ = Eparam_.movetimer_;
		moveRmax_ = false;
	}
}

void Slime::UpdateRun()
{

	PlayerDir();

	if (IsExistPlayer(HITBOXSIZE.x / 2.0f + ATTACKRANGE)) {
		Eanim_.animtype_ = EAnimation::ATTACK;
		Player* p = GetParent()->FindGameObject<Player>();
		targetvec_ = VGet(GetCenterTransPos().x - p->GetHitBoxCenterPosition().x, GetCenterTransPos().y - (p->GetHitBoxCenterPosition().y-50), 0);
		targetvec_ = VNorm(targetvec_);
		speed = Eparam_.runspeed_ * 6.0f;
		attacktimer_ = ATTACKTIME;
		return;
	}

	if (!IsExistPlayer(Eparam_.range_)) {
		Eanim_.animtype_ = Enemy::IDOL;
		Idoltimer_ = Eparam_.movetimer_;
		originpos_ = transform_.position_;
		return;
	}

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

void Slime::UpdateDamege()
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

void Slime::UpdateDeath()
{
	Eanim_.animloop_ = true;
	Effect* e;
	e = Instantiate<Effect>(GetParent());
	e->Reset(transform_, e->KILL);
	e->SetEffectObjectName("EKillEffect");
	KillMe();
}