#include"Player.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include "ImGui/imgui.h"

namespace {
	const float MOVESPEED{ 100 };			//動くスピード
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const VECTOR IMAGESIZE{ 48 * 1.5,48 * 1.5 };			//画像サイズ
	//反転あり
	const VECTOR LUPOINT{ 11.0f * 1.5f,14.0f * 1.5f };		//左上の座標
	const VECTOR RUPOINT{ 37.0f * 1.5f,14.0f * 1.5f };	//右上の座標
	const VECTOR LDPOINT{ 11.0f * 1.5f,46.0f * 1.5f };		//左下の座標
	const VECTOR RDPOINT{ 37.0f * 1.5f,46.0f * 1.5f };	//右下の座標
	const VECTOR HITBOXSIZE{ 26 * 1.5f,32 * 1.5f };			//当たり判定のボックスのサイズ
	const float BUFFER{ 0.5f };		//攻撃後の硬直
	const float JUMPHEIGHT{ (float)(IMAGESIZE.y * 4.0) };
	const VECTOR PCENTER{ 26.0f * 1.5f,32.0f * 1.5f };

}

void Player::LoadParameter()
{
	enum CSVPARAM
	{
		STRENGTH = 1,
		TECHNIC,
		SPEED,
		HP,
		POWER = 1,
		RANGE,
		FRAME,
		RECHARGE,
	};

	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerParameter.csv");
	param_.strength_ = csv->GetInt(1, CSVPARAM::STRENGTH) - 1;
	param_.technic_ = csv->GetInt(1, CSVPARAM::TECHNIC) - 1;
	param_.speed_ = csv->GetInt(1, CSVPARAM::SPEED) - 1;
	param_.hp_ = csv->GetInt(1, CSVPARAM::HP) - 1;

	for (int i = 4; i < 9; i++) {
		ParamCorre_[i - 4].strength_ = csv->GetInt(i, CSVPARAM::STRENGTH);
		ParamCorre_[i - 4].technic_ = csv->GetInt(i, CSVPARAM::TECHNIC);
		ParamCorre_[i - 4].speed_ = csv->GetInt(i, CSVPARAM::SPEED);
		ParamCorre_[i - 4].hp_ = csv->GetInt(i, CSVPARAM::HP);
	}

	param_.strength_ = Clamp(param_.strength_, 0, 4);
	param_.technic_ = Clamp(param_.technic_, 0, 4);
	param_.speed_ = Clamp(param_.speed_, 0, 4);
	param_.hp_ = Clamp(param_.hp_, 0, 4);

	attack_[0].power_ = -1;
	attack_[0].range_ = -1;
	attack_[0].attackframe_ = -1;
	attack_[0].recharge_ = -1;

	for (int i = 11; i <16; i++) {
		attack_[i - 10].power_ = csv->GetInt(i, CSVPARAM::POWER);
		attack_[i - 10].range_ = csv->GetInt(i, CSVPARAM::RANGE);
		attack_[i - 10].attackframe_ = csv->GetInt(i, CSVPARAM::FRAME);
		attack_[i - 10].recharge_ = csv->GetInt(i, CSVPARAM::RECHARGE);
	}

}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(0), Gaccel_(0), invincible_(false), isjamp_(true)
{
	//アニメーションの初期化
	anim_.animtype_ = Animation::IDOL;
	anim_.BEanimtype_ = Animation::NONE;
	anim_.AFmax_ = 0;
	anim_.animframe_ = 0;
	anim_.AFCmax_ = 0;
	anim_.animframecount_ = 0;
	anim_.animloop_ = false;
	anim_.Rdir_ = true;

	transform_.position_ = { 0,0,0 };
	miningtime_ = 0.0f;

	//当たり判定の初期化
	hitobject_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);

	LoadParameter();

	Atype_ = AttackType::TNONE;
}

Player::~Player()
{
	if (hitobject_ != nullptr)
		delete hitobject_;
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player1.5.png");
	assert(hImage_ > 0);
}

