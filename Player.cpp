#include "Player.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include "ImGui/imgui.h"
#include "Bullet.h"
#include "Effect.h"
#include "PlayScene.h"

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
	const XMFLOAT3 EFFECTATTACK{ 20,10,0 };
	const XMFLOAT3 EFFECTJUMP{ 0,5,0 };
	const XMFLOAT3 EFFECTMOVE{ 30,-5,0 };
	
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
		ParamCorre_[i - 4].strength_ = csv->GetFloat(i, CSVPARAM::STRENGTH);
		ParamCorre_[i - 4].technic_ = csv->GetFloat(i, CSVPARAM::TECHNIC);
		ParamCorre_[i - 4].speed_ = csv->GetFloat(i, CSVPARAM::SPEED);
		ParamCorre_[i - 4].hp_ = csv->GetInt(i, CSVPARAM::HP);
	}

	param_.strength_ = Clamp(param_.strength_, 0, 4);
	param_.technic_ = Clamp(param_.technic_, 0, 4);
	param_.speed_ = Clamp(param_.speed_, 0, 4);
	param_.hp_ = Clamp(param_.hp_, 0, 4);

	attack_[0].power_ = 0;
	attack_[0].range_ = 0;
	attack_[0].attackframe_ = 0;
	attack_[0].recharge_ = 0;

	for (int i = 11; i < 16; i++) {
		attack_[i - 10].power_ = csv->GetInt(i, CSVPARAM::POWER);
		attack_[i - 10].range_ = csv->GetInt(i, CSVPARAM::RANGE);
		attack_[i - 10].attackframe_ = csv->GetInt(i, CSVPARAM::FRAME);
		attack_[i - 10].recharge_ = csv->GetInt(i, CSVPARAM::RECHARGE);
	}
	int a = 0;
	for (int i = 0; i < 5; i++)
		rechargetimer_[i] = -1.0f;

	HP_ = ParamCorre_[param_.hp_].hp_;

}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(0), Gaccel_(0), invincible_(false), isjump_(true)
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
	anim_.animSkip_ = false;

	transform_.position_ = { 0,0,0 };
	miningtime_ = 0.0f;

	//当たり判定の初期化
	hitobject_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);

	LoadParameter();

	Atype_ = AttackType::TNONE;

	attackbuttondown = false;

}

Player::~Player()
{
	if (hitobject_ != nullptr) {
		delete hitobject_;
		hitobject_ = nullptr;
	}
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\new-Player1.5.png");
	assert(hImage_ > 0);
}

