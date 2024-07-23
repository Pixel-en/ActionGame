#include "TitleText.h"

namespace {
	const SIZE FONTSIZE{ 36 , 36 };
}

int TitleText::CharNum(char c)
{
	if (std::toupper(c) >= 65)
		return std::toupper(c) - 65;
	else if (std::toupper(c) >= 48 && std::toupper(c) <= 57)
		return std::toupper(c) - 48 + 26;
}

void TitleText::DrawString(std::string _text, float _posx, float _posy)
{
	for (int i = 0; i < _text.size(); i++) {
		int num = CharNum(_text[i]);
		DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0 + num * FONTSIZE.cx, 0, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
	}
	//MessageBox(NULL, "test", NULL, MB_OK);
}

TitleText::TitleText(GameObject* parent)
	:GameObject(parent,"TitleText"),hImage_(0)
{
}

TitleText::~TitleText()
{
}

void TitleText::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\Font2.png");
	assert(hImage_ > 0);
}

void TitleText::Update()
{
}

void TitleText::Draw()
{
}

void TitleText::Release()
{
}
