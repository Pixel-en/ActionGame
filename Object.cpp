#include "Object.h"
#include "Camera.h"
#include "Player.h"

namespace {
	const SIZE HITSIZE{ 64,64 };
	const int IMAGESIZE{ 64 };				//�摜�T�C�Y
	const VECTOR LUPOINT{ 0.0f,1.0f };	//����̍��W
	const VECTOR RUPOINT{ 64.0f,1.0f };	//�E��̍��W
	const VECTOR LDPOINT{ 0.0f,63.0f };	//�����̍��W
	const VECTOR RDPOINT{ 64.0f,63.0f };	//�E���̍��W
	const VECTOR LRHITBOX{ 4.0f,4.0f };		//�����蔻��̍�����W
}

Object::Object(GameObject* parent)
	:GameObject(parent), hImage_(-1)
{
	framecnt_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	AFmax_ = 0;
	hitsize_ = HITSIZE;
}

Object::Object(GameObject* parent, const std::string& name)
	:GameObject(parent, "Object"), hImage_(-1),hitobj_(nullptr)
{
	framecnt_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	AFmax_ = 0;
	hitsize_ = HITSIZE;
}

Object::~Object()
{
	if (hitobj_ != nullptr)
		delete hitobj_;
}

void Object::Initialize()
{
	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);
}

void Object::Reset()
{
	hitobj_->AllCollisionCheck();
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
	if (p->HitCheck(transform_.position_.x, transform_.position_.y, hitsize_))
		return true;

	return false;
}
