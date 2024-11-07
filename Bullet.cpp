#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

Bullet::Bullet(GameObject* parent)
	:Object(parent, "Bullet")
{
	dir_ = 1;
	speed_ = 200.0f;
	bulletType_ = FIRE;
	originpos_ = { 0,0,0 };
	range_ = -1;

	framecnt_ = 0;
	animframe_ = 0;
	targetName_ = "";
	damege_ = 0;
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

void Bullet::Set(int _dir, int _type, XMFLOAT3 pos,float range, std::string Name)
{
	dir_ = _dir;
	bulletType_ = _type;

	originpos_ = pos;
	range_ = range;
	transform_.position_ = pos;

	targetName_ = Name;

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
	//int xpos = transform_.position_.x;

	//Camera* cam = GetParent()->FindGameObject<Camera>();
	//if (cam != nullptr) {
	//	xpos -= cam->GetValue();
	//}

	//if (xpos > 800 || 0 > xpos)
	//{
	//	KillMe();
	//}

	//transform_.position_.x += speed_ * Time::DeltaTime() * dir_;



	transform_.position_.x += speed_ * Time::DeltaTime() * dir_;
	if (fabs(originpos_.x - transform_.position_.x) >= range_)
		KillMe();

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

	DrawRectGraph(xpos , ypos , animframe_ * bulletSize_.cx, 0, bulletSize_.cx, bulletSize_.cy, hImage_, true, (dir_ * -1) - 1);
}

void Bullet::Release()
{
}


SIZE Bullet::GetSize()
{
	return bulletSize_;
}
