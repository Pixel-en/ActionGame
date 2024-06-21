#include "Enemy.h"
#include "Player.h"

namespace {
	const SIZE IMAGESIZE{ 64,64 };
}

Enemy::Enemy(GameObject* parent)
	:Object(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Enemy_test.png");
	assert(hImage_ > 0);
}

void Enemy::Update()
{
}

void Enemy::Release()
{
}

bool Enemy::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x, transform_.position_.y, IMAGESIZE)) {
		p->KillMe();
		return true;
	}

	return false;
}
