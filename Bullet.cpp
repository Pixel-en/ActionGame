#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

Bullet::Bullet(GameObject* parent)
	:Object(parent, "Bullet")
{
	dir_ = 1;
	speed_ = 200.0f;
	bulletType_ = FIRE;

	framecnt_ = 0;
	animframe_ = 0;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	std::string fileName_;
	switch (bulletType_)
	{
	case FIRE:
		fileName_ = "fire";
		break;
	default:
		break;
	}
	fileName_ = "Assets\\Image\\Enemy\\" + fileName_ + ".png";
	hImage_ = LoadGraph(fileName_.c_str());
	assert(hImage_ > 0);
}

void Bullet::Initialize(int _dir, int _type)
{
	dir_ = _dir;
	bulletType_ = _type;

	std::string fileName_;
	switch (bulletType_)
	{
	case FIRE:
		fileName_ = "fire";
		break;
	default:
		break;
	}
	fileName_ = "Assets\\Image\\Enemy\\" + fileName_ + ".png";
	hImage_ = LoadGraph(fileName_.c_str());
	assert(hImage_ > 0);
}

void Bullet::Reset()
{
}

void Bullet::Update()
{
	int xpos = transform_.position_.x;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
	}

	if (xpos > 800 || 0 > xpos)
	{
		KillMe();
	}

	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;

	if (framecnt_ >= 20)
	{
		framecnt_ = 0;
		animframe_++;
		if (animframe_ >= BULLET_ANIMATION)
		{
			animframe_ = 0;
		}
	}
	framecnt_++;
}

void Bullet::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos - (bulletSize_.cx - bulletHitBoxSize_.cx) , ypos - (bulletSize_.cy - bulletHitBoxSize_.cy) / 2, animframe_ * bulletSize_.cx, 0, bulletSize_.cx, bulletSize_.cy, hImage_, true, (dir_ * -1) - 1);
}

void Bullet::Release()
{
}

bool Bullet::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x, transform_.position_.y, bulletHitBoxSize_)) {
		return true;
	}

	return false;
}

SIZE Bullet::GetSize()
{
	return bulletSize_;
}
