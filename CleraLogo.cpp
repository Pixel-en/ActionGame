#include "CleraLogo.h"
#include "TitleText.h"

ClearLogo::ClearLogo(GameObject* parent)
	:GameObject(parent,"ClearLogo"),hImage_(0),output_(false)
{
}

ClearLogo::~ClearLogo()
{
}

void ClearLogo::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Clear.png");
	assert(hImage_ > 0);

	transform_.position_ = { 2000,200,0 };
}

void ClearLogo::Update()
{	
	transform_.position_.x -= 200 * Time::DeltaTime();
	if (transform_.position_.x < 250) {
		transform_.position_.x = 250;
		output_ = true;
	}

	
}


void ClearLogo::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_, true);

	if (output_) {
		TitleText* tt = GetParent()->FindGameObject<TitleText>();
		tt->DrawString("Return key to title", 350, 300);
	}

	/*if (output_) {
		TitleText* tt = GetParent()->FindGameObject<TitleText>();
		tt->DrawString("Write Down �� Your Name", 350, 300);
	}*/
}

void ClearLogo::Release()
{
}
