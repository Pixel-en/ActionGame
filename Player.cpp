#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Goal.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Clear.h"

namespace {
	const float MOVESPEED{ 100 };			//動くスピード
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const int IMAGESIZE{ 48 };				//画像サイズ
	//const VECTOR LUPOINT{ 1.0f,14.0f };
	//const VECTOR RUPOINT{ 27.0f,14.0f };
	//const VECTOR LHITBOX{ 1.0f,46.0f };
	//const VECTOR RHITBOX{ 27.0f,46.0f };
	const VECTOR LUPOINT{ 11.0f,14.0f };		//左上の座標
	const VECTOR RUPOINT{ 37.0f,14.0f };	//右上の座標
	const VECTOR LHITBOX{ 11.0f,46.0f };		//左下の座標
	const VECTOR RHITBOX{ 37.0f,46.0f };	//右下の座標
	const SIZE HITBOXSIZE{ 26,32 };			//当たり判定のボックスのサイズ
	const float BUFFER{ 0.5f };		//攻撃後の硬直
	const float JUMPHEIGHT{ IMAGESIZE * 4.0 };
	const VECTOR PCENTER{ 26.0f,32.0f };
}

void Player::TestFunc()
{

}

bool Player::HitAttack(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;
	
	SIZE BOXSIZE{ 30,30 };
	if (!pRdir_)
		BOXSIZE = { -30,30 };

	int px = transform_.position_.x + PCENTER.x + BOXSIZE.cx / 2;
	int py = transform_.position_.y + PCENTER.y;

	//if (pdir_ < 0)
	//	px += IMAGESIZE / 2;
#if 1
	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//中心
	DrawBox(_x, _y, _x + _size.cx, _y + _size.cy, GetColor(111, 111, 255), false);
	DrawBox(px - BOXSIZE.cx / 2, py - BOXSIZE.cy / 2, px + BOXSIZE.cx / 2, py + BOXSIZE.cy / 2, GetColor(255, 111, 111), false);
#endif

	if (abs(x - px) < _size.cx / 2 + abs(BOXSIZE.cx) / 2 &&
		abs(y - py) < _size.cy / 2 + BOXSIZE.cy / 2)
		return true;

	return false;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(-1), attackon_(false), pRdir_(true), framecnt_(0), animframe_(0),attackbuffer_(false),bufferTime_(BUFFER),
	onjump_(false), flagon_(false), animtype_(IDOL),FCmax_(0),AFmax_(0),BEanimtype_(NONE),Gaccel_(0.0f)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player.png");
	assert(hImage_ > 0);
}

void Player::Update()
{
	//------アイドル状態のアニメーション-----
	animtype_ = Animation::IDOL;
	FCmax_ = 20;
	AFmax_ = 4;


	Field* field = GetParent()->FindGameObject<Field>();
	Clear* clear = GetParent()->FindGameObject<Clear>();

	if (clear->GetFlag())
		flagon_ = false;

	if (transform_.position_.y < 0)
		transform_.position_.y = 0;

	//重力加速
	Gaccel_ += GRAVITY;
	transform_.position_.y += Gaccel_;

	//下側当たり判定
	int DLhit = field->CollisionDownCheck(transform_.position_.x + LHITBOX.x ,
										  transform_.position_.y + LHITBOX.y + 1 );
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RHITBOX.x ,
										  transform_.position_.y + RHITBOX.y + 1 );
	int push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
		Gaccel_ = 0.0f;
		onjump_ = false;
		animtype_ = Animation::IDOL;
	}

	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());

	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		pc->DeadState();
	}

	if (!pc->CanMove())
		return;

	TestFunc();

	if (!flagon_&&!attackon_) {
		//右移動
		if (CheckHitKey(KEY_INPUT_D)) {
			AFmax_ = 6;
			if (CheckHitKey(KEY_INPUT_LSHIFT)) {
				transform_.position_.x += MOVESPEED * Time::DeltaTime() * 2;
				animtype_ = Animation::RUN;
				FCmax_ = 11;
			}
			else {
				transform_.position_.x += MOVESPEED * Time::DeltaTime();
				animtype_ = Animation::WALK;
				FCmax_ = 17;
			}
			//右側当たり判定
			int Rhitx = transform_.position_.x + RHITBOX.x  ;
			int Rhity = transform_.position_.y + RHITBOX.y  ;
			push = field->CollisionRightCheck(Rhitx, Rhity);
			transform_.position_.x -= push;
			pRdir_ = true;

		}

		//左移動
		if (CheckHitKey(KEY_INPUT_A)) {
			AFmax_ = 6;

			if (CheckHitKey(KEY_INPUT_LSHIFT)) {
				transform_.position_.x -= MOVESPEED * Time::DeltaTime() * 2.0;
				animtype_ = RUN;
				FCmax_ = 11;
			}
			else {
				transform_.position_.x -= MOVESPEED * Time::DeltaTime();
				
				animtype_ = WALK;
				FCmax_ = 17;
			}

			//左側当たり判定
			int Lhitx = transform_.position_.x + LHITBOX.x  ;
			int Lhity = transform_.position_.y + LHITBOX.y  ;
			push = field->CollisionLeftCheck(Lhitx, Lhity);
			transform_.position_.x += push;
			pRdir_ = false;
			
		}

		if (CheckHitKey(KEY_INPUT_W)) {
			if (field->CollisionObjectCheck(transform_.position_.x + PCENTER.x, transform_.position_.y + 46.0f)) {
				animtype_ = Animation::CLIMB;
				FCmax_ = 17;
				AFmax_ = 6;
				
				Gaccel_ = 0.0;
				transform_.position_.y -= MOVESPEED * Time::DeltaTime();
				onjump_ = true;
			}
		}

		//ジャンプ(消すかもわからん)
		if (CheckHitKey(KEY_INPUT_SPACE) && !onjump_) {
			onjump_ = true;
			Gaccel_ = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
		}

		if (onjump_) {
			//animtype_ = Animation::JUMP;
			//transform_.position_.y -= 9.0;
			//右側当たり判定
			int Rhitx = transform_.position_.x + RHITBOX.x  ;
			int Rhity = transform_.position_.y + RHITBOX.y - 1;
			push = field->CollisionRightCheck(Rhitx, Rhity);

			//左側当たり判定
			int Lhitx = transform_.position_.x + LHITBOX.x  ;
			int Lhity = transform_.position_.y + LHITBOX.y - 1  ;
			push = max(field->CollisionRightCheck(Lhitx, Lhity), push);
			transform_.position_.y += push - 1;

			//上方向当たり判定
			int ULhit = field->CollisionUpCheck(transform_.position_.x + LUPOINT.x  ,
				transform_.position_.y + LUPOINT.y - 1  );
			int URhit = field->CollisionUpCheck(transform_.position_.x + RUPOINT.x  ,
				transform_.position_.y + RUPOINT.y - 1  );
			push = max(ULhit, URhit);
			transform_.position_.y += push + 1;
			if (push > 0) {
				Gaccel_ = 0.0;
			}
		}

		if (CheckHitKey(KEY_INPUT_J) && !attackbuffer_&&!attackon_) {
			attackon_ = true;
		}
	}

	//攻撃中
	if (attackon_) {
		animtype_ = Animation::ATTACK;
		FCmax_ = 8;
		AFmax_ = 6;

		//３フレームから５フレームまで攻撃判定
		std::list<Enemy*> enemies = GetParent()->FindGameObjects<Enemy>();
		if (animframe_ >= 2 && animframe_ <= 4) {
			for (auto& E : enemies) {
				if (HitAttack(E->GetPosition().x, E->GetPosition().y, E->GetImageSize()))
					E->KillMe();
			}
		}

		if (animframe_ >= 5) {
			attackbuffer_ = true;
			attackon_ = false;
		}
	}

	if (attackbuffer_) {
		bufferTime_ -= Time::DeltaTime();
		if (bufferTime_ < 0) {
			attackbuffer_ = false;
			bufferTime_ = BUFFER;
		}
	}


	//アニメーションの動作
	if (true) {
		//前フレームと違うアニメーションならカウントをゼロにする
		if (BEanimtype_ != animtype_) {
			framecnt_ = 0;
			animframe_ = 0;
		}

		framecnt_++;
		if (framecnt_ > FCmax_) {
			framecnt_ = 0;
			animframe_ = (animframe_ + 1) % AFmax_;
		}
		BEanimtype_ = animtype_;
	}

	//右固定カメラ
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
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

