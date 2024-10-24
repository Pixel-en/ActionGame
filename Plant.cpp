#include "Plant.h"
#include "Enemy.h"

Plant::Plant(GameObject* parent)
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

Plant::~Plant()
{
}

void Plant::Initialize()
{
}

void Plant::Update()
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
	case ATTACK:
		AFmax_ = 4;
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

void Plant::Draw()
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

void Plant::Release()
{
}

SIZE Plant::GetImageSize()
{
	return ENEMY_IMAGESIZE;
}

void Plant::DeadState()
{
	if (state_ != DEATH) {
	}
	state_ = DEATH;

	framecnt_ = 0;
	animframe_ = 0;
}

void Plant::UpdateIdol()
{
	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;

	

	if (startmove_ && IsExistPlayer(range_))
	{
		movetimer_ = baseMovetimer;
		attackfrm_ = 0;
		TargetPoint_ = TargetPos();
		startmove_ = false;
		bullet_ = Instantiate<Bullet>(GetParent());
		bullet_->Initialize(dir_, FIRE);
		bullet_->SetPosition(transform_.position_);
		state_ = ATTACK;
		return;
	}
	else 
	{
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = 0;
			startmove_ = true;
		}
	}
}

void Plant::UpdateAttack()
{
	if (AnimationEnd()) {
		SpawnPoint_ = transform_.position_;
		state_ = IDOL;
	}
}

void Plant::UpdateHurt()
{
	hurtTime_ -= Time::DeltaTime();
	if (hurtTime_ <= 0)
	{
		hurtTime_ = baseHurtTime_;
		state_ = IDOL;
	}
}

void Plant::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}
