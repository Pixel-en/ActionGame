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
	const int IMAGESIZE{ 48 };				//画像サイズ	幅44*高さ44
	const VECTOR LUPOINT{ 1.0f,14.0f };
	const VECTOR LHITBOX{ 1.0f,46.0f };		//左下の座標
	const VECTOR RHITBOX{ 27.0f,46.0f };	//右下の座標
	const SIZE HITBOXSIZE{ 26,32 };			//当たり判定のボックスのサイズ
	const int SWORDLENGTH{ 100 };
	const float RIGORTIME{ 2.0f };		//攻撃後の硬直
	const float JUMPHEIGHT{ IMAGESIZE * 4.0 };
}

void Player::TestFunc()
{

}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(-1), attackon_(false), pdir_(1), framecnt_(0), animframe_(0),
	onjump_(false), flagon_(false), animtype_(IDOL),FCmax_(0),AFmax_(0),BEanimtype_(NONE)
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
	static float Gaccel = 0;
	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	//下側当たり判定
	int DLhit = field->CollisionDownCheck(transform_.position_.x + LHITBOX.x, transform_.position_.y + LHITBOX.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RHITBOX.x, transform_.position_.y + RHITBOX.y + 1);
	int push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
		Gaccel = 0.0f;
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
			int Rhitx = transform_.position_.x + RHITBOX.x;
			int Rhity = transform_.position_.y + RHITBOX.y;
			push = field->CollisionRightCheck(Rhitx, Rhity);
			transform_.position_.x -= push;
			pdir_ = 1.0;

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
			int Lhitx = transform_.position_.x + LHITBOX.x;
			int Lhity = transform_.position_.y + LHITBOX.y;
			push = field->CollisionRightCheck(Lhitx, Lhity);
			transform_.position_.x += push;
			pdir_ = -1.0f;
			
		}
		//ジャンプ(消すかもわからん)
		if (CheckHitKey(KEY_INPUT_SPACE) && !onjump_) {
			onjump_ = true;
			Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);
		}

		if (onjump_) {
			animtype_ = Animation::JUMP;
			//transform_.position_.y -= 9.0;
			//右側当たり判定
			int Rhitx = transform_.position_.x + RHITBOX.x;
			int Rhity = transform_.position_.y + RHITBOX.y - 1;
			push = field->CollisionRightCheck(Rhitx, Rhity);

			//左側当たり判定
			int Lhitx = transform_.position_.x + LHITBOX.x;
			int Lhity = transform_.position_.y + LHITBOX.y - 1;
			push = max(field->CollisionRightCheck(Lhitx, Lhity), push);
			transform_.position_.y += push - 1;
		}

#if 0
		if (CheckHitKey(KEY_INPUT_J) && !attackon_ && !rigoron_) {
			attackon_ = true;
			framecnt_ = 0;
		}


		//不安定　できるだけ早く治すこと
		static VECTOR boxcen;
		static VECTOR Ecen;
		static int temp;
		static VECTOR box;
		static SIZE ebox;
		if (attackon_) {
			animtype_ = 4;
			framecnt_++;
			if (framecnt_ > 5) {
				attackon_ = false;
				rigoron_ = true;
				rigortimer_ = RIGORTIME;
			}
			if (framecnt_ > 1 && framecnt_ < 5) {	//攻撃判定
				VECTOR b1{ transform_.position_.x + LUPOINT.x + HITBOXSIZE.cx / 2,							transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2 - 10.0f };	//中心座標より10.0上
				VECTOR b2{ transform_.position_.x + LUPOINT.x + HITBOXSIZE.cx / 2 + (SWORDLENGTH * pdir_), transform_.position_.y + LUPOINT.y + HITBOXSIZE.cy / 2 + 10.0f };	//中心座標より10.0下
				SIZE boxsize = { abs(b2.x - b1.x), abs(b2.y - b1.y) };
				box.x = boxsize.cx;
				box.y = boxsize.cy;
				boxcen = { b1.x + boxsize.cx / 2.0f,b1.y + boxsize.cy / 2.0f };



				std::list<Enemy*> enemies = GetParent()->FindGameObjects<Enemy>();

				for (auto& Ene : enemies) {
					Ecen = { Ene->GetPosition().x + Ene->GetImageSize().cx / 2,Ene->GetPosition().y + Ene->GetImageSize().cy / 2 };
					ebox = Ene->GetImageSize();
					if (fabs(boxcen.x - Ecen.x) < boxsize.cx / 2.0 + Ene->GetImageSize().cx / 2.0 &&
						fabs(Ecen.y - boxcen.y) < boxsize.cy / 2.0 + Ene->GetImageSize().cy / 2.0)
						Ene->KillMe();
					temp = abs(Ecen.x - boxcen.x) < boxsize.cx / 2.0 + Ene->GetImageSize().cx / 2.0;
				}
			}
		}

		ImGui::Begin("pos");
		ImGui::InputFloat("x", &boxcen.x);
		ImGui::InputFloat("y", &boxcen.y);
		ImGui::InputFloat("ex", &Ecen.x);
		ImGui::InputFloat("ey", &Ecen.y);
		ImGui::InputFloat("ex", &box.x);
		ImGui::InputFloat("ey", &box.y);
		float size = box.x / 2.0 + ebox.cx / 2.0;
		ImGui::InputFloat("size", &size);
		float tempa = fabs(Ecen.x - boxcen.x);
		ImGui::InputFloat("kyori", &tempa);
		ImGui::InputInt("booly", &temp);
		ImGui::End();

		DrawCircle(ebox.cx, ebox.cy, 64, GetColor(255, 255, 0), true);

		if (rigoron_) {
			rigortimer_ -= Time::DeltaTime();
			if (rigortimer_ < 0)
				rigoron_ = false;
		}
	}
#endif

		if (CheckHitKey(KEY_INPUT_J) && !attackon_) {
			attackon_ = true;
		}
	}

	//攻撃中
	if (attackon_) {
		animtype_ = Animation::ATTACK;
		FCmax_ = 8;
		AFmax_ = 6;

		if (animframe_ >= 5) {
			attackon_ = false;
		}
		//３フレームから５フレームまで攻撃判定



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
	if (pdir_ > 0)
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);
	else
		DrawRectGraph(xpos, ypos, 1 * animframe_ * IMAGESIZE, animtype_ * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, true);

#if 1

	//画像サイズ
	DrawBox(xpos, ypos, xpos + IMAGESIZE, ypos + IMAGESIZE, GetColor(255, 0, 255), false);

	//当たり判定確認用
	if (pdir_ > 0)
		DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);
	else {
		xpos += IMAGESIZE / 2;
		DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);
		xpos -= IMAGESIZE / 2;
	}

	DrawCircle(xpos, ypos, 3, GetColor(255, 0, 255), true);
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.y, 3, GetColor(255, 0, 0), true);	//右
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y, 3, GetColor(0, 255, 0), true);	//左
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.y + 1, 3, GetColor(0, 0, 255), true);	//右下
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y + 1, 3, GetColor(0, 0, 255), true); //左下	
	HitCheck(xpos + LUPOINT.x, ypos + LUPOINT.y, HITBOXSIZE);


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

	if (pdir_ < 0)
		px += IMAGESIZE / 2;

	DrawCircle(x, y, 3, GetColor(0, 255, 255), false);	//中心

	if (abs(x - px) < _size.cx / 2 + HITBOXSIZE.cx / 2 &&
		abs(y - py) < _size.cy / 2 + HITBOXSIZE.cy / 2)
		return true;



	return false;
}
