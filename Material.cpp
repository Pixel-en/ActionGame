#include "Material.h"
#include "Camera.h"
#include "ImGui/imgui.h"
#include "Player.h"
#include "Effect.h"
#include "ScoreAndTimeAndMap.h"

namespace {
	const float GRAVITY{ 9.8f / 60.0f };
	const float MAXDURABILITY{ 5.0f };
	const XMFLOAT3 EFFECTMINEPOS{ 32,32,0 };
	const int MATERIALSCORE{ 100 };
}

Material::Material(GameObject* parent)
	:Object(parent, "Material")
{
	sizeX_ = 0;
	sizeY_ = 0;

	Mlist = { "blue4","green4", "lime4", "orange4", "red-pink4", "blue4","violet4","white-gold4" };

	std::string color = Mlist[rand() % 8];

	std::string Name = "Assets\\Image\\Crystal\\crystal_" + color + ".png";

	hImage_ = LoadGraph(Name.c_str());
	assert(hImage_ > 0);

	GetGraphSize(hImage_, &sizeX_, &sizeY_);


	VECTOR LUPOINT{ 0.0f,0.0f };
	VECTOR RUPOINT{ sizeX_,0.0f };
	VECTOR LDPOINT{ 0.0f,sizeY_ + 1 };
	VECTOR RDPOINT{ sizeX_,sizeY_ + 1 };

	//hitobj_ = new HitObject(, this);

	hitsize_ = { sizeX_,sizeY_ };
	hitobj_ = new HitObject(VECTOR{ (float)sizeX_,(float)sizeY_ }, this);

	durability_ = MAXDURABILITY;

	posNear = false;

	SeeUiLength = 150.0f;

}

Material::~Material()
{
	if (hitobj_ != nullptr)
		delete hitobj_;
	hitobj_ = nullptr;
}

void Material::Initialize()
{
}

void Material::Update()
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	VecX = pPlayer->GetPosition().x - transform_.position_.x;
	VecY = pPlayer->GetPosition().y - transform_.position_.y;
	VecZ = pPlayer->GetPosition().z - transform_.position_.z;

	VecSize = VSize(VGet(VecX, VecY, VecZ));

	if (VecSize < SeeUiLength) {
		posNear = true;
	}
	else {
		posNear = false;
	}
	while (!hitobj_->DownCollisionCheck()) {
		Gaccel += GRAVITY;
		transform_.position_.y += Gaccel;
	}
	Gaccel = 0.0f;

}

void Material::Draw()
{
	
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 0, 0, sizeX_, sizeY_, hImage_, true);

	//DrawBox(xpos, ypos, xpos + sizeX_, ypos + sizeY_, GetColor(255, 0, 255), false);
	if (posNear) {
		DrawCircle(xpos + sizeX_ / 2.0, ypos - 10, (MAXDURABILITY - durability_) / MAXDURABILITY * 10.0f, GetColor(255, 255, 255), true);
		DrawCircle(xpos + sizeX_ / 2.0, ypos - 10, 10, GetColor(255, 255, 255), false);
	}
	//
	//DrawCircle(xpos, ypos, 3, GetColor(255, 255, 255), false);
}

void Material::Release()
{
}

void Material::Mining(float _mintime)
{
	if (_mintime > 0.0) {

		Effect* e = GetParent()->FindGameObject<Effect>("MMineEffect");
		if (e == nullptr) {
			Transform trans;
			trans.position_ = { transform_.position_.x + sizeX_ / 2 - EFFECTMINEPOS.x,transform_.position_.y - EFFECTMINEPOS.y  ,transform_.position_.z + EFFECTMINEPOS.z };
			e = Instantiate<Effect>(GetParent());
			e->Reset(trans, e->MINE);
			e->SetEffectObjectName("MMineEffect");
		}
		durability_ -= _mintime;
		if (durability_ < 0) {
			Effect* e = GetParent()->FindGameObject<Effect>("MMineEffect");
			if (e != nullptr)
				e->KillMe();
			KillMe();
			ScoreAndTimeAndMap::AddScore(MATERIALSCORE);
		}
	}
	else {
		Effect* e = GetParent()->FindGameObject<Effect>("MMineEffect");
		if (e != nullptr)
			e->KillMe();
	}
}

