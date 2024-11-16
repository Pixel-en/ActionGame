#include "PlayPreparationState.h"
#include "Engine/CsvReader.h"

namespace {
	const VECTOR IMAGESIZE{ 1024,640 };
	const VECTOR FRAMEPOS{ 450,180 };
	const int FRAMEBUFFER{ 70 };
	const int GAUGELENGTH[5]{ 0,96,192,288,384 };
	enum CSVPARAM
	{
		STRENGTH = 1,
		TECHNIC,
		SPEED,
		HP,
		MAX
	};
}

void PlayPreparationState::ParameterReader()
{
	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerParameter.csv");
	param_[STRENGTH - 1] = csv->GetInt(1, CSVPARAM::STRENGTH) - 1;
	param_[TECHNIC - 1] = csv->GetInt(1, CSVPARAM::TECHNIC) - 1;
	param_[SPEED - 1] = csv->GetInt(1, CSVPARAM::SPEED) - 1;
	param_[HP - 1] = csv->GetInt(1, CSVPARAM::HP) - 1;
}

void PlayPreparationState::ParameterWrite()
{
}

PlayPreparationState::PlayPreparationState(GameObject* parent)
	:GameObject(parent,"PlayPreparationState"), hImage_(-1), hImageState_(-1)
{
	ParameterReader();
}

void PlayPreparationState::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\PlayPreparationState.png");
	assert(hImage_ > 0);
	hImageState_ = LoadGraph("Assets\\Image\\StateMemoryFrame.png");
	assert(hImageState_ > 0);
}

void PlayPreparationState::Update()
{
}

void PlayPreparationState::Draw()
{
	//DrawGraph(150, 0, hImage_, true);
	DrawExtendGraph(200, 50, 200 + 1 + IMAGESIZE.x * 0.8, 50 + 1 + IMAGESIZE.y * 0.8, hImage_, true);
	for (int i = 0; i < 4; i++) {
		DrawBox(FRAMEPOS.x, FRAMEPOS.y + i * FRAMEBUFFER, FRAMEPOS.x + 96 + GAUGELENGTH[param_[i]], FRAMEPOS.y + i * FRAMEBUFFER + 32, GetColor(200, 200, 200), true);
		DrawGraph(FRAMEPOS.x, FRAMEPOS.y + i * FRAMEBUFFER, hImageState_, true);
	}
}

void PlayPreparationState::Release()
{
}
