#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Clear.h"

namespace {
	const SIZE IMAGESIZE{ 128,128 };
	const float LOOKRANGE{ 150 };
	const float ATTACKRANGE{ 101.5f };
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const VECTOR LUPOINT{ 34.0f,90.0f };	//左上の座標
	const VECTOR RUPOINT{ 94.0f,90.0f };	//右上の座標
	const VECTOR LDPOINT{ 34.0f,127.0f };	//左下の座標
	const VECTOR RDPOINT{ 94.0f,127.0f };	//右下の座標
	const SIZE HITBOXSIZE{ 45,46 };
	const float JUMPHEIGHT{ IMAGESIZE.cx * 1.5f };	//ジャンプの高さ
	const float MOVESPEED{ 85 };
	const float RUNSPEED{ 170 };	//ダッシュスピード
	const float ATTACKSPEED{ 1500 };
	const float SPEEDDOWN{ 70 };
	const float MOVETIME{ 1.0f };
}

float Enemy::EPDistance()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr)
		return 0.0;

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
	,animtype_(Animation::IDOL),SpawnPoint_(transform_.position_)
{

	/*アニメーション*/
	framecnt_=0;	
	FCmax_=0;	
	animframe_=0;
	AFmax_=0;
}

Enemy::~Enemy()
{
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

	if (clear->GetFlag())
		return;

	animtype_ = Animation::IDOL;
	onGround_ = false;


	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	//当たり判定
	int Rhitx = transform_.position_.x + RDPOINT.x;
	int Rhity = transform_.position_.y + RDPOINT.y;
	int push = field->CollisionRightCheck(Rhitx, Rhity);
	transform_.position_.x -= push;

	int Lhitx = transform_.position_.x + LDPOINT.x;
	int Lhity = transform_.position_.y + LDPOINT.y;
	push = field->CollisionLeftCheck(Lhitx, Lhity);
	transform_.position_.x += push;

	int DLhit = field->CollisionDownCheck(transform_.position_.x + LDPOINT.x, transform_.position_.y + LDPOINT.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RDPOINT.x, transform_.position_.y + RDPOINT.y + 1);
	push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
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

	//攻撃バッファ
	if (!startmove_) {
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = MOVETIME;
			startmove_ = true;
		}
	}

}

void Enemy::Draw()
{


	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();
	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE.cx, IMAGESIZE.cy, hImage_, true);

#if 1
	//発見範囲
	DrawCircle(xpos + IMAGESIZE.cx / 2, ypos + IMAGESIZE.cy / 2, ATTACKRANGE, GetColor(255, 0, 0), false);
	DrawCircle(xpos + IMAGESIZE.cx / 2, ypos + IMAGESIZE.cy / 2, range_, GetColor(255, 0, 0), false);

	DrawBox(transform_.position_.x, transform_.position_.y, transform_.position_.x + IMAGESIZE.cx, transform_.position_.y + IMAGESIZE.cy, GetColor(255, 255, 255), false);
	DrawCircle(transform_.position_.x + IMAGESIZE.cx / 2, transform_.position_.y + IMAGESIZE.cy / 2, 3, GetColor(0, 255, 0), true);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RDPOINT.x, ypos + RDPOINT.y, GetColor(255, 0, 0), false);
	EPDistance();
#endif
}

void Enemy::Release()
{
}

bool Enemy::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x+LUPOINT.x, transform_.position_.y+LUPOINT.y, HITBOXSIZE)) {
		p->KillMe();
		return true;
	}

	return false;
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
	animtype_ = Animation::MOVE;
}

void Enemy::UpdateMove()
{
	if(IsExistPlayer(LOOKRANGE)) {
		speed_ = RUNSPEED;
		range_ = LOOKRANGE * 2;
		animtype_ = Animation::RUN;
	}
}

void Enemy::UpdateRun()
{
	if (IsExistPlayer(range_)) {
		if (IsExistPlayer(ATTACKRANGE)) {
			speed_ = ATTACKSPEED;
			Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
			animtype_ = Animation::ATTACK;
		}
		else {
			transform_.position_.x += speed_ * Time::DeltaTime();
		}
	}
	else {
		speed_ = MOVESPEED;
		range_ = LOOKRANGE;
		animtype_ = Animation::MOVE;
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
	transform_.position_.x += speed_ * Time::DeltaTime();
	speed_ -= SPEEDDOWN;
	if (speed_ < 0)
		speed_ = 0;

	ImGui::Begin("aa");
	ImGui::InputFloat("s", &speed_);
	ImGui::End();
}

void Enemy::UpdateDeath()
{
}

