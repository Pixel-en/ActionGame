#include "TitleText.h"
#include "Engine/CsvReader.h"

namespace {
	const SIZE FONTSIZE{ 37 , 22 };
}

char TitleText::CharNum(char c)
{
	if (std::toupper(c) >= 65 && std::toupper(c) <= 90)
		return std::toupper(c);
	else if (std::toupper(c) >= 48 && std::toupper(c) <= 57)
		return std::toupper(c);

	return c;

}

void TitleText::DrawString(std::wstring _text, float _posx, float _posy)
{
	DrawString(_text, _posx, _posy, true);
}

void TitleText::DrawString(std::wstring _text, float _posx, float _posy, bool black)
{
	for (int i = 0; i < _text.size(); i++) {
		wchar_t c = _text[i];//CharNum(_text[i]);
		for (int j = 0; j < fontarr.size(); j++) {
			if (fontarr[j] == c) {
				if(black)
					DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + j * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
				else
					DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + j * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImageW_, true);
				break;
			}
		}
	}
}

TitleText::TitleText(GameObject* parent)
	:GameObject(parent,"TitleText"),hImage_(0)
{
	fontarr =
		L"0123456789!?ABCDEFGHIJKLMNOPQRSTUVWXYZァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヲンヴヵヶー";
}

TitleText::~TitleText()
{
}

void TitleText::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\Font_zou.png");
	assert(hImage_ > 0);
	hImageW_ = LoadGraph("Assets\\Font\\Font_zou_white.png");
	assert(hImageW_ > 0);
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
