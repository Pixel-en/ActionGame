#include "zombie.h"

Zombie::Zombie(GameObject* parent)
	:Enemy(parent)
{
	movetimer_ = baseMovetimer;
	startmove_ = false;
	speed_ = 0;
	onGround_ = false;
	range_ = ENEMY_LOOKRANGE * 5;
	state_ = IDOL;
	SpawnPoint_ = transform_.position_;
	dir_ = -1;

	attackfrm_ = 0;
	hp_ = baseHp;
	hurtTime_ = baseHurtTime_;

	hittransform_ = transform_;
	hittransform_.position_ = { transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2,transform_.position_.y - ENEMY_HITBOXSIZE.cy / 2,transform_.position_.z };

	hitobj_ = new HitObject(hittransform_, ENEMY_HITBOXSIZE, this);
}

Zombie::~Zombie()
{
}

void Zombie::Initialize()
{
}

void Zombie::Update()
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

	this->ConvertHitTransformtoTransform();

	if (p == nullptr)
		return;
	//ƒvƒŒƒCƒ„[‚ªŽ€‚ñ‚Å‚Ä‚à‚±‚±‚Ü‚Å‚Í‚·‚é

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
		AFmax_ = 3;
		FCmax_ = 25;
		UpdateIdol();
		break;
	case RUN:
		AFmax_ = 6;
		FCmax_ = 20;
		UpdateRun();
		break;
	case ATTACK:
		AFmax_ = 5;
		FCmax_ = 20;
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

void Zombie::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos - ENEMY_IMAGESIZE.cx / 2, ypos - (ENEMY_IMAGESIZE.cy - ENEMY_HITBOXSIZE.cy), animframe_ * ENEMY_IMAGESIZE.cx, state_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, (dir_ * -1) - 1);

}

void Zombie::Release()
{
}

SIZE Zombie::GetImageSize()
{
	return ENEMY_IMAGESIZE;
}

void Zombie::DeadState()
{
}

void Zombie::UpdateIdol()
{
	if (IsExistPlayer(range_)) {
		speed_ = baseSpeed;
		attackfrm_ = 0;
		startmove_ = false;
		TargetPoint_ = TargetPos();
		state_ = RUN;
	}
}

void Zombie::UpdateRun()
{
	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;
	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;

	if (!IsExistPlayer(range_)) {
		state_ = IDOL;
	}
	if (IsExistPlayer(ENEMY_ATTACKRANGE)) {
		speed_ = baseRunSpeed;
		state_ = ATTACK;
		attackfrm_ = 0;
		startmove_ = false;
	}
}

void Zombie::UpdateAttack()
{
	if (NowAnimFrame() == 2)
	{
		transform_.position_.x += speed_ * Time::DeltaTime() * dir_;
	}
	if (AnimationEnd()) {
		SpawnPoint_ = transform_.position_;
		state_ = IDOL;
	}
}

void Zombie::UpdateHurt()
{
	hurtTime_ -= Time::DeltaTime();
	if (hurtTime_ <= 0)
	{
		hurtTime_ = baseHurtTime_;
		state_ = IDOL;
	}
}

void Zombie::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}
