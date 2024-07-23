#include "ClearPlayer.h"
#include "Camera.h"

namespace {
	const float IMAGESIZE{ 48 * 1.5 };				//画像サイズ
}

Clearplayer::Clearplayer(GameObject* parent)
	:GameObject(parent,"Clearplayer"),hImage_(0)
{
}

Clearplayer::~Clearplayer()
{
}

void Clearplayer::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Player1.5.png");
	assert(hImage_ > 0);

	framecnt_ = 0;
	animframe_ = 0;
	FCmax_ = 11;
	AFmax_ = 6;


	//アニメーションの動作
		transform_.position_ = { 400.0f,890.0f,0.0f };
}

void Clearplayer::Update()
{
	framecnt_++;
	if (framecnt_ > FCmax_) {
		framecnt_ = 0;
		animframe_ = (animframe_ + 1) % AFmax_;
	}
	transform_.position_.x += 100 * Time::DeltaTime();
	if (transform_.position_.x > 1680)
		transform_.position_.x = 400;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	int y = (int)transform_.position_.y - cam->GetValueY();

	//if (x > 400) {
		x = 400;
		cam->SetValue(transform_.position_.x - x);
	//}


}

void Clearplayer::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE, 2 * IMAGESIZE, IMAGESIZE, IMAGESIZE, hImage_, true, false);
}

void Clearplayer::Release()
{
}
