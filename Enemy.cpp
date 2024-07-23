#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Clear.h"
#include "PlaySound.h"
namespace {
	const SIZE IMAGESIZE{ 128,128 };
	const float LOOKRANGE{ 150 };
	const float ATTACKRANGE{ 101.5f };
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const VECTOR LUPOINT{ 34.0f,90.0f };	//左上の座標
	const VECTOR RUPOINT{ 94.0f,90.0f };	//右上の座標
	const VECTOR LDPOINT{ 34.0f,127.0f };	//左下の座標
	const VECTOR RDPOINT{ 94.0f,127.0f };	//右下の座標
	const SIZE HITBOXSIZE{ 60,37 };
	const float JUMPHEIGHT{ IMAGESIZE.cx * 1.5f };	//ジャンプの高さ
	const float MOVESPEED{ 85 };
	const float RUNSPEED{ 170 };	//ダッシュスピード
	const float ATTACKSPEED{ 1500 };
	const float SPEEDDOWN{ 50 };
	const float MOVETIME{ 1.0f };
}

float Enemy::EPDistance()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return 0.0;
	}

	float cenx = transform_.position_.x + LUPOINT.x;
	float ceny = transform_.position_.y + LUPOINT.y;

	float x = cenx - p->GetHitBoxPosition().x;
	float y = ceny - p->GetHitBoxPosition().y;

	DrawCircle(p->GetHitBoxPosition().x, p->GetHitBoxPosition().y, 3, GetColor(0, 255, 0), false);
	DrawCircle(cenx, ceny, 3, GetColor(0, 255, 0), false);

	return sqrt(x * x + y * y);
}

Enemy::Enemy(GameObject* parent)
	:Object(parent, "Enemy"), movetimer_(MOVETIME), startmove_(false), speed_(0), onGround_(false), range_(LOOKRANGE)
	,animtype_(EAnimation::IDOL),SpawnPoint_(transform_.position_),dir_(1),attackfrm_(0)
{

	/*アニメーション*/
	framecnt_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	AFmax_ = 0;

	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);
}

Enemy::~Enemy()
{
	if (hitobj_ != nullptr)
		delete hitobj_;
}

void Enemy::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\BlueSlimeScript.png");
	assert(hImage_ > 0);
}

void Enemy::Update()
{
	Player* p = GetParent()->FindGameObject<Player>();

	Field* field = GetParent()->FindGameObject<Field>();

	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag() || p == nullptr)
		return;

	//animtype_ = EAnimation::IDOL;
	onGround_ = false;
	Ppos = p->GetPosition();
	Gaccel += GRAVITY;
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

void Enemy::Draw()
{


	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE.cx, animtype_ * IMAGESIZE.cy, IMAGESIZE.cx,IMAGESIZE.cy, hImage_, true, dir_ - 1);

#if 1
	//発見範囲
	DrawCircle(xpos + IMAGESIZE.cx / 2, ypos + IMAGESIZE.cy / 2, ATTACKRANGE, GetColor(255, 0, 0), false);
	DrawCircle(xpos + IMAGESIZE.cx / 2, ypos + IMAGESIZE.cy / 2, range_, GetColor(255, 0, 0), false);

	DrawCircle(transform_.position_.x, transform_.position_.y, 5, GetColor(148,31, 48), false);
	DrawBox(transform_.position_.x, transform_.position_.y, transform_.position_.x + IMAGESIZE.cx, transform_.position_.y + IMAGESIZE.cy, GetColor(255, 255, 255), false);
	DrawCircle(transform_.position_.x + IMAGESIZE.cx / 2, transform_.position_.y + IMAGESIZE.cy / 2, 3, GetColor(0, 255, 0), true);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RDPOINT.x, ypos + RDPOINT.y, GetColor(255, 0, 0), false);
	DrawCircle(xpos+LDPOINT.x,ypos+LDPOINT.y,3,GetColor(0,0,255),false);
	DrawCircle(xpos+RDPOINT.x,ypos+RDPOINT.y,3,GetColor(0,0,255),false);
	EPDistance();
#endif
}

void Enemy::Release()
{
}

