#include "Player.h"

namespace {
	const float MOVESPEED{ 100 };
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hImage_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player_test.png");
	assert(hImage_ > 0);
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		transform_.position_.x += MOVESPEED * Time::DeltaTime();
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		transform_.position_.x -= MOVESPEED * Time::DeltaTime();
	}

	transform_.position_.y += 9.8 / 60.0f;

}

void Player::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_,true);
}

void Player::Release()
{
}
