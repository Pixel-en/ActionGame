#include "Object.h"
#include "Camera.h"
#include "Player.h"

namespace {
	const SIZE HITSIZE{ 64,64 };
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
