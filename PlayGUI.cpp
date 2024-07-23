#include "PlayGUI.h"
#include <locale>

namespace {
	SIZE FONTSIZE{ 18,18 };
}

int PlayGUI::CharNum(char c)
{
	if (std::toupper(c) >= 65)
		return std::toupper(c) - 65;
	else if (std::toupper(c) >= 48 && std::toupper(c) <= 57)
		return std::toupper(c) - 48 + 26;
}

PlayGUI::PlayGUI(GameObject* parent)
	:hImage_(0)
{
}

PlayGUI::~PlayGUI()
{
}

void PlayGUI::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\Font.png");
	assert(hImage_ > 0);
	hImageUI_ = LoadGraph("Assets\\Image\\UI2.png");
	assert(hImageUI_ > 0);

}

void PlayGUI::Update()
{

}

void PlayGUI::Draw()
{
	for (int i = 0; i < 3; i++) {
		DrawRectGraph(0 + i * 32, 0, 0 + 36 * (i + 6), 36* 16, 32, 32, hImageUI_, true);
	}

	DrawString("test", 0, 0);
}

void PlayGUI::Release()
{
}

void PlayGUI::DrawString(std::string _text, float _posx, float _posy)
{
	for (int i = 0; i < _text.size(); i++) {
		int num = CharNum(_text[i]);
		DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0 + num * FONTSIZE.cx, 0, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
	}
}
