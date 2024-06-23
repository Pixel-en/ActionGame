#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "ImGui/imgui.h"

namespace {
	const SIZE IMAGESIZE{ 64,64 };
	const int LOOKRANGE{ 300 };
	const float GRAVITY{ 9.8f / 60.0f };	//重力
	const VECTOR LHITBOX{ 64.0f,63.0f };	//左下の座標
	const VECTOR RHITBOX{ 64.0f,63.0f };	//右下の座標
	const VECTOR LRHITBOX{ 4.0f,4.0f };		//当たり判定の左上座標
	const float JUMPHEIGHT{ IMAGESIZE.cx * 3.0f };	//ジャンプの高さ
	const int MOVEANGLE{ 45 };
	const float MOVETIME{ 1.0f };
}

Enemy::Enemy(GameObject* parent)
	:Object(parent, "Enemy"), inmoving_(false),movetimer_(MOVETIME),startmove_(false)
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
	Player* p = GetParent()->FindGameObject<Player>();

	Field* field = GetParent()->FindGameObject<Field>();

	//当たり判定
	int Rhitx = transform_.position_.x + RHITBOX.x;
	int Rhity = transform_.position_.y + RHITBOX.y;
	int push = field->CollisionRightCheck(Rhitx, Rhity);
	transform_.position_.x -= push;

	int Lhitx = transform_.position_.x + LHITBOX.x;
	int Lhity = transform_.position_.y + LHITBOX.y;
	push = field->CollisionRightCheck(Lhitx, Lhity);
	transform_.position_.x += push;


	static float Gaccel=0;

	Gaccel += GRAVITY;
	transform_.position_.y += Gaccel;

	int DLhit = field->CollisionDownCheck(transform_.position_.x + LHITBOX.x, transform_.position_.y + LHITBOX.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RHITBOX.x, transform_.position_.y + RHITBOX.y + 1);
	push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
		Gaccel = 0;
		inmoving_ = false;
		startmove_ = false;
	}


	if (transform_.position_.y > 1000.0f) {
		transform_.position_.y = 1000.0f;
		KillMe();
	}

	//攻撃バッファ
	if (!startmove_) {
		movetimer_ -= Time::DeltaTime();
		if (movetimer_ < 0) {
			movetimer_ = MOVETIME;
			startmove_ = true;
		}
	}

	static XMVECTOR move;

	//動きの計算
	if (IsExistPlayer() && !inmoving_&&startmove_) {
		inmoving_ = true;

		move = XMVECTOR{ p->GetPosition().x - transform_.position_.x,0,0 };
		XMMATRIX zrot = XMMatrixRotationZ(XMConvertToRadians(MOVEANGLE) * -(XMVectorGetX(move) / fabs(XMVectorGetX(move))));
		move = XMVector3Transform(move, zrot);
		move = XMVector3Normalize(move);
		
		Gaccel = -sqrtf(2 * GRAVITY * JUMPHEIGHT);

	}

	//動き
	if (inmoving_) {

		XMVECTOR pos = XMLoadFloat3(&transform_.position_);
		pos = pos + move *200*Time::DeltaTime();
		XMStoreFloat3(&transform_.position_, pos);
	}


}

void Enemy::Draw()
{


	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();
	DrawCircle(xpos + IMAGESIZE.cx / 2, ypos + IMAGESIZE.cy / 2, 300, GetColor(255, 0, 0), false);
	DrawRectGraph(xpos, ypos, 0, 0, 64, 64, hImage_, true);
	DrawBox(xpos, ypos, xpos + IMAGESIZE.cx, ypos + IMAGESIZE.cy, GetColor(255, 255, 255), false);
	DrawCircle(transform_.position_.x + IMAGESIZE.cx / 2, transform_.position_.y + IMAGESIZE.cy / 2, 3, GetColor(0, 255, 0), true);

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

bool Enemy::IsExistPlayer()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr)
		return false;

	float cenx = transform_.position_.x;
	float ceny = transform_.position_.y;

	float x = cenx - p->GetPosition().x;
	float y = ceny - p->GetPosition().y;

	if (x * x + y * y < LOOKRANGE * LOOKRANGE)
		return false;

	return false;
}

SIZE Enemy::GetImageSize()
{	
	return IMAGESIZE;
}