#include "Effect.h"
#include "Camera.h"

Effect::Effect(GameObject* parent)
	:Object(parent)
{
}

Effect::~Effect()
{
}

void Effect::Initialize()
{
	fileName = "Assets\\Image\\Effect\\Kill.png";
	imageSize = { 64,64 };
	animFrame = 3;
	maxFrame = 3;
	canLoop = false;
	isStart = false;
	isEnd = false;
}

void Effect::Initialize(Transform pos,int _effectNumber)
{
	switch (_effectNumber)
	{
	case KILL:
		fileName = "Assets\\Image\\Effect\\Kill.png";
		canLoop = false;
		imageSize = { 64,64 };
		animFrame = 2;
		maxFrame = 7;
		break;
	case GRASS:
		fileName = "Assets\\Image\\Effect\\Grass.png";
		canLoop = true;
		imageSize = { 64,64 };
		animFrame = 20;
		maxFrame = 5;
		break;
	case JUMP:
		fileName = "Assets\\Image\\Effect\\Jump.png";
		canLoop = false;
		imageSize = { 64,64 };
		animFrame = 5;
		maxFrame = 4;
		break;
	case SLASH:
		fileName = "Assets\\Image\\Effect\\Slash.png";
		canLoop = false;
		imageSize = { 64,64 };
		animFrame = 7;
		maxFrame = 4;
		break;
	case MINE:
		fileName = "Assets\\Image\\Effect\\Mine.png";
		canLoop = true;
		imageSize = { 64,64 };
		animFrame = 25;
		maxFrame = 4;
		break;
	default:
		break;
	}

	transform_ = pos;

	hImage_ = LoadGraph(fileName.c_str());
	assert(hImage_ > 0);
}

void Effect::Reset()
{
	frame = 0;
	animframe_ = 0;
	isStart = false;
	isEnd = false;
}

void Effect::Update()
{
	if (frame % animFrame == 1)
	{
		animframe_++;
	}
	if (animframe_ >= maxFrame)
	{
		if (canLoop)
		{
			animframe_ = 0;
		}
		else
		{
			isEnd = true;
		}
	}
	frame++;
}

void Effect::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	//Camera* cam = GetParent()->FindGameObject<Camera>();
	//if (cam != nullptr) {
	//	xpos -= cam->GetValue();
	//	ypos -= cam->GetValueY();
	//}
	// 
	xpos -= cameraPos_.x;
	ypos -= cameraPos_.y;
	//DrawRectGraph(xpos, ypos, 0, 0, 128, 128, hImage_, true);
	//DrawRectGraph(xpos, ypos, 1 * animframe_ * ENEMY_IMAGESIZE.cx, animtype_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, dir_ - 1);

	DrawRectGraph(xpos, ypos, imageSize.cx * animframe_, 0, imageSize.cx, imageSize.cy, hImage_, true, false);
}

void Effect::Draw(XMFLOAT3 _cameraPos)
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	xpos -= _cameraPos.x;
	ypos -= _cameraPos.y;

	DrawRectGraph(xpos, ypos, imageSize.cx * animframe_, 0, imageSize.cx, imageSize.cy, hImage_, true, false);
}

void Effect::Draw(int _camX, int _camY)
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	xpos -= _camX;
	ypos -= _camY;

	DrawRectGraph(xpos, ypos, imageSize.cx * animframe_, 0, imageSize.cx, imageSize.cy, hImage_, true, false);
}

void Effect::Release()
{
}

void Effect::SetCameraPos(XMFLOAT3 _cameraPos)
{
	cameraPos_ = _cameraPos;
}