void Player::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &pad);


	PlayScene* pc = GetRootJob()->FindGameObject<PlayScene>();

	//重力
	if (!Ladderup_) {
		Gaccel_ += GRAVITY;
		transform_.position_.y += Gaccel_;
	}
	if (pc != nullptr) {
		if (transform_.position_.y > 1050&&!pc->isStateClear())
			anim_.animtype_ = RESET;
	}
	else {
		if (transform_.position_.y > 1050)
			anim_.animtype_ = RESET;
	}

	//地面との当たり判定
	if (hitobject_->DownCollisionCheck()) {
		Gaccel_ = 0;
		isjump_ = false;
	}

	if (pc != nullptr) {
		if (anim_.animtype_ < Animation::DAMAGE && pc->isStart()) {
			anim_.animtype_ = Animation::IDOL;
			MoveControl();
		}
	}
	else {
		if (anim_.animtype_ < Animation::DAMAGE ) {
			anim_.animtype_ = Animation::IDOL;
			MoveControl();
		}
	}

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

	if (anim_.Rdir_)
		DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE.x, anim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true);
	else {
		DrawRectGraph(xpos, ypos, anim_.animframe_ * IMAGESIZE.x, anim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, true);
	}

	//hitobject_->DrawHitBox({ (float)xpos,(float)ypos, 0 });
	//DrawCircle(xpos, ypos, 5, GetColor(255, 255, 255), true);
	//DrawCircle(xpos+RUPOINT.x/2.0f, ypos + RUPOINT.y, 5, GetColor(255, 0, 255), true);

	//PlayerAttackHitCheck(transform_.position_, HITBOXSIZE);
	//DrawCircle(xpos + LDPOINT.x, ypos + LDPOINT.y, 5, GetColor(0, 255, 255), true);

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
	miningtime_ = -1.0f;
	Ladderup_ = false;

	if (!ActionControl()) {
		//左移動
		if (CheckHitKey(KEY_INPUT_A) || pad.ThumbLX <= -10000) {

			anim_.animtype_ = Animation::WALK;

			//ダッシュ
			if ((CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))||pad.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]||pad.LeftTrigger>=150) {
				Dash = 2.0f;
				anim_.animtype_ = Animation::RUN;
			}

			transform_.position_.x += -MOVESPEED * ParamCorre_[param_.speed_].speed_ * Dash * Time::DeltaTime();
			anim_.Rdir_ = false;
			//hitobject_->LeftCollisionCheck();
		}

		//右移動
		if (CheckHitKey(KEY_INPUT_D) || pad.ThumbLX >= 10000) {

			anim_.animtype_ = Animation::WALK;

			//ダッシュ
			if ((CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)) || pad.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] || pad.LeftTrigger >= 150) {
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
		if ((CheckHitKey(KEY_INPUT_SPACE) || pad.Buttons[XINPUT_BUTTON_A]) && !isjump_) {
			isjump_ = true;
			Gaccel_ = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
			Transform trans;
			trans.position_ = { transform_.position_.x + EFFECTJUMP.x,transform_.position_.y + EFFECTJUMP.y ,transform_.position_.z + EFFECTJUMP.z };
			Effect* e = Instantiate<Effect>(GetParent());
			e->Reset(trans, e->JUMP);

		}

		if (isjump_) {
			anim_.animtype_ = Animation::JUMP;
			//WaitKey();
		}
		////上移動
		if (CheckHitKey(KEY_INPUT_W) || pad.ThumbLY >= 10000) {
			Field* f = GetParent()->FindGameObject<Field>();
			if (f->CollisionObjectCheck(transform_.position_.x + PCENTER.x, transform_.position_.y + LDPOINT.y)) {
				anim_.animtype_ = Animation::CLIMB;
				transform_.position_.y += -MOVESPEED * ParamCorre_[param_.speed_].speed_ * Time::DeltaTime();
				//isjamp_ = true;
				Gaccel_ = 0;
				Ladderup_ = true;
			}
		}
	}
	hitobject_->UpCollisionCheck();

	//hitobject_->AllCollisionCheck();
	//hitobject_->SelectCollisionCheck(1100);

}

