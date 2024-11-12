#include "Bard.h"
#include "ImGui/imgui.h"

namespace {
	const VECTOR IMAGESIZE{ 80,80 };
	const VECTOR LUPOINT{ 10,10 };
	const VECTOR HITBOXSIZE{ 60,60 };
	const float IDOLTIME{ 3.0f };
}

Bard::Bard(GameObject* parent)
	:Enemy(parent)
{
	hitobj_ = new HitObject(LUPOINT, HITBOXSIZE, this);
	Idoltimer_ = 0.0;
	sinangle_ = 0.0;
	Eanim_.animtype_ = IDOL;
}

Bard::~Bard()
{
	if (hitobj_ != nullptr) {
		delete hitobj_;
		hitobj_ = nullptr;
	}
}

void Bard::Initialize()
{
}

void Bard::Update()
{
	//Eanim_.animtype_ = IDOL;


	switch (Eanim_.animtype_)
	{
	case Enemy::NONE:
		AFmax_ = 0;
		FCmax_ = 0;
		break;
	case Enemy::IDOL:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 25;
		UpdateIdol();
		break;
	case Enemy::ATTACK:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
		UpdateAttack();
		break;
	case Enemy::MOVE:
		Eanim_.AFmax_ = 4;
		Eanim_.AFCmax_ = 15;
		UpdateMove();
		break;
	case Enemy::DAMEGE:
		AFmax_ = 1;
		FCmax_ = 1;
		UpdateDamege();
		break;
	case Enemy::DEATH:
		AFmax_ = 4;
		FCmax_ = 20;
		UpdateDeath();
		break;
	}

	AnimationCalculation();
	int a = Eanim_.animtype_;
	ImGui::Begin("temp");
	ImGui::InputInt("type", &a);
	ImGui::End();
}

void Bard::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, Eanim_.animframe_ * IMAGESIZE.x, Eanim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true);

	DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(255, 255, 255), false);
	DrawBox(xpos + LUPOINT.x, ypos + LUPOINT.y, xpos + LUPOINT.x + HITBOXSIZE.x, ypos + LUPOINT.y + HITBOXSIZE.y, GetColor(255, 0, 0), false);
}

void Bard::Release()
{
}

void Bard::UpdateIdol()
{
	sinangle_ += 1.0f;
	float sinval = sinf(sinangle_ * DX_PI_F / 180.0f);
	transform_.position_.y = transform_.position_.y + sinval;

	Eanim_.animSkip_ = false;
	if (Idoltimer_ > 0) {
		Idoltimer_ -= Time::DeltaTime();
	}
	else {
		Idoltimer_ = IDOLTIME;
		Eanim_.animtype_ = EAnimation::MOVE;
	}
}

void Bard::UpdateAttack()
{
	Eanim_.animSkip_ = false;
}

void Bard::UpdateMove()
{
	Eanim_.animSkip_ = false;
}

void Bard::UpdateDamege()
{
	Eanim_.animSkip_ = false;
}

void Bard::UpdateDeath()
{
	Eanim_.animSkip_ = false;
}