#include "PlayPreparationState.h"
#include "Engine/CsvReader.h"
#include "OutText.h"
#include <fstream>

namespace {
	const VECTOR IMAGESIZE{ 1024,640 };
	const VECTOR MAINIMAGEPOS{ 200,50 };
	const VECTOR FRAMEPOS{ 450,180 };
	const int FRAMEBUFFER{ 70 };
	const int GAUGELENGTH[5]{ 0,96,192,288,384 };
	const VECTOR STARTPOS{ 500,600 };
	const VECTOR MESSAGEPOS{ 270,500 };
	const VECTOR CURSORPOS[5]{ {190,170},
							   {190,240},
							   {190,310},
							   {190,380},
							   {450,590} };

	enum CSVPARAM
	{
		STRENGTH = 1,
		TECHNIC,
		SPEED,
		HP,
		MAX
	};
	const int STATUSMEMORYMAX{ 12 };
	const VECTOR RESIDUEPOS{ 870,120 };
	const VECTOR RESIDUEMESSAGEPOS{ 750,120 };
}

void PlayPreparationState::ParameterReader()
{
	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerParameter.csv");
	param_[STRENGTH - 1] = csv->GetInt(1, CSVPARAM::STRENGTH) - 1;
	param_[TECHNIC - 1] = csv->GetInt(1, CSVPARAM::TECHNIC) - 1;
	param_[SPEED - 1] = csv->GetInt(1, CSVPARAM::SPEED) - 1;
	param_[HP - 1] = csv->GetInt(1, CSVPARAM::HP) - 1;
	for (int i = 0; i < 4; i++) {
		residue_ -= param_[i] + 1;
	}
	if (residue_ < 0) {
		param_[STRENGTH - 1] = 2;
		param_[TECHNIC - 1] = 2;
		param_[SPEED - 1] = 2;
		param_[HP - 1] = 2;
		residue_ = 0;
	}
	if(csv!=nullptr)
		delete csv;
	csv = nullptr;

	CsvReader* csvtext = new CsvReader("Assets\\Status\\PreparationMessage.csv");
	for (int i = 0; i < 6; i++) {
		message_[i] = csvtext->GetString(i, 1);
	}
	if(csvtext!=nullptr)
		delete csvtext;
	csvtext = nullptr;
}

void PlayPreparationState::ParameterWrite()
{
	std::ifstream ifs("Assets\\Status\\PlayerParameter.csv",std::ios::in);
	if (ifs.fail())
		assert(false);

	std::string text;
	std::string temp="";

	while (std::getline(ifs, text)) {
		filelinecount_++;
		if (filelinecount_ != 2)
			temp += text;
		else {
			temp += "5’iŠK," + std::to_string(param_[STRENGTH - 1] + 1) + ","
							+ std::to_string(param_[TECHNIC - 1] + 1) + ","
							+ std::to_string(param_[SPEED - 1] + 1) + ","
							+ std::to_string(param_[HP - 1] + 1) + ",";
		}
		temp += "\n";
	}
	ifs.close();


	std::ofstream ofs("Assets\\Status\\PlayerParameter.csv", std::ios::out);
	if (ofs.fail())
		assert(false);

	ofs << temp;

	ofs.close();
}

PlayPreparationState::PlayPreparationState(GameObject* parent)
	:GameObject(parent,"PlayPreparationState"), hImage_(-1), hImageState_(-1),hImageCursor_(-1)
{
	ParameterReader();
	poscount_ = 0;
	button_ = true;
	startflag_ = false;
	residue_ = STATUSMEMORYMAX;
	filelinecount_ = 0;
	messagenum_ = 0;
	cursorflag_ = false;
}

