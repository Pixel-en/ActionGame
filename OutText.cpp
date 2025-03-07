#include "OutText.h"
#include "Engine/CsvReader.h"

namespace {
	const SIZE FONTSIZE{ 37 , 22 };
}

char OutText::CharNum(char c)
{
	if (std::toupper(c) >= 65 && std::toupper(c) <= 90)
		return std::toupper(c);
	else if (std::toupper(c) >= 48 && std::toupper(c) <= 57)
		return std::toupper(c);

	return c;
}

void OutText::DrawString(std::string _text, float _posx, float _posy)
{
	DrawString(_text, _posx, _posy, true);
}

void OutText::DrawString(std::string _text, float _posx, float _posy, bool black)
{
	for (int i = 0; i < _text.size(); i++) {
		char c = CharNum(_text[i]);
		for (int j = 0; j < fontarr.size(); j ++) {
			if (fontarr[j]==c) {
				if (black)
					DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + j * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
				else
					DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + j * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImageW_, true);
				break;
			}
		}
	}
}

void OutText::DrawStringJ(std::string _text, float _posx, float _posy)
{
	DrawStringJ(_text, _posx, _posy, true);
}

void OutText::DrawStringJ(std::string _text, float _posx, float _posy, bool black)
{
	for (int i = 0; i < _text.size(); i += 2) {
		for (int j = 0; j < fontarrJ.size(); j += 2) {
			if (fontarrJ.substr(j, 2) == _text.substr(i, 2)) {
				if (black)
					DrawRectGraph(_posx + (i / 2) * FONTSIZE.cx, _posy, 0, 0 + (j / 2 + 38) * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
				else
					DrawRectGraph(_posx + (i / 2) * FONTSIZE.cx, _posy, 0, 0 + (j / 2 + 38) * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImageW_, true);
				break;
			}
		}
	}
}

OutText::OutText(GameObject* parent)
	:GameObject(parent,"OutText"),hImage_(0)
{
	fontarr =
		"0123456789!?ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	fontarrJ =
		"ァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヲンヴヵヶー";
}

OutText::~OutText()
{
}

void OutText::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\Font_zou.png");
	assert(hImage_ > 0);
	hImageW_ = LoadGraph("Assets\\Font\\Font_zou_white.png");
	assert(hImageW_ > 0);
}

void OutText::Update()
{
}

void OutText::Draw()
{
}

void OutText::Release()
{
}
