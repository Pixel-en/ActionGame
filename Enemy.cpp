#include "Enemy.h"
#include "Engine/CsvReader.h"

namespace {
	const VECTOR LUPOINT{ -1,-1 };
	const VECTOR HITBOXSIZE{ -1,-1 };
	const int ENEMYTYPENUM{ 7 };
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
			Eanim_.animSkip_ = true;
			break;
		}
	}

}

void Enemy::AnimationCalculation()
{
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
				if (Eanim_.animframe_ == Eanim_.AFmax_)
					Eanim_.animtype_ = EAnimation::IDOL;
			}
		}
	}
	Eanim_.BEanimtype_ = Eanim_.animtype_;
}

Enemy::Enemy(GameObject* parent)
	:Object(parent, "Enemy")
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Eanim_.animtype_ = NONE;
	Eanim_.BEanimtype_ = NONE;
	Eanim_.AFmax_ = 0;
	Eanim_.animframe_ = 0;
	Eanim_.AFCmax_ = 0;
	Eanim_.animframecount_ = 0;
	Eanim_.animloop_ = true;
	Eanim_.Rdir_ = true;
	Eanim_.animSkip_ = true;
}

Enemy::~Enemy()
{
	if (hitobj_ != nullptr)
		delete hitobj_;
}

void Enemy::Initialize()
{
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
