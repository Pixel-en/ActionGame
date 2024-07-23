#include "Material.h"
#include "Camera.h"
#include "ImGui/imgui.h"


namespace {
	const float GRAVITY{ 9.8f / 60.0f };
}

Material::Material(GameObject* parent)
	:Object(parent,"Material")
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

	hitobj_ = new HitObject(LUPOINT, RUPOINT, LDPOINT, RDPOINT, this);

	hitsize_ = { sizeX_,sizeY_ };

}

Material::~Material()
{
}

void Material::Initialize()
{
}

void Material::Update()
{
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
}

void Material::Release()
{
}