void Player::Update()
{

	//重力
	Gaccel_ += GRAVITY;
	transform_.position_.y += Gaccel_;
	//地面との当たり判定
	if (hitobject_->DownCollisionCheck()) {
		Gaccel_ = 0;
		isjamp_ = false;
	}

	if (anim_.animtype_ < Animation::DAMAGE) {
		anim_.animtype_ = Animation::IDOL;
		MoveControl();
	}
	float time = Time::DeltaTime();
	float temp;
	ImGui::Begin("debug");
	//ImGui::InputFloat("time", &time);
	//temp = time*ParamCorre_[0].technic_;
	//ImGui::InputFloat("0", &temp);
	//temp = time*ParamCorre_[1].technic_;
	//ImGui::InputFloat("1", &temp);
	//temp = time*ParamCorre_[2].technic_;
	//ImGui::InputFloat("2", &temp);
	//temp = time*ParamCorre_[3].technic_;
	//ImGui::InputFloat("3", &temp);
	//temp = time*ParamCorre_[4].technic_;
	//ImGui::InputFloat("4", &temp);
	ImGui::End();

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

	if(anim_.Rdir_)
		DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE.x, anim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true);
	else {
		DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE.x, anim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, true);
	}
	hitobject_->DrawHitBox({ (float)xpos,(float)ypos, 0 });
	DrawCircle(xpos + LDPOINT.x, ypos + LDPOINT.y, 5, GetColor(0, 255, 255), true);

	PlayerAttackHitCheck(transform_.position_, HITBOXSIZE);
}

void Player::Release()
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

	float Dash = 1.0f;
	miningtime_ = 0.0f;

	if(!ActionControl()){

		//左移動
		if (CheckHitKey(KEY_INPUT_A)) {

			anim_.animtype_ = Animation::WALK;

			//ダッシュ
			if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)) {
				Dash = 2.0f;
				anim_.animtype_ = Animation::RUN;
			}

			transform_.position_.x += -MOVESPEED * ParamCorre_[param_.speed_].speed_ * Dash * Time::DeltaTime();
			anim_.Rdir_ = false;
			//hitobject_->LeftCollisionCheck();
		}

		//右移動
		if (CheckHitKey(KEY_INPUT_D)) {

			anim_.animtype_ = Animation::WALK;

			//ダッシュ
			if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)) {
				Dash = 2.0f;
				anim_.animtype_ = Animation::RUN;
			}

			transform_.position_.x += MOVESPEED * ParamCorre_[param_.speed_].speed_ * Dash * Time::DeltaTime();
			anim_.Rdir_ = true;
			//hitobject_->RightCollisionCheck();
		}

		hitobject_->LeftCollisionCheck();
		hitobject_->RightCollisionCheck();

		//ジャンプ
		if (CheckHitKey(KEY_INPUT_SPACE) && !isjamp_) {
			isjamp_ = true;
			Gaccel_ = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
		}

		if (isjamp_) {
			anim_.animtype_ = Animation::JUMP;
			//WaitKey();
		}
		////上移動
		//if (CheckHitKey(KEY_INPUT_W)) {

		//	transform_.position_.y = -MOVESPEED * Time::DeltaTime();
		//}
	}

	//hitobject_->AllCollisionCheck();
	//hitobject_->SelectCollisionCheck(1100);

}

bool Player::ActionControl()
{

	//採取
	if (CheckHitKey(KEY_INPUT_I)) {
		anim_.animtype_ = Animation::COLLECTION;
		miningtime_ = Time::DeltaTime() * ParamCorre_[param_.technic_].technic_;
	}

	if (CheckHitKey(KEY_INPUT_J)) {
		anim_.animtype_ = Animation::ATTACK;
		Atype_ = ATTACKT;
	}

	if (CheckHitKey(KEY_INPUT_K)) {
		anim_.animtype_ = Animation::ATTACK2;
		Atype_ = ATTACK2T;
	}
	
	if (CheckHitKey(KEY_INPUT_L)) {
		anim_.animtype_ = Animation::ATTACK3;
		Atype_ = ATTACK3T;
	}
	if (CheckHitKey(KEY_INPUT_M)) {
		anim_.animtype_ = Animation::MAGIC;

		if (CheckHitKey(KEY_INPUT_K)) {
			Atype_ = MAGIC1T;
		}

		if (CheckHitKey(KEY_INPUT_L)) {
			Atype_ = MAGIC2T;
		}
	}

	if (anim_.animtype_ == Animation::IDOL)
		return false;
	else
		return true;
}

