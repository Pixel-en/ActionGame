#include "Slime.h"
#include "Enemy.h"

Slime::Slime(GameObject* parent)
	:Enemy(parent)
{
	movetimer_ = baseMovetimer;
	startmove_ = false;
	speed_ = 0;
	onGround_ = false;
	range_ = ENEMY_LOOKRANGE;
	state_ = IDOL;
	SpawnPoint_ = transform_.position_;
	dir_ = 1;

	attackfrm_ = 0;
	hp_ = baseHp;
	hurtTime_ = baseHurtTime_;

	hitobj_ = new HitObject(ENEMY_HITBOXSIZE, this);
}

Slime::~Slime()
{
}

void Slime::Initialize()
{
}

void Slime::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();

	Field* field = GetParent()->FindGameObject<Field>();

	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag() || p == nullptr)
		return;

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

	if (CheckHitKey(KEY_INPUT_L))
	{
		state_ = HURT;
	}

	switch (state_)
	{
	case IDOL:
		AFmax_ = 4;
		FCmax_ = 25;
		UpdateIdol();
		break;
	case MOVE:
		AFmax_ = 5;
		FCmax_ = 20;
		UpdateMove();
		break;
	case RUN:
		AFmax_ = 5;
		FCmax_ = 11;
		UpdateRun();
		break;
	case ATTACK:
		AFmax_ = 5;
		FCmax_ = 11;
		UpdateAttack();
		break;
	case HURT:
		AFmax_ = 1;
		FCmax_ = 1;
		UpdateHurt();
		break;
	case DEATH:
		AFmax_ = 4;
		FCmax_ = 20;
		UpdateDeath();
		break;
	default:
		break;
	}

	AnimationCheck();
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

	DrawRectGraph(xpos - ENEMY_IMAGESIZE.cx / 2, ypos - (ENEMY_IMAGESIZE.cy - ENEMY_HITBOXSIZE.cy), animframe_ * ENEMY_IMAGESIZE.cx, state_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, (dir_ * -1) - 1);


	DrawLine(transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	DrawLine(transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	DrawLine(transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	DrawLine(transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
}

void Slime::Release()
{
}

SIZE Slime::GetImageSize()
{
	return ENEMY_IMAGESIZE;
}

void Slime::DeadState()
{
	if (state_ != DEATH) {
	}
	state_ = DEATH;
	
	framecnt_ = 0;
	animframe_ = 0;
}

void Slime::UpdateIdol()
{
	//攻撃バッファ
	if (!startmove_) {
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = 0;
			startmove_ = true;
		}
	}
	else {
		speed_ = baseSpeed;
		if (transform_.position_.x - SpawnPoint_.x >= 0)
		{
			dir_ = -1;
		}
		else
		{
			dir_ = 1;
		}
		movetimer_ = baseMovetimer;
		state_ = MOVE;
	}
}

void Slime::UpdateMove()
{	
	if (IsExistPlayer(range_)) {
		speed_ = baseRunSpeed;
		range_ = ENEMY_LOOKRANGE * 2;
		state_ = RUN;
		return;
	}
	else
		range_ = ENEMY_LOOKRANGE;

	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;

	if (SpawnPoint_.x - transform_.position_.x > 30.0f) {
		transform_.position_.x = SpawnPoint_.x - 30.0f;
		startmove_ = false;
		state_ = IDOL;
	}
	else if (SpawnPoint_.x - transform_.position_.x < -30.0f) {
		transform_.position_.x = SpawnPoint_.x + 30.0f;
		startmove_ = false;
		state_ = IDOL;
	}

}

void Slime::UpdateRun()
{
	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;

	if (IsExistPlayer(range_)) {
		if (IsExistPlayer(ENEMY_ATTACKRANGE)) {
			speed_ = ENEMY_ATTACKSPEED;
			Gaccel = -sqrtf(2 * ENEMY_GRAVITY * ENEMY_JUMPHEIGHT);
			state_ = ATTACK;
			attackfrm_ = 0;
			startmove_ = false;
		}
		else {
			transform_.position_.x += speed_ * Time::DeltaTime() * dir_;
		}
	}
}

void Slime::UpdateAttack()
{
	int frm[4] = { 5,10,20,30 };
	static int i = 0;
	int rate = 0;
	//96f	48f
	transform_.position_.x += 200.0/*speed_*/ * Time::DeltaTime() * dir_;

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
		speed_ = 0;
		SpawnPoint_ = transform_.position_;
		movetimer_ = baseMovetimer;
		state_ = IDOL;
	}
}

void Slime::UpdateHurt()
{
	hurtTime_ -= Time::DeltaTime();
	if (hurtTime_ <= 0)
	{
		hurtTime_ = baseHurtTime_;
		state_ = IDOL;
	}
}

void Slime::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}
