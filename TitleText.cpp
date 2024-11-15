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

void TitleText::DrawString(std::string _text, float _posx, float _posy)
{
	//for (int i = 0; i < _text.size(); i++) {
	//	int num = CharNum(_text[i]);
	//	DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + num * FONTSIZE.cy+0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
	//}
	//MessageBox(NULL, "test", NULL, MB_OK);

	for (int i = 0; i < _text.size(); i++) {
		char c = CharNum(_text[i]);
		for (int j = 0; j < fontarr.size(); j++) {
			if (fontarr[i] == c);
				DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + j * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
		}
	}
}

TitleText::TitleText(GameObject* parent)
	:GameObject(parent,"TitleText"),hImage_(0)
{
	fontarr =
		"0123456789!?ABCDEFGHIJKLMNOPQRSTUVWXYZァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヲンヴヵヶー";
}

TitleText::~TitleText()
{
}

void TitleText::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\Font_zou.png");
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
