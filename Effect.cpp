#include "Effect.h"
#include "Camera.h"
#include "ImGui/imgui.h"

Effect::Effect(GameObject* parent)
	:GameObject(parent, "Effect")
{
	framecnt_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	AFmax_ = 0;
}

Effect::~Effect()
{
}

void Effect::Initialize()
{
}

void Effect::Reset(Transform pos, EffectType _effecttype, bool _isRight)
{
	switch (_effecttype)
	{
	case KILL:
		fileName_ = "Assets\\Image\\Effect\\Kill.png";
		canLoop_ = false;
		FCmax_ = 10;
		AFmax_ = 7;
		imagesize_ = { 64,64 };
		objectName_ = "KillEffect";
		break;
	case GRASS:
		fileName_ = "Assets\\Image\\Effect\\Grass.png";
		canLoop_ = true;
		FCmax_ = 20;
		AFmax_ = 5;
		imagesize_ = { 64,64 };
		objectName_ = "GrassEffect";
		break;
	case JUMP:
		fileName_ = "Assets\\Image\\Effect\\Jump.png";
		canLoop_ = false;
		FCmax_ = 5;
		AFmax_ = 4;
		imagesize_ = { 64,64 };
		objectName_ = "jumpEffect";
		break;
	case SLASH:
		fileName_ = "Assets\\Image\\Effect\\Slash.png";
		canLoop_ = false;
		FCmax_ = 7;
		AFmax_ = 4;
		imagesize_ = { 64,64 };
		objectName_ = "SlashEffect";
		break;
	case MINE:
		fileName_ = "Assets\\Image\\Effect\\Mine.png";
		canLoop_ = true;
		FCmax_ = 25;
		AFmax_ = 4;
		imagesize_ = { 64,64 };
		objectName_ = "MineEffect";
		break;
	case WALK:
		fileName_ = "Assets\\Image\\Effect\\Walk.png";
		canLoop_ = true;
		FCmax_ = 10;
		AFmax_ = 6;
		imagesize_ = { 24,6 };
		objectName_ = "WalkEffect";
		break;
	case RUN:
		fileName_ = "Assets\\Image\\Effect\\Run.png";
		canLoop_ = true;
		FCmax_ = 10;
		AFmax_ = 6;
		imagesize_ = { 38,6 };
		objectName_ = "RunEffect";
		break;
	case EXPLOSION:
		fileName_ = "Assets\\Image\\Effect\\Explosion.png";
		canLoop_ = false;
		FCmax_ = 15;
		AFmax_ = 4;
		imagesize_ = { 160,160 };
		objectName_ = "RunEffect";
	default:
		break;
	}

	isRight_ = _isRight;
	transform_ = pos;
	if (!isRight_)
		transform_.position_.x = transform_.position_.x - imagesize_.x;


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

	DrawRectGraph(xpos, ypos, animframe_ * imagesize_.x, 0, imagesize_.x, imagesize_.y, hImage_, true, isRight_);
	DrawBox(xpos, ypos, xpos + imagesize_.x, ypos + imagesize_.y, GetColor(0, 255, 255), false);
	//DrawCircle(xpos, ypos, 3, GetColor(255, 255, 255), true);
}

void Effect::Release()
{
}

void Effect::SetBackEffectPos(XMFLOAT3 pos, bool _dir)
{
	isRight_ = _dir;
	transform_.position_ = pos;
	if (isRight_)
		transform_.position_.x = transform_.position_.x - imagesize_.x;
}

void Effect::SetFrontEffectPos(XMFLOAT3 pos, bool _dir)
{
	isRight_ = _dir;
	transform_.position_ = pos;
	if (!isRight_)
		transform_.position_.x = transform_.position_.x - imagesize_.x;
}