void Player::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	//メイン出力
	if (pRdir_==true)
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);
	else
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, true);

#if 1
	//デバッグ用出力

	//画像サイズ
	DrawBox(xpos, ypos, xpos + IMAGESIZE, ypos + IMAGESIZE, GetColor(255, 0, 255), false);

	//当たり判定確認用
	if (pRdir_==true)
		DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);
	else {
		xpos += IMAGESIZE / 2;
		DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);
		xpos -= IMAGESIZE / 2;
	}


	DrawCircle(xpos, ypos, 3, GetColor(255, 0, 255), true);
	DrawCircle(xpos + RHITBOX.x , ypos + RHITBOX.y, 3, GetColor(255, 0, 0), true);	//右　赤
	DrawCircle(xpos + LHITBOX.x , ypos + LHITBOX.y, 3, GetColor(0, 255, 0), true);	//左　緑
	DrawCircle(xpos + RUPOINT.x, ypos + RUPOINT.y, 3, GetColor(255, 0, 0), true);	//右　赤
	DrawCircle(xpos + LUPOINT.x, ypos + LUPOINT.y, 3, GetColor(0, 255, 0), true);	//左　緑
	//DrawCircle(xpos + RHITBOX.x+pFieldBuffer.x, ypos + RHITBOX.y+pFieldBuffer.y + 1, 3, GetColor(0, 0, 255), true);	//右下　青
	//DrawCircle(xpos + LHITBOX.x+pFieldBuffer.x, ypos + LHITBOX.y+pFieldBuffer.y + 1, 3, GetColor(0, 0, 255), true); //左下	青
	HitCheck(xpos + LUPOINT.x, ypos + LUPOINT.y, HITBOXSIZE);

	DrawCircle(xpos + RHITBOX.x, ypos + LUPOINT.y, 1, GetColor(145, 214, 75), false);

	DrawCircle(xpos + IMAGESIZE / 2+20, ypos + IMAGESIZE / 2, 1, GetColor(148, 241, 111), false);
	DrawCircle(xpos + IMAGESIZE / 2+20, ypos + IMAGESIZE / 2, 10, GetColor(148, 241, 111), false);
	DrawCircle(xpos + PCENTER.x, ypos + 46.0f, 5, GetColor(147, 54, 84), false);
	DrawCircle(transform_.position_.x + PCENTER.x, transform_.position_.y + 45.0f, 5, GetColor(145, 48, 241), true);
	HitAttack(xpos, ypos, HITBOXSIZE);
#endif
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;


	int px = transform_.position_.x + LUPOINT.x + HITBOXSIZE.cx / 2;
	int py = transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2;

	if (pRdir_ == false)
		px += IMAGESIZE / 2;

	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//中心

	if (abs(x - px) < _size.cx / 2 + HITBOXSIZE.cx / 2 &&
		abs(y - py) < _size.cy / 2 + HITBOXSIZE.cy / 2)
		return true;



	return false;
}
