#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"
#include "Goal.h"
#include "PlayScene.h"

namespace {
	const float MOVESPEED{ 100 };			//動くスピード
	const float GRAVITY{ 9.8f / 120.0f };	//重力
	const int IMAGESIZE{ 64 };				//画像サイズ
	const VECTOR LHITBOX{ 4.0f,60.0f };		//左下の座標
	const VECTOR RHITBOX{ 60.0f,60.0f };	//右下の座標
	const VECTOR LRHITBOX{ 4.0f,4.0f };		//当たり判定の左上座標
	const SIZE HITBOXSIZE{ 54,54 };			//当たり安定のボックスのサイズ
}

void Player::TestFunc()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
		transform_.position_.y -= 10.0;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hImage_(-1)
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
	Field* field = GetParent()->FindGameObject<Field>();

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
	}

	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());
	
	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		pc->DeadState();
	}


	if (!pc->CanMove())
		return;

	TestFunc();

	//右移動
	if (CheckHitKey(KEY_INPUT_D)) {
		if (CheckHitKey(KEY_INPUT_LSHIFT))
			transform_.position_.x += MOVESPEED * Time::DeltaTime() * 2.0;
		else
			transform_.position_.x += MOVESPEED * Time::DeltaTime();

		//右側当たり判定
		int Rhitx = transform_.position_.x + RHITBOX.x;
		int Rhity = transform_.position_.y + RHITBOX.y;
		int push = field->CollisionRightCheck(Rhitx, Rhity);
		transform_.position_.x -= push;

	}
	//左移動
	else if (CheckHitKey(KEY_INPUT_A)) {
		if (CheckHitKey(KEY_INPUT_LSHIFT))
			transform_.position_.x -= MOVESPEED * Time::DeltaTime() * 2.0;
		else
			transform_.position_.x -= MOVESPEED * Time::DeltaTime();

		//左側当たり判定
		int Lhitx = transform_.position_.x + LHITBOX.x;
		int Lhity = transform_.position_.y + LHITBOX.y;
		int push = field->CollisionRightCheck(Lhitx, Lhity);
		transform_.position_.x += push;
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



	DrawRectGraph(xpos, ypos, 0, 0, IMAGESIZE, IMAGESIZE, hImage_, true);

	//当たり判定確認用
	DrawBox(xpos + LHITBOX.x, ypos + 4, xpos + RHITBOX.x, ypos + RHITBOX.y, GetColor(255, 255, 255), FALSE);

	DrawCircle(xpos, ypos, 3, GetColor(255, 0, 255), true);
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.y, 3, GetColor(255, 0, 0), true);	//右
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y, 3, GetColor(0, 255, 0), true);	//左
	DrawCircle(xpos + RHITBOX.x, ypos + RHITBOX.x + 1, 3, GetColor(0, 0, 255), true);	//右下
	DrawCircle(xpos + LHITBOX.x, ypos + LHITBOX.y + 1, 3, GetColor(0, 0, 255), true); //左下
	HitCheck(xpos + LHITBOX.x, ypos + 4, HITBOXSIZE);
}

void Player::Release()
{
}

bool Player::HitCheck(int _x, int _y, SIZE _size)
{
	int x = _x + _size.cx / 2;
	int y = _y + _size.cy / 2;

	int px = transform_.position_.x + HITBOXSIZE.cx / 2;
	int py = transform_.position_.y + HITBOXSIZE.cy / 2;

	DrawCircle(x, y, 3, GetColor(0, 255, 255), true);

	if (abs(x - px) < _size.cx / 2 + HITBOXSIZE.cx / 2 &&
		abs(y - py) < _size.cy / 2 + HITBOXSIZE.cy / 2)
		return true;



	return false;
}
