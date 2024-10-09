#include"Player.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include <algorithm>

namespace {
	const float MOVESPEED{ 100 };			//動くスピード
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const float IMAGESIZE{ 48 * 1.5 };				//画像サイズ
	const VECTOR LUPOINT{ 11.0f * 1.5f,14.0f * 1.5f };		//左上の座標
	const VECTOR RUPOINT{ 37.0f * 1.5f,14.0f * 1.5f };	//右上の座標
	const VECTOR LDPOINT{ 11.0f * 1.5f,46.0f * 1.5f };		//左下の座標
	const VECTOR RDPOINT{ 37.0f * 1.5f,46.0f * 1.5f };	//右下の座標
	const SIZE HITBOXSIZE{ 26 * 1.5f,32 * 1.5f };			//当たり判定のボックスのサイズ
	const float BUFFER{ 0.5f };		//攻撃後の硬直
	const float JUMPHEIGHT{ IMAGESIZE * 4.0 };
	const VECTOR PCENTER{ 26.0f * 1.5f,32.0f * 1.5f };

}

void Player::LoadParameter()
{
	enum CSVPARAM
	{
		STRENGTH=1,
		TECHNIC,
		SPEED,
		HP,
	};

	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerParameter.csv");
	param_.strength_= csv->GetInt(1, CSVPARAM::STRENGTH);
	param_.technic_ = csv->GetInt(1, CSVPARAM::TECHNIC);
	param_.speed_ = csv->GetInt(1, CSVPARAM::SPEED);
	param_.hp_ = csv->GetInt(1, CSVPARAM::HP);

	for (int i = 4; i < csv->GetLines(); i++) {
		ParamCorre_[i-4].strength_ = csv->GetInt(i, CSVPARAM::STRENGTH);
		ParamCorre_[i-4].technic_ = csv->GetInt(i, CSVPARAM::TECHNIC);
		ParamCorre_[i-4].speed_ = csv->GetInt(i, CSVPARAM::SPEED);
		ParamCorre_[i-4].hp_ = csv->GetInt(i, CSVPARAM::HP);
	}


	param_.strength_ = Clamp(param_.strength_, 1, 5);
	param_.technic_ = Clamp(param_.technic_, 1, 5);
	param_.speed_ = Clamp(param_.speed_, 1, 5);
	param_.hp_ = Clamp(param_.hp_, 1, 5);
	
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hImage_(0), Gaccel_(0)
{
	//アニメーションの初期化
	anim_.animtype_ = Animation::IDOL;
	anim_.BEanimtype_ = Animation::NONE;
	anim_.AFmax_ = 0;
	anim_.animframe_ = 0;
	anim_.AFCmax_ = 0;
	anim_.animframecount_ = 0;
	
	transform_.position_ = { 0,0,0 };
	//std::string str = GetParent()->GetParent()->GetObjectName();

	//当たり判定の初期化
	hitobject_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);

	LoadParameter();
}

Player::~Player()
{
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player1.5.png");
	assert(hImage_ > 0);
}

void Player::Update()
{
	anim_.animtype_ = Animation::IDOL;

	MoveControl();

	AnimStatus();

	CameraScroll();
}

void Player::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	////メイン出力
	////if (pRdir_ == true)
	//	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);/*
	//else
	//	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, true);*/

	DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE, anim_.animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true);
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	return false;
}

XMFLOAT3 Player::GetHitBoxPosition()
{
	return { 0,0,0 };
}

void Player::DeadState()
{
}


void Player::CameraScroll()
{
	//右固定カメラ
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	int y = (int)transform_.position_.y - cam->GetValueY();



	if (y > 500) {
		y = 500;
		cam->SetValueY(transform_.position_.y - y);
	}
	else if (y < 100) {

		y = 100;
		cam->SetValueY(transform_.position_.y - y);
		if (transform_.position_.y < 0)
			transform_.position_.y = 0;
		if (cam->GetValueY() < 0)
			cam->SetValueY(0);
	}
	else {
		cam->SetValueY(transform_.position_.y - y);
	}
	if (cam->GetValueY() > 300)
		cam->SetValueY(300);


	if (x > 400) {
		x = 400;
		cam->SetValue(transform_.position_.x - x);
	}
	//左固定カメラ
	else if (x < 200) {

		x = 200;
		cam->SetValue(transform_.position_.x - x);
		if (transform_.position_.x < 0)
			transform_.position_.x = 0;
		if (cam->GetValue() < 0)
			cam->SetValue(0);

	}
}

void Player::MoveControl()
{

	//重力
	Gaccel_ += GRAVITY;
	transform_.position_.y += Gaccel_;
	//地面との当たり判定
	if (hitobject_->DownCollisionCheck()) {
		Gaccel_ = 0;
	}

	float Dash = 1.0f;

	//ダッシュ
	if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)) {
		Dash = 2.0f;
		anim_.animtype_ = Animation::RUN;
	}

	//左移動
	if (CheckHitKey(KEY_INPUT_A)) {
		if(anim_.animtype_!=Animation::RUN)
			anim_.animtype_ = Animation::WALK;
		transform_.position_.x += -MOVESPEED * ParamCorre_[param_.speed_ - 1].speed_ * Dash * Time::DeltaTime();
	}

	//右移動
	if (CheckHitKey(KEY_INPUT_D)) {
		if (anim_.animtype_ != Animation::RUN)
			anim_.animtype_ = Animation::WALK;
		transform_.position_.x += MOVESPEED * ParamCorre_[param_.speed_ - 1].speed_ * Dash * Time::DeltaTime();

	}

	////上移動
	//if (CheckHitKey(KEY_INPUT_W)) {

	//	transform_.position_.y = -MOVESPEED * Time::DeltaTime();
	//}

	//if (CheckHitKey(KEY_INPUT_SPACE)) {

	//	transform_.position_.x = -MOVESPEED * Time::DeltaTime();
	//}

	hitobject_->AllCollisionCheck();

}

void Player::AnimStatus()
{
	switch (anim_.animtype_)
	{
	case Player::NONE:
		anim_.AFmax_ = 0;
		anim_.AFCmax_ = 0;
		break;
	case Player::IDOL:
		anim_.AFmax_ = 4;
		anim_.AFCmax_ = 20;
		break;
	case Player::WALK:
		anim_.AFmax_ =6;
		anim_.AFCmax_ = 17;
		break;
	case Player::RUN:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 11;
		break;
	case Player::JUMP:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 0;
		break;
	case Player::ATTACK:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 8;
		break;
	case Player::ATTACK2:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 8;
		break;
	case Player::ATTACK3:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 8;
		break;
	case Player::CLIMB:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 17;
		break;
	case Player::COLLECTION:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 0;
		break;
	case Player::MAGIC:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 0;
		break;
	case Player::DAMAGE:
		anim_.AFmax_ = 3;
		anim_.AFCmax_ = 0;
		break;
	case Player::DEATH:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 20;
		break;
	}
	
	//フレームのカウント
	if (anim_.BEanimtype_ != anim_.animtype_) {
		anim_.animframe_ = 0;
		anim_.animframecount_ = 0;
	}

	anim_.animframecount_++;
	if (anim_.animframecount_ > anim_.AFCmax_) {
		anim_.animframecount_ = 0;
		anim_.animframe_ = (anim_.animframe_ + 1) % anim_.AFmax_;
	}
	anim_.BEanimtype_ = anim_.animtype_;

}
