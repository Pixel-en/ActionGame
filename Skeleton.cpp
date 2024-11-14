#include "Skeleton.h"
#include "ImGui/imgui.h"

namespace {
	const VECTOR IMAGESIZE{ 64,64 };
	const VECTOR LUPOINT{ 10,8 };
	const VECTOR HITBOXSIZE{ 44,50 };
	const float MOVEXRANGE{ 200.0f };
	const float ATTACKRANGE{ 70.0f };
	const float DAMEGETIME{ 1.0f };
	const float ATTACKTIME{ 1.0f };
	const VECTOR EFFECTEXPLOSIONPOS{ 50,50 };
	const float DAMEGERANGE{ 200.0f };
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
	Eanim_.animloop_ = true;

	hitobj_->DownCollisionCheck();

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
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 11;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
		UpdateMove();
		break;
	case Enemy::RUN:
		Eanim_.AFmax_ = 4;
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
	int a = Eanim_.animtype_;
	ImGui::Begin("ske");
	ImGui::InputInt("type", &a);
	ImGui::End();

	AnimationCalculation();
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

	DrawCircle(originpos_.x - cam->GetValue(), originpos_.y - cam->GetValueY(), MOVEXRANGE, GetColor(255, 255, 255), false);
	//索敵範囲
	DrawCircle(xpos + LUPOINT.x + HITBOXSIZE.x / 2, ypos + LUPOINT.y + HITBOXSIZE.y / 2, Eparam_.range_, GetColor(0, 255, 0), false);
	//攻撃範囲
	DrawCircle(xpos + LUPOINT.x + HITBOXSIZE.x / 2, ypos + LUPOINT.y + HITBOXSIZE.y / 2, HITBOXSIZE.x / 2.0f + ATTACKRANGE, GetColor(255, 0, 0), false);


	XMFLOAT3 attacktrans_ = { GetCenterTransPos().x - DAMEGERANGE / 2.0f,GetCenterTransPos().y - DAMEGERANGE / 2.0f,0 };
	VECTOR attackhitbox_ = VGet(DAMEGERANGE, DAMEGERANGE, 0);

	DrawBox(attacktrans_.x - cam->GetValue(), attacktrans_.y - cam->GetValueY(), attacktrans_.x - cam->GetValue() + attackhitbox_.x, attacktrans_.y - cam->GetValueY() + attackhitbox_.y, GetColor(0, 255, 255), false);

}

void Skeleton::Release()
{
}

bool Skeleton::EnemyAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox)
{
	if (!isattack_)
		return false;

	XMFLOAT3 attacktrans_ = { GetCenterTransPos().x - DAMEGERANGE / 2.0f,GetCenterTransPos().y - DAMEGERANGE / 2.0f,0 };
	VECTOR attackhitbox_ = VGet(DAMEGERANGE, DAMEGERANGE, 0);

	bool set = hitobj_->HitObjectANDObject(attacktrans_, attackhitbox_, _trans, _hitbox);
	return set;

}


void Skeleton::UpdateIdol()
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

void Skeleton::UpdateAttack()
{
	Eanim_.animloop_ = true;
	if (attacktimer_ < 0){
		isattack_ = true;
		Effect* e = Instantiate<Effect>(GetParent());
		Transform trans;
		trans.position_ = { transform_.position_.x - EFFECTEXPLOSIONPOS.x,transform_.position_.y - EFFECTEXPLOSIONPOS.y ,transform_.position_.z };
		e->Reset(trans, e->EXPLOSION);
		e->SetEffectObjectName("EExplosionEffect");
		Eanim_.animtype_ = EAnimation::DEATH;
	}
	else
		attacktimer_ -= Time::DeltaTime();
}

void Skeleton::UpdateMove()
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

void Skeleton::UpdateRun()
{
	if (IsExistPlayer(HITBOXSIZE.x / 2.0f + ATTACKRANGE)) {
		Eanim_.animtype_ = EAnimation::ATTACK;
		attacktimer_ = ATTACKTIME;
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

void Skeleton::UpdateDamege()
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

void Skeleton::UpdateDeath()
{
	Eanim_.animloop_ = true;
	Effect* e;
	e = Instantiate<Effect>(GetParent());
	e->Reset(transform_, e->KILL);
	e->SetEffectObjectName("EKillEffect");
	KillMe();
}