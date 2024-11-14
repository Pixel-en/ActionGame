#include "Bullet.h"
#include "Player.h"
#include "Camera.h"

namespace {
	const VECTOR LUPOINT{ 8,8 };
}

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
}

void Bullet::Set(int _dir, int _type, XMFLOAT3 pos,float range, std::string Name)
{
	dir_ = _dir;
	bulletType_ = _type;
	range_ = range;
	if (dir_ == 1) {
		originpos_ = pos;
		transform_.position_ = pos;
	}
	else {
		originpos_ = { pos.x - bulletSize_.x ,pos.y,pos.z };
		transform_.position_ = originpos_;
	}
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
	hitobj_ = new HitObject(LUPOINT, bulletHitBoxSize_, this);
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

	if (hitobj_->LeftCollisionCheck())
		KillMe();
	if (hitobj_->RightCollisionCheck())
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

	DrawRectGraph(xpos , ypos , animframe_ * bulletSize_.x, 0, bulletSize_.x, bulletSize_.y, hImage_, true, (dir_ * -1) - 1);
	DrawBox(xpos, ypos, xpos + bulletSize_.x, ypos + bulletSize_.y, GetColor(255, 255, 255), false);
	DrawBox(xpos+LUPOINT.x, ypos+LUPOINT.x, xpos+LUPOINT.x + bulletHitBoxSize_.x, ypos+LUPOINT.y + bulletHitBoxSize_.y, GetColor(255, 0, 0), false);
}

void Bullet::Release()
{
}


SIZE Bullet::GetSize()
{
	SIZE temp = { bulletSize_.x ,bulletSize_.y, };
	return temp;
}

Transform Bullet::GetHitTrans()
{
	Transform trans;
	trans.position_ = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	return trans;
}

VECTOR Bullet::GetHitBox()
{
	return bulletHitBoxSize_;
}