void PlayPreparationState::Initialize()
{
	hImage_ = LoadGraph("Assets\\Image\\PlayPreparationState.png");
	assert(hImage_ > 0);
	hImageState_ = LoadGraph("Assets\\Image\\StateMemoryFrame.png");
	assert(hImageState_ > 0);
	hImageCursor_ = LoadGraph("Assets\\Image\\Arrow.png");
	assert(hImageCursor_ > 0);

	Instantiate<OutText>(GetParent());
	ParameterReader();

}

void PlayPreparationState::Update()
{
	int paramvar = 0;

	GetJoypadXInputState(DX_INPUT_PAD1, &pad);

	if (button_ == false) {
		if (CheckHitKey(KEY_INPUT_UP) || pad.ThumbLY >= 10000) {
			poscount_--;
			button_ = true;
			cursorflag_ = true;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) || pad.ThumbLY <= -10000) {
			poscount_++;
			button_ = true;
			cursorflag_ = true;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) || pad.ThumbLX <= -10000) {
			paramvar--;
			button_ = true;
			cursorflag_ = true;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) || pad.ThumbLX >= 10000) {
			paramvar++;
			button_ = true;
			cursorflag_ = true;
		}
	}
	if (!CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && !CheckHitKey(KEY_INPUT_LEFT) && !CheckHitKey(KEY_INPUT_RIGHT) &&
		pad.ThumbLY < 10000 && pad.ThumbLY > -10000 && pad.ThumbLX < 10000 && pad.ThumbLX > -10000)
		button_ = false;
	if (poscount_ >= 5)
		poscount_ = 0;
	if (poscount_ < 0)
		poscount_ = 4;

	if (cursorflag_)
		messagenum_ = poscount_ + 1;
	else
		messagenum_ = 0;


	if (poscount_ == 4) {
		if (CheckHitKey(KEY_INPUT_RETURN)||pad.Buttons[XINPUT_BUTTON_A]|| pad.Buttons[XINPUT_BUTTON_B]|| pad.Buttons[XINPUT_BUTTON_START])
			startflag_ = true;
	}
	if (poscount_ >= 0 && poscount_ < 4) {
		if (residue_ > 0) {
			if (param_[poscount_] < 4 && paramvar == 1) {
				param_[poscount_] += paramvar;
				residue_--;
			}
		}
		if (residue_ < STATUSMEMORYMAX) {
			if (param_[poscount_] > 0 && paramvar == -1) {
				param_[poscount_] += paramvar;
				residue_++;
			}
		}
	}

}

void PlayPreparationState::Draw()
{
	OutText* text = GetParent()->FindGameObject<OutText>();
	//DrawGraph(150, 0, hImage_, true);
	DrawExtendGraph(MAINIMAGEPOS.x, MAINIMAGEPOS.y, MAINIMAGEPOS.x + 1 + IMAGESIZE.x * 0.8, MAINIMAGEPOS.y + 1 + IMAGESIZE.y * 0.8, hImage_, true);

	text->DrawStringJ("ƒmƒRƒŠ", RESIDUEMESSAGEPOS.x, RESIDUEMESSAGEPOS.y, false);
	text->DrawString(std::to_string(residue_), RESIDUEPOS.x, RESIDUEPOS.y,false);
	for (int i = 0; i < 4; i++) {
		DrawBox(FRAMEPOS.x, FRAMEPOS.y + i * FRAMEBUFFER, FRAMEPOS.x + 96 + GAUGELENGTH[param_[i]], FRAMEPOS.y + i * FRAMEBUFFER + 32, GetColor(200, 200, 200), true);
		DrawGraph(FRAMEPOS.x, FRAMEPOS.y + i * FRAMEBUFFER, hImageState_, true);
	}
	DrawGraph(CURSORPOS[poscount_].x, CURSORPOS[poscount_].y, hImageCursor_, true);
	text->DrawStringJ(message_[messagenum_], MESSAGEPOS.x, MESSAGEPOS.y, false);


	text->DrawString("Start!", STARTPOS.x, STARTPOS.y,false);
}

void PlayPreparationState::Release()
{
	ParameterWrite();
}