bool Player::ActionControl()
{

	//採取
	if (CheckHitKey(KEY_INPUT_I) || (pad.Buttons[XINPUT_BUTTON_B] && !pad.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]&& pad.RightTrigger < 150)) {
		anim_.animtype_ = Animation::COLLECTION;
		miningtime_ = Time::DeltaTime() * ParamCorre_[param_.technic_].technic_;
	}

	if (((CheckHitKey(KEY_INPUT_M) || pad.RightTrigger >= 150) && !attackbuttondown) || Atype_ == AttackType::MAGIC1T || Atype_ == AttackType::MAGIC2T) {
		anim_.animtype_ = Animation::MAGIC;
		XMFLOAT3 bpos = { transform_.position_.x + RUPOINT.x / 2.0f,transform_.position_.y + RUPOINT.y,transform_.position_.z };

		if (((CheckHitKey(KEY_INPUT_K) || pad.Buttons[XINPUT_BUTTON_X]) && !attackbuttondown) || Atype_ == AttackType::MAGIC1T) {
			if (rechargetimer_[3] < 0.0) {
				Atype_ = MAGIC1T;
				if (!attackbuttondown) {
					Bullet* b = Instantiate<Bullet>(GetParent());
					b->SetDamege(attack_[Atype_].power_ * ParamCorre_[param_.strength_].strength_);
					anim_.animframecount_ = 0;
					if (anim_.Rdir_)
						b->Set(1, BULLET_TYPE::BOLT, bpos, attack_[Atype_].range_, "Enemy");
					else
						b->Set(-1, BULLET_TYPE::BOLT, bpos, attack_[Atype_].range_, "Enemy");
					Damege = -1;
				}
				attackbuttondown = true;
			}
		}

		else if (((CheckHitKey(KEY_INPUT_L) || pad.Buttons[XINPUT_BUTTON_Y]) && !attackbuttondown) || Atype_ == AttackType::MAGIC2T) {
			if (rechargetimer_[4] < 0.0) {
				Atype_ = MAGIC2T;
				if (!attackbuttondown) {
					Bullet* b = Instantiate<Bullet>(GetParent());
					b->SetDamege(attack_[Atype_].power_ * ParamCorre_[param_.strength_].strength_);
					anim_.animframecount_ = 0;
					if (anim_.Rdir_)
						b->Set(1, BULLET_TYPE::CHARGE, bpos, attack_[Atype_].range_, "Enemy");
					else
						b->Set(-1, BULLET_TYPE::CHARGE, bpos, attack_[Atype_].range_, "Enemy");
					Damege = -1;
				}
				attackbuttondown = true;
			}
		}
	}

	else if (((CheckHitKey(KEY_INPUT_J) || (pad.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && pad.Buttons[XINPUT_BUTTON_X])) && !attackbuttondown) || Atype_ == AttackType::ATTACKT) {
		if (rechargetimer_[0] < 0.0) {
			anim_.animtype_ = Animation::ATTACK;
			Atype_ = ATTACKT;
			attackbuttondown = true;
		}
	}

	else if (((CheckHitKey(KEY_INPUT_K) || (pad.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && pad.Buttons[XINPUT_BUTTON_Y])) && !attackbuttondown) || Atype_ == AttackType::ATTACK2T) {
		if (rechargetimer_[1] < 0.0) {
			anim_.animtype_ = Animation::ATTACK2;
			Atype_ = ATTACK2T;
			attackbuttondown = true;
		}
	}

	else if (((CheckHitKey(KEY_INPUT_L) || (pad.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && pad.Buttons[XINPUT_BUTTON_B])) && !attackbuttondown) || Atype_ == AttackType::ATTACK3T) {
		if (rechargetimer_[2] < 0.0) {
			anim_.animtype_ = Animation::ATTACK3;
			Atype_ = ATTACK3T;
			attackbuttondown = true;
		}
	}

	else if (!CheckHitKey(KEY_INPUT_J) && !CheckHitKey(KEY_INPUT_K) && !CheckHitKey(KEY_INPUT_L) && !CheckHitKey(KEY_INPUT_M) &&
		!pad.Buttons[XINPUT_BUTTON_B] && !pad.Buttons[XINPUT_BUTTON_Y] && !pad.Buttons[XINPUT_BUTTON_X] && pad.RightTrigger < 150)
		attackbuttondown = false;



	for (int i = 0; i < 5; i++) {
		if (rechargetimer_[i] < 0.0)
			rechargetimer_[i] = -1.0;
		else
			rechargetimer_[i] -= Time::DeltaTime();
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

	anim_.animSkip_ = false;

	Transform trans;
	if (anim_.Rdir_)
		trans.position_ = { transform_.position_.x + LDPOINT.x + HITBOXSIZE.x / 2.0f - EFFECTMOVE.x,transform_.position_.y + RDPOINT.y + EFFECTMOVE.y ,transform_.position_.z + EFFECTMOVE.z };
	else
		trans.position_ = { transform_.position_.x + LUPOINT.x + HITBOXSIZE.x / 2.0f + EFFECTMOVE.x,transform_.position_.y + RDPOINT.y + EFFECTMOVE.y ,transform_.position_.z + EFFECTMOVE.z };

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
		{
			Effect* e = GetParent()->FindGameObject<Effect>("PWalkEffect");
			if (e == nullptr) {
				e = Instantiate<Effect>(GetParent());
				e->Reset(trans, e->RUN, anim_.Rdir_);
				e->SetEffectObjectName("PWalkEffect");
			}
			e->SetBackEffectPos(trans.position_, anim_.Rdir_);
		}
		break;
	case Player::RUN:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 11;
		{
			Effect* e = GetParent()->FindGameObject<Effect>("PRunEffect");
			if (e == nullptr) {
				e = Instantiate<Effect>(GetParent());
				e->Reset(trans, e->RUN, anim_.Rdir_);
				e->SetEffectObjectName("PRunEffect");
			}
			e->SetBackEffectPos(trans.position_, anim_.Rdir_);
		}
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
	case Player::ATTACK:	//AttackAnimに移植
	case Player::ATTACK2:
	case Player::ATTACK3:
	case Player::MAGIC:
		anim_.AFmax_ = 5;
		anim_.AFCmax_ = 20;
		AttackAnim();
		break;
	case Player::CLIMB:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 17;
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

	if (anim_.animtype_ != Player::WALK) {
		Effect* e = GetParent()->FindGameObject<Effect>("PWalkEffect");
		if (e != nullptr)
			e->KillMe();
	}
	if (anim_.animtype_ != Player::RUN) {
		Effect* e = GetParent()->FindGameObject<Effect>("PRunEffect");
		if (e != nullptr)
			e->KillMe();
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
	if (!anim_.animSkip_) {
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
	}
	anim_.BEanimtype_ = anim_.animtype_;
}

void Player::AttackAnim()
{
	Transform trans;
	Damege = 0;
	switch (Atype_)
	{
	case Player::TNONE:

		break;

	case Player::ATTACK3T:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 12;
		if (anim_.animframe_ < 2) {
			if (anim_.Rdir_)
				transform_.position_.x += MOVESPEED * ParamCorre_[param_.speed_].speed_ * Time::DeltaTime() * 3.0;
			else
				transform_.position_.x += -MOVESPEED * ParamCorre_[param_.speed_].speed_ * Time::DeltaTime() * 3.0;
		}


	case Player::ATTACKT:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 12;
	case Player::ATTACK2T:
		anim_.AFmax_ = 6;
		anim_.AFCmax_ = 12;

		trans.position_ = { transform_.position_.x + RUPOINT.x / 2.0f,transform_.position_.y,transform_.position_.z };

		if (anim_.BEanimtype_ != anim_.animtype_) {
			anim_.animframe_ = 0;
			anim_.animframecount_ = 0;
		}
		anim_.animSkip_ = true;
		
		if (anim_.animframe_ >= 2 && anim_.animframe_ <= 4) {
			Damege = attack_[Atype_].power_ * ParamCorre_[param_.strength_].strength_;
			if (Damege <= 0)
				Damege = 1;

			if (anim_.animframe_ == 2 && anim_.animframecount_ == 1) {
				if (anim_.Rdir_)
					trans.position_ = { trans.position_.x + EFFECTATTACK.x,trans.position_.y + EFFECTATTACK.y ,trans.position_.z + EFFECTATTACK.z };
				else
					trans.position_ = { trans.position_.x - EFFECTATTACK.x,trans.position_.y + EFFECTATTACK.y ,trans.position_.z + EFFECTATTACK.z };

				Effect* e = Instantiate<Effect>(GetParent());
				e->Reset(trans, e->SLASH, anim_.Rdir_);
			}
		}

		anim_.animframecount_++;
		if (anim_.animframecount_ > anim_.AFCmax_) {
			anim_.animframecount_ = 0;
			if (anim_.animframe_ + 1 >= anim_.AFmax_) {
				rechargetimer_[Atype_ - 1] = attack_[Atype_].recharge_;
				Atype_ = AttackType::TNONE;
				anim_.animtype_ = IDOL;
				anim_.animframe_ = 0;
				anim_.animframecount_ = 0;
			}
			else
				anim_.animframe_ = anim_.animframe_ + 1;
		}
		break;
	case Player::MAGIC1T:
		anim_.AFmax_ = 6;
		anim_.animframe_ = 5;
		anim_.AFCmax_ = 30;
		anim_.animSkip_ = true;
	case Player::MAGIC2T:
		anim_.AFmax_ = 6;
		anim_.animframe_ = 5;
		anim_.AFCmax_ = 30;
		anim_.animSkip_ = true;
		Damege = -1;

		if (anim_.BEanimtype_ != anim_.animtype_) {
			anim_.animframe_ = 0;
			anim_.animframecount_ = 0;
		}

		anim_.animframecount_++;
		if (anim_.animframecount_ > anim_.AFCmax_) {
			anim_.animframe_ = 0;
			anim_.animframecount_ = 0;
			rechargetimer_[Atype_ - 1] = attack_[Atype_].recharge_;
			Atype_ = AttackType::TNONE;
			anim_.animtype_ = IDOL;

		}
		break;
	default:
		break;
	}


}

VECTOR Player::KnockBackDir(VECTOR _vec)
{
	//ベクトルの挙動が意味わからんかった
	VECTOR Pcenter = { transform_.position_.x + LUPOINT.x + HITBOXSIZE.x / 2,transform_.position_.y + LUPOINT.y + HITBOXSIZE.y / 2 };
	VECTOR dir = VSub(_vec, Pcenter);
	dir = VNorm(dir);


	return dir;
}

XMFLOAT3 Player::GetHitBoxCenterPosition()
{
	return { transform_.position_.x + LUPOINT.x + HITBOXSIZE.x / 2, transform_.position_.y + LUPOINT.y + HITBOXSIZE.y / 2, 0 };
}

void Player::HitDamage(VECTOR _dir)
{
	//ダメージを受けていたり死んでいないとき
	if (anim_.animtype_ < Animation::DAMAGE && !invincible_) {
		HP_--;
		if (HP_ < 0) {
			anim_.animtype_ = Animation::DEATH;
			HP_ = ParamCorre_[param_.hp_].hp_;
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
	if (Atype_ < 1 || Damege <= 0)
		return false;

	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}
	XMFLOAT3 attacktrans_;
	VECTOR attackhitbox_;

	if (anim_.Rdir_) {

		attacktrans_ = { transform_.position_.x + RUPOINT.x,transform_.position_.y + RUPOINT.y,transform_.position_.z };
		attackhitbox_ = VGet(attack_[Atype_].range_, HITBOXSIZE.y, 0);
		//攻撃用当たり判定
		DrawBox(xpos + RUPOINT.x, ypos + RUPOINT.y, xpos + RUPOINT.x + attack_[Atype_].range_, ypos + RDPOINT.y, GetColor(0, 0, 255), false);
	}
	else
	{
		attacktrans_ = { transform_.position_.x + LUPOINT.x,transform_.position_.y + LUPOINT.y,transform_.position_.z };
		attackhitbox_ = VGet(-attack_[Atype_].range_, HITBOXSIZE.y, 0);
		//攻撃用当たり判定
		DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + attackhitbox_.x, ypos + LUPOINT.y+attackhitbox_.y, GetColor(0, 0, 255), false);
	}

	bool set = hitobject_->HitObjectANDObject(attacktrans_, attackhitbox_, _trans, _hitbox);

	return set;
}

XMFLOAT3 Player::GetObjectCheckPos()
{
	return { transform_.position_.x + PCENTER.x, transform_.position_.y + LDPOINT.y,0 };
}