void Player::AnimStatus()
{

	static float timecnt = 0;

	anim_.animloop_ = true;

	switch (anim_.animtype_)
	{
	case Player::NONE:
		anim_.AFmax_ = 1;
		anim_.AFCmax_ = 1;
		anim_.animloop_ = false;
		break;
	case Player::IDOL:
		anim_.AFmax_ = 4;
		anim_.AFCmax_ = 20;
		break;
	case Player::WALK:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 17;
		break;
	case Player::RUN:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 11;
		break;
	case Player::JUMP:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 120;
		anim_.animloop_ = false;
		if (Gaccel_ <= -sqrtf(2 * GRAVITY * JUMPHEIGHT) * 0.5) {
			anim_.animframe_ = 1;
		}
		else if (Gaccel_ <= -1.0) {
			anim_.animframe_ = 2;
		}
		else if (Gaccel_ <= 1.0) {
			anim_.animframe_ = 3;
		}
		else if (Gaccel_ <= sqrtf(2 * GRAVITY * JUMPHEIGHT) * 0.7) {
			anim_.animframe_ = 4;
		}
		else {
			anim_.animframe_ = 5;
		}
		anim_.animframecount_ = 0;
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
	case Player::MAGIC:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 15;
		break;
	case Player::COLLECTION:
		anim_.AFmax_ = 5;
		anim_.AFCmax_ = 17;
		break;
	case Player::DAMAGE:
		anim_.AFmax_ = 3;
		anim_.AFCmax_ = 10;
		anim_.animloop_ = false;
		invincible_ = true;
		break;
	case Player::DEATH:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 20;
		anim_.animloop_ = false;
		if (anim_.animframe_ >= 5) {
			anim_.animframecount_ = 0;
		}
		timecnt += Time::DeltaTime();
		if (timecnt >= 2.0) {
			timecnt = 0.0f;
			anim_.animtype_ = Animation::RESET;
		}
		break;
	case Player::RESET:
		anim_.AFmax_ = 1;
		anim_.AFCmax_ = 100;
		anim_.animframe_ = 0;
		anim_.animframecount_ = 0;
		anim_.animloop_ = false;
		break;
	}

	//無敵時間
	if (invincible_) {
		timecnt += Time::DeltaTime();
		if (timecnt >= 1.0) {
			timecnt = 0.0f;
			invincible_ = false;
		}
	}


	/*----アニメーションの切り替えなど-----*/

	//フレームのカウント
	if (anim_.BEanimtype_ != anim_.animtype_) {
		anim_.animframe_ = 0;
		anim_.animframecount_ = 0;
	}

	anim_.animframecount_++;
	if (anim_.animframecount_ > anim_.AFCmax_) {
		anim_.animframecount_ = 0;
		if (anim_.animloop_)
			anim_.animframe_ = (anim_.animframe_ + 1) % anim_.AFmax_;
		else {
			anim_.animframe_ = anim_.animframe_ + 1;
			if (anim_.animframe_ == anim_.AFmax_)
				anim_.animtype_ = Animation::IDOL;
		}
	}
	anim_.BEanimtype_ = anim_.animtype_;
}

VECTOR Player::KnockBackDir(VECTOR _vec)
{
	//ベクトルの挙動が意味わからんかった
	VECTOR Pcenter = { transform_.position_.x + LUPOINT.x + HITBOXSIZE.x / 2,transform_.position_.y + LUPOINT.y + HITBOXSIZE.y / 2 };
	VECTOR dir = VSub(_vec, Pcenter);
	dir = VNorm(dir);


	return dir;
}

XMFLOAT3 Player::GetHitBoxPosition()
{
	return { transform_.position_.x /*+ LUPOINT.x*/ + HITBOXSIZE.x / 2, transform_.position_.y /*+ LUPOINT.y*/ + HITBOXSIZE.y / 2, 0 };
}

void Player::HitDamage(VECTOR _dir)
{

	static int HP = ParamCorre_[param_.hp_].hp_;
	//ダメージを受けていたり死んでいないとき
	if (anim_.animtype_ < Animation::DAMAGE && !invincible_) {
		HP--;
		if (HP < 0) {
			anim_.animtype_ = Animation::DEATH;
			HP = ParamCorre_[param_.hp_].hp_;
		}
		else {
			anim_.animtype_ = Animation::DAMAGE;
			VECTOR transPos = VScale(VScale(KnockBackDir(_dir), 100.0f), Time::DeltaTime());
			transform_.position_.x += transPos.x;
			transform_.position_.y += transPos.y;
			transform_.position_.z += transPos.z;


		}
	}

}

Transform Player::GetHitTrans()
{
	Transform trans = transform_;
	trans.position_ = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
	return trans;
}

VECTOR Player::GetHitBox()
{
	return HITBOXSIZE;
}

void Player::DeadState()
{
	if (anim_.animtype_ == Animation::RESET)
		return;

	anim_.animtype_ = Animation::DEATH;
}

bool Player::PlayerAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox)
{
	if (Atype_ < 0)
		return false;

	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	XMFLOAT3 attacktrans_ = { transform_.position_.x+RUPOINT.x,transform_.position_.y + RUPOINT.y,transform_.position_.z };
	VECTOR attackhitbox_ = { attacktrans_.x + attack_[Atype_].range_,attacktrans_.y };
	//攻撃用当たり判定
	DrawBox(xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x + attack_[Atype_].range_, ypos + LDPOINT.y, GetColor(0, 0, 255), false);



	return hitobject_->HitObjectANDObject(attacktrans_, attackhitbox_, _trans, _hitbox);
}