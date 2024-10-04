#include "GreenSlime.h"
#include "Enemy.h"
#include "PlaySound.h"

GreenSlime::GreenSlime(GameObject* parent)
	:Enemy(parent)
{
	movetimer_ = baseMovetimer;
	startmove_ = false;
	speed_ = 0;
	onGround_ = false;
	range_ = ENEMY_LOOKRANGE;
	animtype_ = EAnimation::IDOL;
	SpawnPoint_ = transform_.position_;
	dir_ = 1;
	attackfrm_ = 0;
	hp_ = baseHp;
}

GreenSlime::~GreenSlime()
{
}

void GreenSlime::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\GreenSlimeScript.png");
	assert(hImage_ > 0);
}

void GreenSlime::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();

	Field* field = GetParent()->FindGameObject<Field>();

	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag() || p == nullptr)
		return;

	//animtype_ = EAnimation::IDOL;
	onGround_ = false;
	Ppos = p->GetPosition();
	Gaccel += ENEMY_GRAVITY;
	transform_.position_.y += Gaccel;


	short cflag = hitobj_->AllCollisionCheck();
	if (cflag & 0b1000 || cflag & 0b0100) {
		Gaccel = 0;
		onGround_ = true;
	}

	if (p == nullptr)
		return;
	//プレイヤーが死んでてもここまではする

	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		KillMe();
	}

	if (transform_.position_.y < 0)
		transform_.position_.y = 0;

	switch (animtype_)
	{
	case Enemy::IDOL:
		UpdateIdol();
		break;
	case Enemy::MOVE:
		UpdateMove();
		break;
	case Enemy::RUN:
		UpdateRun();
		break;
	case Enemy::ATTACK:
		UpdateAttack();
		break;
	case Enemy::DEATH:
		UpdateDeath();
		break;
	default:
		break;
	}

	AnimationCheck();
}

void GreenSlime::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	DrawRectGraph(xpos, ypos, 1 * animframe_ * ENEMY_IMAGESIZE.cx, animtype_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, dir_ - 1);
}

void GreenSlime::Release()
{
}

bool GreenSlime::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x + ENEMY_LUPOINT.x, transform_.position_.y + ENEMY_LUPOINT.y, ENEMY_HITBOXSIZE)) {
		return true;
	}

	return false;
}

SIZE GreenSlime::GetImageSize()
{
	return ENEMY_IMAGESIZE;
}

void GreenSlime::DeadState()
{
	if (animtype_ != EAnimation::DEATH) {
		Playsound* ps = GetParent()->FindGameObject<Playsound>();
		ps->SoundON("EDeath");
	}
	animtype_ = EAnimation::DEATH;
	FCmax_ = 20;
	AFmax_ = 3;
	framecnt_ = 0;
	animframe_ = 0;
}

SIZE GreenSlime::GetSize()
{
	return ENEMY_IMAGESIZE;
}


void GreenSlime::UpdateIdol()
{
	AFmax_ = 8;
	FCmax_ = 20;

	//攻撃バッファ
	if (!startmove_) {
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = baseMovetimer;
			startmove_ = true;
		}
	}
	else {
		speed_ = baseSpeed;
		animtype_ = EAnimation::MOVE;
	}
}

void GreenSlime::UpdateMove()
{
	AFmax_ = 8;
	FCmax_ = 10;
	if (IsExistPlayer(range_)) {
		speed_ = baseRunSpeed;
		range_ = ENEMY_LOOKRANGE * 2;
		animtype_ = EAnimation::RUN;
		return;
	}
	else
		range_ = ENEMY_LOOKRANGE;

	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;

	if (SpawnPoint_.x - transform_.position_.x > 30.0f) {
		dir_ = 1;
		transform_.position_.x = SpawnPoint_.x - 30.0f;
		startmove_ = false;
		animtype_ = EAnimation::IDOL;
	}
	else if (SpawnPoint_.x - transform_.position_.x < -30.0f) {
		dir_ = -1;
		transform_.position_.x = SpawnPoint_.x + 30.0f;
		startmove_ = false;
		animtype_ = EAnimation::IDOL;
	}
}

void GreenSlime::UpdateRun()
{
	AFmax_ = 7;
	FCmax_ = 11;

	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;

	if (IsExistPlayer(range_)) {
		if (IsExistPlayer(ENEMY_ATTACKRANGE)) {
			speed_ = ENEMY_ATTACKSPEED;
			Gaccel = -sqrtf(2 * ENEMY_GRAVITY * ENEMY_JUMPHEIGHT);
			Playsound* ps = GetParent()->FindGameObject<Playsound>();
			ps->SoundON("EAttack");
			animtype_ = EAnimation::ATTACK;
			attackfrm_ = 0;
			startmove_ = false;
		}
		else {
			transform_.position_.x += speed_ * Time::DeltaTime() * dir_;
		}
	}
	else {
		speed_ = baseSpeed;
		range_ = ENEMY_LOOKRANGE;
		animtype_ = EAnimation::MOVE;
	}
	////動きの計算
	//if (IsExistPlayer() && !inmoving_ && startmove_) {
	//	inmoving_ = true;
	//
	//	Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
	//	speed_ = ATTACKSPPED;
	//	trs = transform_;
	//}
	////動き
	//if (inmoving_) {
	//
	//	transform_.position_.x += speed_ * Time::DeltaTime();
	//	speed_ -= SPEEDDOWN;
	//	if (speed_ < 0)
	//		speed_ = 0;
	//}
}

void GreenSlime::UpdateAttack()
{
	if (attackfrm_ < 5)
		animframe_ = 3;
	else if (attackfrm_ < 40)
		animframe_ = 4;
	else if (attackfrm_ < 50)
		animframe_ = 5;
	else if (attackfrm_ < 60)
		animframe_ = 6;
	else if (attackfrm_ < 70)
		animframe_ = 7;
	else if (attackfrm_ < 80)
		animframe_ = 8;
	else if (attackfrm_ < 90)
		animframe_ = 9;

	int frm[4] = { 5,10,20,30 };
	static int i = 0;
	int rate = 0;
	//96f	48f
	transform_.position_.x += 140.0/*speed_*/ * Time::DeltaTime() * dir_;

	if (attackfrm_ == frm[i] && i < 4) {
		i++;
		rate++;
	}

	if (speed_ > 0)
		speed_ -= ENEMY_SPEEDDOWN - rate * 10;
	else
		speed_ = 0;
	attackfrm_++;

	if (onGround_) {
		speed_ = baseMovetimer;
		SpawnPoint_ = transform_.position_;
		animtype_ = EAnimation::IDOL;

	}
}

void GreenSlime::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}
