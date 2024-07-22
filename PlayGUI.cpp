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
	hImage_ = LoadGraph("Assets\\Font\\test.png", 1);
	assert(hImage_ > 0);
}

void PlayGUI::Update()
{

}

void PlayGUI::Draw()
{
	DrawString(0, 0, "Hello", GetColor(255, 255, 0), hImage_);
}

void PlayGUI::Release()
{
}
