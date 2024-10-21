#include "CrystalBlack.h"
#include"Camera.h"
#include"Player.h"

CrystalBlack::CrystalBlack(GameObject* parent): Item(parent)
{
}

CrystalBlack::~CrystalBlack()
{
	if (hImage_ > 0) {
		DeleteGraph(hImage_);
	}
}

void CrystalBlack::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Crystal\\crystal_black4.png");
	assert(hImage_ >= 0);
	GetGraphSize(hImage_, &graphSizeX_, &graphSizeY_);
	fGraphSizeX_ = static_cast<float>(graphSizeX_);
	fGraphSizeY_ = static_cast<float>(graphSizeY_);
}

void CrystalBlack::Update()
{
}

void CrystalBlack::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, 0, 0, fGraphSizeX_, fGraphSizeY_, hImage_, TRUE, FALSE);
	DrawBox(xpos, ypos,fGraphSizeX_,fGraphSizeY_, GetColor(255, 255, 255), false);
}
