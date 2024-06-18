#include "Object.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"

namespace {
	const SIZE HITSIZE{ 64,64 };
	const int IMAGESIZE{ 64 };				//画像サイズ
	const VECTOR LHITBOX{ 64.0f,63.0f };	//左下の座標
	const VECTOR RHITBOX{ 64.0f,63.0f };	//右下の座標
	const VECTOR LRHITBOX{ 4.0f,4.0f };		//当たり判定の左上座標
}

Object::Object(GameObject* parent)
	:GameObject(parent),hImage_(-1)
{
}

Object::Object(GameObject* parent, const std::string& name)
	:GameObject(parent,"Object"),hImage_(-1)
{
}

Object::~Object()
{
}

void Object::Initialize()
{
}

void Object::Reset()
{
	Field* field = GetParent()->FindGameObject<Field>();

	int Rhitx = transform_.position_.x + RHITBOX.x;
	int Rhity = transform_.position_.y + RHITBOX.y;
	int push = field->CollisionRightCheck(Rhitx, Rhity);
	transform_.position_.x -= push;

	int Lhitx = transform_.position_.x + LHITBOX.x;
	int Lhity = transform_.position_.y + LHITBOX.y;
	push = field->CollisionRightCheck(Lhitx, Lhity);
	transform_.position_.x += push;

	int DLhit = field->CollisionDownCheck(transform_.position_.x + LHITBOX.x, transform_.position_.y + LHITBOX.y + 1);
	int DRhit = field->CollisionDownCheck(transform_.position_.x + RHITBOX.x, transform_.position_.y + RHITBOX.y + 1);
	push = max(DLhit, DRhit);
	if (push >= 1) {
		transform_.position_.y -= push - 1;
	}
}

void Object::Update()
{
}

void Object::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
		xpos -= cam->GetValue();

	DrawRectGraph(xpos, ypos, 0, 0, 64, 64, hImage_, true);
}

void Object::Release()
{
}

bool Object::IsHitting()
{
	Player* p = GetParent()->FindGameObject<Player>();
	if (p->HitCheck(transform_.position_.x, transform_.position_.y, HITSIZE))
		return true;

	return false;
}
