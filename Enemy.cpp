#include "Enemy.h"
#include "Engine/CsvReader.h"
#include "Player.h"

namespace {
	const VECTOR LUPOINT{ -1,-1 };
	const VECTOR HITBOXSIZE{ -1,-1 };
	const int ENEMYTYPENUM{ 7 };
}

float Enemy::EPDistance()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return 0.0;
	}

	float cenx = CenterTransPos_.x;
	float ceny = CenterTransPos_.y;

	float x = cenx - p->GetHitBoxCenterPosition().x;
	float y = ceny - p->GetHitBoxCenterPosition().y;

	DrawCircle(p->GetHitBoxCenterPosition().x, p->GetHitBoxCenterPosition().y, 3, GetColor(0, 255, 0), false);
	DrawCircle(cenx, ceny, 3, GetColor(0, 255, 0), false);

	return sqrt(x * x + y * y);
}

void Enemy::SetCenterTransPos(XMFLOAT3 _trans, VECTOR _size)
{
	CenterTransPos_ = { _trans.x + _size.x / 2.0f,_trans.y + _size.y / 2.0f ,_trans.z };
}

void Enemy::PlayerDir()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr) {
		return;
	}

	if (p->GetPosition().x - transform_.position_.x < 0)
		Eanim_.Rdir_ = false;
	else
		Eanim_.Rdir_ = true;

}

void Enemy::StatusReader(int _enemyNumber)
{
	enum CSVEPARAM
	{
		MOVESPEED = 1,
		RUNSPEED,
		HP,
		MOVETIMER,
		FILENAME
	};


	CsvReader* csv = new CsvReader("Assets\\Status\\EnemyStatus.csv");
	for (int i = 1; i <= ENEMYTYPENUM; i++) {
		if (_enemyNumber == csv->GetInt(i, 0))
		{
			Eparam_.speed_ = csv->GetFloat(i, MOVESPEED);
			Eparam_.runspeed_ = csv->GetFloat(i, RUNSPEED);
			Eparam_.hp_ = csv->GetInt(i, HP);
			Eparam_.movetimer_ = csv->GetFloat(i, MOVETIMER);
			Eparam_.filename_ = csv->GetString(i, FILENAME);
			Eparam_.range_ = 100.0f;
			objectName_ = Eparam_.filename_;
			Eparam_.filename_ = "Assets\\Image\\Enemy\\" + Eparam_.filename_ + "_sprite.png";
			hImage_ = LoadGraph(Eparam_.filename_.c_str());
			assert(hImage_ > 0);

			Eanim_.animtype_ = IDOL;
			Eanim_.BEanimtype_ = NONE;
			Eanim_.AFmax_ = 0;
			Eanim_.animframe_ = 0;
			Eanim_.AFCmax_ = 0;
			Eanim_.animframecount_ = 0;
			Eanim_.animloop_ = true;
			Eanim_.Rdir_ = true;
			Eanim_.animSkip_ = false;
			break;
		}
	}

}

void Enemy::StatusDamege()
{
	Eanim_.animtype_ = Enemy::DAMEGE;
}

void Enemy::HitDamege(int _damege)
{
	if (_damege < 0)
		return;

	if (!invincible_) {

		Eparam_.hp_ -= _damege;
		if (Eparam_.hp_ <= 0) {
			Eanim_.animtype_ = EAnimation::DEATH;
		}
		else
			Eanim_.animtype_ = EAnimation::DAMEGE;
		invincibleTimer_ = 0.5f;
		invincible_ = true;
		Eanim_.animframecount_ = 0;
		Eanim_.animframe_ = 0;

	}
}

XMFLOAT3 Enemy::GetHitTransPos()
{
	return { transform_.position_.x + LU.x,transform_.position_.y + LU.y,transform_.position_.z };
}

VECTOR Enemy::GetHitBox()
{
	return Hitbox_;
}

void Enemy::AnimationCalculation()
{

	if (invincible_) {
		invincibleTimer_ -= Time::DeltaTime();
		if (invincibleTimer_ < 0.0f) {
			invincible_ = false;
		}
	}

	if (!Eanim_.animSkip_) {
		if (Eanim_.BEanimtype_ != Eanim_.animtype_) {
			Eanim_.animframe_ = 0;
			Eanim_.animframecount_ = 0;
		}


		Eanim_.animframecount_++;
		if (Eanim_.animframecount_ > Eanim_.AFCmax_) {
			Eanim_.animframecount_ = 0;
			if (Eanim_.animloop_)
				Eanim_.animframe_ = (Eanim_.animframe_ + 1) % Eanim_.AFmax_;
			else {
				Eanim_.animframe_ = Eanim_.animframe_ + 1;
				if (Eanim_.animframe_ == Eanim_.AFmax_) {
					Eanim_.animtype_ = EAnimation::IDOL;
					Eanim_.animframe_ = 0;
					Eanim_.animframecount_ = 0;
				}
			}
		}
	}
	Eanim_.BEanimtype_ = Eanim_.animtype_;
}

Enemy::Enemy(GameObject* parent)
	:Object(parent, "Enemy")
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Eanim_.animtype_ = IDOL;
	Eanim_.BEanimtype_ = NONE;
	Eanim_.AFmax_ = 0;
	Eanim_.animframe_ = 0;
	Eanim_.AFCmax_ = 0;
	Eanim_.animframecount_ = 0;
	Eanim_.animloop_ = true;
	Eanim_.Rdir_ = true;
	Eanim_.animSkip_ = false;
}

Enemy::~Enemy()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Enemy::Initialize()
{
}

void Enemy::Reset()
{
	originpos_ = transform_.position_;
	Eanim_.animtype_ = IDOL;
	Eanim_.BEanimtype_ = NONE;
	Eanim_.AFmax_ = 0;
	Eanim_.animframe_ = 0;
	Eanim_.AFCmax_ = 0;
	Eanim_.animframecount_ = 0;
	Eanim_.animloop_ = true;
	Eanim_.Rdir_ = true;
	Eanim_.animSkip_ = true;
	hitobj_->RightCollisionCheck();
	hitobj_->LeftCollisionCheck();
	if(hitobj_->DownCollisionCheck()) {
		Gaccel = 0.0f;
	}
	hitobj_->UpCollisionCheck();
}

void Enemy::Reset(XMFLOAT3 pos)
{

	originpos_ = pos;
	transform_.position_ = originpos_;

	Eanim_.animtype_ = IDOL;
	Eanim_.BEanimtype_ = NONE;
	Eanim_.AFmax_ = 0;
	Eanim_.animframe_ = 0;
	Eanim_.AFCmax_ = 0;
	Eanim_.animframecount_ = 0;
	Eanim_.animloop_ = true;
	Eanim_.Rdir_ = true;
	Eanim_.animSkip_ = false;

	hitobj_->RightCollisionCheck();
	hitobj_->LeftCollisionCheck();
	if (hitobj_->DownCollisionCheck()) {
		Gaccel = 0.0f;
	}
	hitobj_->UpCollisionCheck();
}

void Enemy::Update()
{
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
}

void Enemy::Release()
{
}

bool Enemy::IsExistPlayer(float _range)
{
	if (powf(EPDistance(), 2) < _range * _range)
		return true;

	return false;
}