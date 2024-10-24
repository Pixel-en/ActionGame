#include "Enemy.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "PlaySound.h"
#include "Engine/CsvReader.h"


float Enemy::EPDistance()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return 0.0;
	}

	float cenx = transform_.position_.x /*- ENEMY_HITBOXSIZE.cx*/;
	float ceny = transform_.position_.y /*- ENEMY_HITBOXSIZE.cy*/;

	float x = cenx - p->GetHitBoxPosition().x;
	float y = ceny - p->GetHitBoxPosition().y;

	DrawCircle(p->GetHitBoxPosition().x, p->GetHitBoxPosition().y, 3, GetColor(0, 255, 0), false);
	DrawCircle(cenx, ceny, 3, GetColor(0, 255, 0), false);

	return sqrt(x * x + y * y);
}

XMFLOAT3 Enemy::EPVector()
{
	XMFLOAT3 v;
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return{ 0,0,0 };
	}
	v = { transform_.position_.x - p->GetPosition().x,transform_.position_.y - p->GetPosition().y,0 };
	return v;
}

XMFLOAT3 Enemy::TargetPos()
{
	XMFLOAT3 v;
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return{ 0,0,0 };
	}
	v = {p->GetPosition()};
	return v;
}

void Enemy::StatusReader(int _enemyNumber)
{
	CsvReader* csv = new CsvReader("Assets\\Status\\EnemyStatus.csv");
	for (int i = 1; i < ENEMY_TYPE_END+1; i++) {
		if (_enemyNumber == csv->GetInt(i, 0))
		{
			baseSpeed = csv->GetInt(i, 1);
			baseRunSpeed = csv->GetInt(i, 2);
			baseHp = csv->GetInt(i, 3);
			baseMovetimer = csv->GetInt(i, 4);
			speed_ = baseSpeed;
			hp_ = baseHp;
			movetimer_ = baseMovetimer;
			filename = csv->GetString(i, 5);
			filename = "Assets\\Image\\Enemy\\" + filename + "_sprite.png";
			hImage_ = LoadGraph(filename.c_str());
			assert(hImage_ > 0);
		}
	}

}

Enemy::Enemy(GameObject* parent)
	:Object(parent, "Enemy"), movetimer_(1.0f), startmove_(false), speed_(0), onGround_(false), range_(ENEMY_LOOKRANGE)
	,state_(EAnimation::IDOL),SpawnPoint_(transform_.position_),dir_(1),attackfrm_(0)
{

	/*アニメーション*/
	framecnt_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	AFmax_ = 0;

	//hitobj_ = new HitObject(ENEMY_LUPOINT, ENEMY_RUPOINT, ENEMY_LDPOINT, ENEMY_RDPOINT, this);
	hitobj_ = new HitObject(ENEMY_IMAGESIZE, this);
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

	switch (state_)
	{
	case IDOL:
		UpdateIdol();
		break;
	case MOVE:
		UpdateMove();
		break;
	case RUN:
		UpdateRun();
		break;
	case ATTACK:
		UpdateAttack();
		break;
	case HURT:
		UpdateHurt();
		break;
	case DEATH:
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
	DrawRectGraph(xpos, ypos, 1 * animframe_ * ENEMY_IMAGESIZE.cx, state_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, dir_ - 1);
}

void Enemy::Release()
{
}

bool Enemy::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x, transform_.position_.y, ENEMY_HITBOXSIZE)) {
		return true;
	}

	return false;
}

void Enemy::AnimationCheck()
{
	//前フレームと違うアニメーションならカウントをゼロにする
	if (BEanimtype_ != state_) {
		framecnt_ = 0;
		animframe_ = 0;
	}
	/*if (state_ != EAnimation::ATTACK) {
		framecnt_++;
		if (framecnt_ > FCmax_) {
			framecnt_ = 0;
			animframe_ = (animframe_ + 1) % AFmax_;
		}
	}*/
	framecnt_++;
	if (framecnt_ > FCmax_) {
		framecnt_ = 0;
		animframe_ = (animframe_ + 1) % AFmax_;
	}
	BEanimtype_ = state_;
}

bool Enemy::AnimationEnd()
{
	if(animframe_ == AFmax_-1 && framecnt_ == FCmax_)
		return true;
	return false;
}

int Enemy::NowAnimFrame()
{
	return animframe_;
}

void Enemy::DeadState()
{
	if (state_ != EAnimation::DEATH) {
		Playsound* ps = GetParent()->FindGameObject<Playsound>();
		ps->SoundON("EDeath");
	}
	state_ = EAnimation::DEATH;
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
	return ENEMY_IMAGESIZE;
}

void Enemy::UpdateIdol()
{
}

void Enemy::UpdateMove()
{
}

void Enemy::UpdateRun()
{
}

void Enemy::UpdateAttack()
{
}

void Enemy::UpdateHurt()
{
}

void Enemy::UpdateDeath()
{
}

void Enemy::Reset()
{
	Field* field = GetParent()->FindGameObject<Field>();
	int push;
	//int DLhit = field->CollisionDownCheck(transform_.position_.x - (ENEMY_IMAGESIZE.cx / 2), transform_.position_.y + (ENEMY_IMAGESIZE.cy / 2) + 1);
	//int DRhit = field->CollisionDownCheck(transform_.position_.x + (ENEMY_IMAGESIZE.cx / 2), transform_.position_.y + (ENEMY_IMAGESIZE.cy / 2) + 1);
	////int DLhit = field->CollisionDownCheck(transform_.position_.x + ENEMY_LDPOINT.x, transform_.position_.y + ENEMY_LDPOINT.y + 1);
	////int DRhit = field->CollisionDownCheck(transform_.position_.x + ENEMY_RDPOINT.x, transform_.position_.y + ENEMY_RDPOINT.y + 1);
	//int push = max(DLhit, DRhit);
	//if (push >= 1) {
	//	transform_.position_.y -= push - 1;
	//}

	//地面との当たり判定
	if (hitobj_->DownCollisionCheck()) {
		Gaccel = 0;
	}

	//右側当たり判定
	int Rhitx = transform_.position_.x + ENEMY_HITBOXSIZE.cx;
	int Rhity = transform_.position_.y + ENEMY_HITBOXSIZE.cy;
	push = field->CollisionRightCheck(Rhitx, Rhity);
	transform_.position_.x -= push;

	//左側当たり判定
	int Lhitx = transform_.position_.x - ENEMY_HITBOXSIZE.cx;
	int Lhity = transform_.position_.y + ENEMY_HITBOXSIZE.cy;
	push = field->CollisionLeftCheck(Lhitx, Lhity);
	transform_.position_.x += push;

	SpawnPoint_ = transform_.position_;

	hitobj_->AllCollisionCheck();
}

SIZE Enemy::GetSize() {
	return ENEMY_IMAGESIZE;
}