bool Enemy::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x + LUPOINT.x, transform_.position_.y + LUPOINT.y, HITBOXSIZE)) {
		return true;
	}

	return false;
}

void Enemy::AnimationCheck()
{

	//前フレームと違うアニメーションならカウントをゼロにする
	if (BEanimtype_ != animtype_) {
		framecnt_ = 0;
		animframe_ = 0;
	}
	if (animtype_ != EAnimation::ATTACK) {
		framecnt_++;
		if (framecnt_ > FCmax_) {
			framecnt_ = 0;
			animframe_ = (animframe_ + 1) % AFmax_;
		}
	}
	BEanimtype_ = animtype_;

}

void Enemy::DeadState()
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

bool Enemy::IsExistPlayer(float _range)
{
	if (powf(EPDistance(), 2) < _range * _range)
		return true;

	return false;
}

SIZE Enemy::GetImageSize()
{
	return IMAGESIZE;
}

void Enemy::UpdateIdol()
{
	AFmax_ = 8;
	FCmax_ = 20;


	//攻撃バッファ
	if (!startmove_) {
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = MOVETIME;
			startmove_ = true;
		}
	}
	else {
		speed_ = MOVESPEED;
		animtype_ = EAnimation::MOVE;
	}

}

void Enemy::UpdateMove()
{

	AFmax_ = 8;
	FCmax_ = 10;
	if (IsExistPlayer(range_)) {
		speed_ = RUNSPEED;
		range_ = LOOKRANGE * 2;
		animtype_ = EAnimation::RUN;
		return;
	}
	else
		range_ = LOOKRANGE;

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

void Enemy::UpdateRun()
{

	AFmax_ = 7;
	FCmax_ = 11;

	if (Ppos.x - transform_.position_.x < 0)
		dir_ = -1;
	else
		dir_ = 1;

	if (IsExistPlayer(range_)) {
		if (IsExistPlayer(ATTACKRANGE)) {
			speed_ = ATTACKSPEED;
			Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
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
		speed_ = MOVESPEED;
		range_ = LOOKRANGE;
		animtype_ = EAnimation::MOVE;
	}
	////動きの計算
	//if (IsExistPlayer() && !inmoving_ && startmove_) {
	//	inmoving_ = true;

	//	Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
	//	speed_ = ATTACKSPPED;
	//	trs = transform_;
	//}
	////動き
	//if (inmoving_) {

	//	transform_.position_.x += speed_ * Time::DeltaTime();
	//	speed_ -= SPEEDDOWN;
	//	if (speed_ < 0)
	//		speed_ = 0;
	//}
}

void Enemy::UpdateAttack()
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
	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;

	if (attackfrm_ == frm[i]&&i<4) {
		i++;
		rate++;
	}

	if (speed_ > 0)
		speed_ -= SPEEDDOWN - rate * 10;
	else
		speed_ = 0;
	attackfrm_++;

	if (onGround_) {
		speed_ = MOVESPEED;
		SpawnPoint_ = transform_.position_;
		animtype_ = EAnimation::IDOL;

	}
}

void Enemy::UpdateDeath()
{
	if (animframe_ == 2) {
		FCmax_ = 60;
		if (framecnt_ == 60) {
			KillMe();
		}
	}
}

void Enemy::Reset()
{
	Field* field = GetParent()->FindGameObject<Field>();

	int DLhit = field->CollisionDownCheck(transform_.position_.x + LDPOINT.x, transform_.position_.y + LDPOINT.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RDPOINT.x, transform_.position_.y + RDPOINT.y + 1);
	int push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
	}

	//右側当たり判定
	int Rhitx = transform_.position_.x + RDPOINT.x;
	int Rhity = transform_.position_.y + RDPOINT.y;
	push = field->CollisionRightCheck(Rhitx, Rhity);
	transform_.position_.x -= push;

	//左側当たり判定
	int Lhitx = transform_.position_.x + LDPOINT.x;
	int Lhity = transform_.position_.y + LDPOINT.y;
	push = field->CollisionLeftCheck(Lhitx, Lhity);
	transform_.position_.x += push;

	SpawnPoint_ = transform_.position_;
}

SIZE Enemy::GetSize() {
	return IMAGESIZE;
}

