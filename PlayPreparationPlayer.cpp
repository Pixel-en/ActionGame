#include "PlayPreparationPlayer.h"

namespace {
	const VECTOR IMAGESIZE{ 48 * 1.5,48 * 1.5 };
}

PlayPreparationPlayer::PlayPreparationPlayer(GameObject* parent)
	:GameObject(parent,"PrepaPlayer"),hImage_(-1)
{
}

PlayPreparationPlayer::~PlayPreparationPlayer()
{
}

void PlayPreparationPlayer::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\new-Player1.5.png");
	assert(hImage_ > 0);
}

void PlayPreparationPlayer::Update()
{
	anim_.animtype_ = IDOL;
	anim_.AFmax_ = 4;
	anim_.AFCmax_ = 20;

	anim_.animframecount_++;
		if (anim_.animframecount_ > anim_.AFCmax_) {
			anim_.animframecount_ = 0;
			anim_.animframe_ = (anim_.animframe_ + 1) % anim_.AFmax_;
		}
}

void PlayPreparationPlayer::Draw()
{
	DrawRectGraph(250, 50, anim_.animframe_ * IMAGESIZE.x, anim_.animtype_ * IMAGESIZE.y, IMAGESIZE.x, IMAGESIZE.y, hImage_, true);
}

void PlayPreparationPlayer::Release()
{
}
