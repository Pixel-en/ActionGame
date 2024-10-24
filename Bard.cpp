#include "Bard.h"
#include "Enemy.h"
#include "ImGui/imgui.h"

Bard::Bard(GameObject* parent)
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
	dir_y = 1;
	attackfrm_ = 0;
	hp_ = baseHp;
	hurtTime_ = baseHurtTime_;

	hittransform_ = transform_;
	hittransform_.position_ = { transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2,transform_.position_.y - ENEMY_HITBOXSIZE.cy / 2,transform_.position_.z };

	hitobj_ = new HitObject(hittransform_,ENEMY_HITBOXSIZE, this);

}

Bard::~Bard()
{
}

void Bard::Initialize()
{
}

void Bard::Update()
{
	hittransform_ = transform_;
	hittransform_.position_ = { transform_.position_.x -ENEMY_HITBOXSIZE.cx / 2
								,transform_.position_.y - ENEMY_HITBOXSIZE.cy / 2
								,transform_.position_.z };

	hitobj_->SetHitTransform(hittransform_);

	Player* p = GetParent()->FindGameObject<Player>();

	Field* field = GetParent()->FindGameObject<Field>();

	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag() || p == nullptr)
		return;

	//state_ = IDOL;
	onGround_ = true;
	Ppos = p->GetPosition();
	Gaccel += ENEMY_GRAVITY;
	//transform_.position_.y += Gaccel;


	//short cflag = hitobj_->AllCollisionCheck();
	//if (cflag & 0b1000 || cflag & 0b0100) {
	//	Gaccel = 0;
	//	onGround_ = true;
	//}

	//hitobj_->DownCollisionCheck();
	//hitobj_->UpCollisionCheck();
	//hitobj_->LeftCollisionCheck();
	//hitobj_->RightCollisionCheck();

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
		AFmax_ = 4;
		FCmax_ = 15;
		UpdateMove();
		break;
	case ATTACK:
		AFmax_ = 4;
		FCmax_ = 15;
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

	int temp = state_;
	ImGui::Begin("Enemy");
	ImGui::InputInt("state", &temp);
	ImGui::End();

	AnimationCheck();
}

void Bard::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	float hitxpos = hittransform_.position_.x;
	float hitypos = hittransform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
		hitxpos -= cam->GetValue();
		hitypos -= cam->GetValueY();
	}
	
	DrawRectGraph(xpos - ENEMY_IMAGESIZE.cx / 2, ypos - ENEMY_IMAGESIZE.cy / 2, animframe_ * ENEMY_IMAGESIZE.cx, state_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true);
	//DrawRectGraph(xpos , ypos, animframe_ * ENEMY_IMAGESIZE.cx, state_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true);

	DrawCircle(xpos, ypos, 3, GetColor(255, 255, 255), true);
	//DrawBox(xpos - ENEMY_IMAGESIZE.cx / 2, ypos - ENEMY_IMAGESIZE.cy / 2, xpos + ENEMY_IMAGESIZE.cx/2, ypos - ENEMY_IMAGESIZE.cy/ 2 + ENEMY_IMAGESIZE.cy, GetColor(255, 255, 255), false);
	//DrawBox(xpos, ypos, xpos + ENEMY_IMAGESIZE.cx, ypos + ENEMY_IMAGESIZE.cy, GetColor(255, 255, 255),false);

	//hitobj_->DrawHitBox({ hitxpos, hitypos, 0 },0, 255, 0);

	//hitobj_->DrawHitBox({ (float)xpos,(float)ypos,0 }, 255, 0, 0);



	//DrawLine(transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	//DrawLine(transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	//DrawLine(transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), transform_.position_.x - ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
	//DrawLine(transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y + ENEMY_HITBOXSIZE.cy - cam->GetValueY(), transform_.position_.x + ENEMY_HITBOXSIZE.cx / 2 - cam->GetValue(), transform_.position_.y - cam->GetValueY(), GetColor(255 / 255, 0 / 255, 0 / 255));
}

void Bard::Release()
{
}

SIZE Bard::GetImageSize()
{
	return ENEMY_IMAGESIZE;
}

void Bard::DeadState()
{
}

void Bard::UpdateIdol()
{
	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;
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
		movetimer_ = baseMovetimer;
		state_ = MOVE;
	}
}

void Bard::UpdateMove()
{
	if (IsExistPlayer(range_)) {
		speed_ = baseRunSpeed;
		speed_ = ENEMY_ATTACKSPEED;
		attackVector = EPVector();
		attackfrm_ = 0;
		startmove_ = false;
		attackVector = { attackVector.x / 150 ,attackVector.y / 150 ,0 };
		TargetPoint_ = TargetPos();
		state_ = ATTACK;
		
		return;
	}
	else
		range_ = ENEMY_LOOKRANGE;

	transform_.position_.y += speed_ * Time::DeltaTime() * dir_y;

	if (SpawnPoint_.y - transform_.position_.y > 30.0f) {
		dir_y = 1;
		transform_.position_.y = SpawnPoint_.y - 30.0f;
		startmove_ = false;
		//state_ = EAnimation::IDOL;
	}
	else if (SpawnPoint_.y - transform_.position_.y < -30.0f) {
		dir_y = -1;
		transform_.position_.y = SpawnPoint_.y + 30.0f;
		startmove_ = false;
	}
}

void Bard::UpdateRun()
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
			attackVector = EPVector();
			state_ = EAnimation::ATTACK;
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
		state_ = EAnimation::MOVE;
	}
}

void Bard::UpdateAttack()
{
	int frm[4] = { 5,10,20,30 };
	static int i = 0;
	int rate = 0;
	//96f	48f
	//transform_.position_.x += 200.0/*speed_*/ * Time::DeltaTime() * dir_;

	transform_.position_.x -= attackVector.x;
	hitobj_->RightCollisionCheck();
	hitobj_->LeftCollisionCheck();

	ConvertHitTransformtoTransform();
	transform_.position_.y -= attackVector.y;
	hitobj_->UpCollisionCheck();
	hitobj_->DownCollisionCheck();

	if (attackfrm_ == frm[i] && i < 4) {
		i++;
		rate++;
	}

	if (speed_ > 0)
		speed_ -= ENEMY_SPEEDDOWN - rate * 10;
	else
		speed_ = 0;
	attackfrm_++;

	speed_ = baseMovetimer;
	if (TargetPoint_.y - (transform_.position_.y + ENEMY_HITBOXSIZE.cy / 2) < attackVector.y && !yUp)
	{
		yUp = true;
		attackVector.x = attackVector.x * -1;
		attackVector.y = attackVector.y * -1;
	}
	if (transform_.position_.y < SpawnPoint_.y)
	{
		transform_.position_.x = SpawnPoint_.x;
		transform_.position_.y = SpawnPoint_.y;
		yUp = false;
		state_ = IDOL;
	}
}

void Bard::UpdateHurt()
{
	hurtTime_ -= Time::DeltaTime();
	if (hurtTime_ <= 0)
	{
		hurtTime_ = baseHurtTime_;
		state_ = IDOL;
	}
}

void Bard::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}
