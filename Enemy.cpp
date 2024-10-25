#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy(GameObject* parent)
	:Object(parent,"Enemy")
{
	animtype_ = EAnimation::IDOL;
	BEanimtype_=EAnimation::IDOL
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hImage_ = LoadGraph("Asset\\Image\\TestImage\\Enemy_test.png");
	assert(hImage_ > 0);
}

void Enemy::Update()
{
	switch (animtype_)
	{
	case Enemy::IDOL:
		AFmax_ = 0;
		FCmax_ = 0;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		AFmax_ = 0;
		FCmax_ = 0;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		AFmax_ = 0;
		FCmax_ = 0;
		UpdateMove();
		break;
	case Enemy::HURT:
		AFmax_ = 0;
		FCmax_ = 0;
		UpdateHurt();
		break;
	case Enemy::DEATH:
		AFmax_ = 0;
		FCmax_ = 0;
		UpdateDeath();
		break;
	default:
		break;
	}
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

	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE.x, animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, false);

}

void Enemy::Release()
{
}

void Enemy::UpdateIdol()
{
}

void Enemy::UpdateAttack()
{
}

void Enemy::UpdateMove()
{
}

void Enemy::UpdateHurt()
{
}

void Enemy::UpdateDeath()
{
}