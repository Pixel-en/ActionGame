#include "Effect.h"

Effect::Effect(GameObject* parent)
	:Object(parent)
{
}

Effect::~Effect()
{
}

void Effect::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\Kill_Obj.png");
	assert(hImage_ > 0);
	transform_.position_ = { 650,500,0 };
	effectSize = { 64,64 };
	animframe_ = 0;
	FCmax_ = 6;
	canLoop_ = false;
}

void Effect::Initialize(Transform pos,std::string _filename, SIZE _size, int _animframe, int _maxframe, bool _canLoop)
{
	/*char filename[30];
	for (int i = 0; i < _filename.length(); i++)
	{
		filename[i] = _filename[i];
	}*/
	hImage_ = LoadGraph("Assets\\Image\\Kill_Obj.png");
	assert(hImage_ > 0);
	effectSize = _size;
	animframe_ = _animframe;
	FCmax_ = 6;
	canLoop_ = _canLoop;
}

void Effect::Reset()
{
}

void Effect::Update()
{
	static int frame = 0;
	if (frame % 10 == 1)
	{
		animframe_++;
	}
	else if (canLoop_)
	{
		animframe_ = 0;
	}
	frame++;
}

void Effect::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	//DrawRectGraph(xpos, ypos, 0, 0, 128, 128, hImage_, true);
	//DrawRectGraph(xpos, ypos, 1 * animframe_ * ENEMY_IMAGESIZE.cx, animtype_ * ENEMY_IMAGESIZE.cy, ENEMY_IMAGESIZE.cx, ENEMY_IMAGESIZE.cy, hImage_, true, dir_ - 1);

	DrawRectGraph(xpos,ypos, effectSize.cx * animframe_, 0, effectSize.cx, effectSize.cy, hImage_, true, false);
}

void Effect::Release()
{
}
