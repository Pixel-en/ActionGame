#include "Explosion.h"
#include "Player.h"
#include "Camera.h"

Explosion::Explosion(GameObject* parent)
    :Object(parent, "Explosion")
{
    explosionType_ = FIRE;

    framecnt_ = 0;
    animframe_ = 0;
}

Explosion::~Explosion()
{
}

void Explosion::Initialize()
{
	std::string fileName_;
	switch (explosionType_)
	{
	case FIRE:
		fileName_ = "Fire";
		break;
	default:
		break;
	}
	fileName_ = "Assets\\Image\\Enemy\\Explosion_" + fileName_ + ".png";
	hImage_ = LoadGraph(fileName_.c_str());
	assert(hImage_ > 0);
}

void Explosion::Initialize(int _type, SIZE _hitBox)
{
    explosionType_ = _type;
    explosionHitBoxSize_ = _hitBox;

	std::string fileName_;
	switch (explosionType_)
	{
	case FIRE:
		fileName_ = "Fire";
		break;
	default:
		break;
	}
	fileName_ = "Assets\\Image\\Enemy\\Explosion_" + fileName_ + ".png";
	hImage_ = LoadGraph(fileName_.c_str());
	assert(hImage_ > 0);
}

void Explosion::Reset()
{
}

void Explosion::Update()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	if (xpos > 800 || 0 > xpos)
	{
		KillMe();
	}

	if (framecnt_ >= 15)
	{
		framecnt_ = 0;
		animframe_++;
		
	}
	framecnt_++;
}

void Explosion::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	//ypos += explosionSize_.cy / 4;

	DrawRectGraph(xpos - explosionSize_.cx / 2, ypos - explosionSize_.cy / 2, animframe_ * explosionSize_.cx, 0, explosionSize_.cx, explosionSize_.cy, hImage_, true);

}

void Explosion::Release()
{
}

SIZE Explosion::GetSize()
{
    return explosionSize_;
}

bool Explosion::AnimationEnd()
{
	if (animframe_ >= EXPLOSION_ANIMATION - 1)
	{
		KillMe();
		return true;
	}
	return false;
}
