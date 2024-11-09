#include "Effect.h"
#include "Camera.h"
#include "ImGui/imgui.h"

namespace {
	const VECTOR IMAGESIZE{ 64,64 };
}

Effect::Effect(GameObject* parent)
	:GameObject(parent,"Effect")
{
}

Effect::~Effect()
{
}

void Effect::Initialize()
{
}

void Effect::Reset(Transform pos, EffectType _effecttype,bool _isRight)
{
	switch (_effecttype)
	{
	case KILL:
		fileName_ = "Assets\\Image\\Effect\\Kill.png";
		canLoop_= false;
		FCmax_ = 2;
		AFmax_ = 7;
		break;
	case GRASS:
		fileName_ = "Assets\\Image\\Effect\\Grass.png";
		canLoop_ = true;
		FCmax_ = 20;
		AFmax_ = 5;
		break;
	case JUMP:
		fileName_ = "Assets\\Image\\Effect\\Jump.png";
		canLoop_ = false;
		FCmax_ = 5;
		AFmax_ = 4;
		break;
	case SLASH:
		fileName_ = "Assets\\Image\\Effect\\Slash.png";
		canLoop_ = false;
		FCmax_ = 7;
		AFmax_ = 4;
		break;
	case MINE:
		fileName_ = "Assets\\Image\\Effect\\Mine.png";
		canLoop_ = true;
		FCmax_ = 25;
		AFmax_ = 4;
		break;
	default:
		break;
	}
	
	isRight_ = _isRight;
	transform_ = pos;
	if (!isRight_)
		transform_.position_.x = transform_.position_.x - IMAGESIZE.x;

	
	hImage_ = LoadGraph(fileName_.c_str());
	assert(hImage_ > 0);
}

void Effect::Reset(Transform pos, EffectType _effecttype)
{
	Reset(pos, _effecttype, true);
}

void Effect::Update()
{
	
	if (framecnt_ > FCmax_) {
		framecnt_ = 0;
		animframe_++;

		if (canLoop_) {
			animframe_ = (animframe_ + 1) % AFmax_;
		}
		else {
			if (animframe_ >= AFmax_) {
				KillMe();
			}
			else
				animframe_++;
		}
	}
	framecnt_++;
}

void Effect::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawRectGraph(xpos, ypos, animframe_ * IMAGESIZE.x, 0, IMAGESIZE.x, IMAGESIZE.y, hImage_, true, isRight_);
	DrawBox(xpos, ypos, xpos + IMAGESIZE.x, ypos + IMAGESIZE.y, GetColor(0, 255, 255), false);
}

void Effect::Release()
{
}
