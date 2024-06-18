#include "Enemy.h"

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
