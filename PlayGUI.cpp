#include "PlayGUI.h"
#include <locale>
#include "Enemy.h"
#include "Material.h"
#include "Player.h"
#include "PlayScene.h"
#include "Clear.h"

namespace {
	const SIZE FONTSIZE{ 32,36 };
	const SIZE UISIZE{ 32,32 };
	const int UIBUFFER{ 4 };
	const float COUNTTIMER{ 1.0f };
}

int PlayGUI::CharNum(char c)
{
	if (std::toupper(c) >= 65&&std::toupper(c) <= 90)
		return std::toupper(c) - 65;
	else if (std::toupper(c) >= 48 && std::toupper(c) <= 57)
		return std::toupper(c) - 48 + 26;

	return 255;
}

PlayGUI::PlayGUI(GameObject* parent)
	:hImage_(0),hImageUI_(0),x(0),y(0),text(""),CDtimer_(0),outset_(false),playtimer_(0)
{
	chipnum_ = { {6,18},{7,18},{7,18},{8,18},
			   {6,20},{7,20},{7,20},{8,20}, };
	transform_.position_.x = 0;
}

PlayGUI::~PlayGUI()
{
}

void PlayGUI::Initialize()
{
	hImage_ = LoadGraph("Assets\\Font\\text1.png");
	assert(hImage_ > 0);
	hImageUI_ = LoadGraph("Assets\\Image\\UI2.png");
	assert(hImageUI_ > 0);

	int x, y;

	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();

	Edata.handle = LoadGraph("Assets\\Image\\Slime.png");
	assert(Edata.handle > 0);
	GetGraphSize(Edata.handle, &x, &y);
	Edata.imagesize = { x,y };

	Mdata.handle = LoadGraph("Assets\\Image\\Crystal\\crystal_Black4.png");
	assert(Mdata.handle > 0);
	GetGraphSize(Mdata.handle,&x, &y );
	Mdata.imagesize = { x,y };

	CDtimer_ = COUNTTIMER;
	transform_.position_.x = -200;


}

void PlayGUI::Update()
{

	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());
	playtimer_ = pc->GetPlayTimer();

	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();
	Enum = e.size();
	Mnum = m.size();
	Player* p = GetParent()->FindGameObject<Player>();
	if (p == nullptr)
		return;
	
	if (p->isIdol()&&outset_) {
		if (CDtimer_ > 0)
			CDtimer_ -= Time::DeltaTime();
		else {
			CDtimer_ = 0;
			transform_.position_.x += 100 * Time::DeltaTime();
			if (transform_.position_.x > 0)
				transform_.position_.x = 0;
		}
	}
	else{
		outset_ = false;
		CDtimer_ = COUNTTIMER;
		transform_.position_.x -= 150 * Time::DeltaTime();
		if (transform_.position_.x < -200) {
			transform_.position_.x = -200;
			outset_ = true;
		}
	}


}

void PlayGUI::Draw()
{
	float xpos = transform_.position_.x;

	//敵の数
	for (int i = 0; i < chipnum_.size(); i++) {
		//DrawRectGraph(0 + i * UISIZE.cx, 0, 0 + (UISIZE.cx+8) * (i + 6), (UISIZE.cy+8)* 16, UISIZE.cx, UISIZE.cy, hImageUI_, true);
		DrawRectGraph(xpos + 10 + i % 4 * UISIZE.cx, 10 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}
	DrawRectGraph(xpos + 20, 20, 0, 0, Edata.imagesize.cx, Edata.imagesize.cy, Edata.handle,true);
	DrawString(std::to_string(Enum), xpos + Edata.imagesize.cx + 30, 20);

	//マテリアル表示
	for (int i = 0; i < chipnum_.size(); i++) {
		//DrawRectGraph(0 + i * UISIZM.cx, 0, 0 + (UISIZM.cx+8) * (i + 6), (UISIZM.cy+8)* 16, UISIZM.cx, UISIZM.cy, hImageUI_, true);
		DrawRectGraph(xpos + 10 + i % 4 * UISIZE.cx, 80 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}
	DrawRectGraph(xpos + 20, 90, 0, 0, Mdata.imagesize.cx, Mdata.imagesize.cy, Mdata.handle, true);
	DrawString(std::to_string(Mnum), xpos + Mdata.imagesize.cx + 30, 90);
	

	//残り時間表示
	for (int i = 0; i < chipnum_.size(); i++) {
		DrawRectGraph(550 + i % 4 * UISIZE.cx, 20 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}

	DrawString(std::to_string(playtimer_), 565, 30);

	Clear* c = GetParent()->FindGameObject<Clear>();
	if (c->GetFlag()) {
		DrawString("CLEAR", 550, 350);
	}
}

void PlayGUI::Release()
{
}

void PlayGUI::DrawString(std::string _text, float _posx, float _posy)
{
	for (int i = 0; i < _text.size(); i++) {
		int num = CharNum(_text[i]);
		DrawRectGraph(_posx + i * FONTSIZE.cx, _posy, 0, 0 + num * FONTSIZE.cy + 0.5f, FONTSIZE.cx, FONTSIZE.cy, hImage_, true);
	}
}
