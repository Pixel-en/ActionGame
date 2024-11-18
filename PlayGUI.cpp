#include "PlayGUI.h"
#include <locale>
#include "Enemy.h"
#include "Material.h"
#include "Player.h"
#include "PlayScene.h"
#include "Clear.h"
#include "OutText.h"
#include "ScoreAndTimeAndMap.h"

namespace {
	const SIZE FONTSIZE{ 32,36 };
	const SIZE UISIZE{ 32,32 };
	const int UIBUFFER{ 4 };
	const float COUNTTIMER{ 1.0f };
}

PlayGUI::PlayGUI(GameObject* parent)
	:hImage_(0),hImageUI_(0),x(0),y(0),text(""),CDtimer_(0),outset_(false),playtimer_(0)
{
	chipnum_ = { {6,18},{7,18},{7,18},{8,18},
			   {6,20},{7,20},{7,20},{8,20}, };
	scorechipnum_ = { {6,18},{7,18},{7,18},{7,18},{7,18},{8,18},
					  {6,19},{7,19},{7,19},{7,19},{7,19},{8,19},
					  {6,20},{7,20},{7,20},{7,20},{7,20},{8,20}, };
	transform_.position_.x = 0;
}

PlayGUI::~PlayGUI()
{
}

void PlayGUI::Initialize()
{
	hImageUI_ = LoadGraph("Assets\\Image\\UI2.png");
	assert(hImageUI_ > 0);
	hImagekey_ = LoadGraph("Assets\\Image\\Key.png");
	assert(hImagekey_ > 0);

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
	Instantiate<OutText>(GetParent());

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
	
	if (p->IsAnimState(p->IDOL)&&outset_) {
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
		DrawRectGraph(550 + i % 4 * UISIZE.cx, 10 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}

	DrawString(std::to_string(playtimer_), 565, 30);

	Clear* c = GetParent()->FindGameObject<Clear>();
	if (c->GetFlag()) {
		DrawString("CLEAR", 550, 350);
	}

	for (int i = 0; i < scorechipnum_.size(); i++) {
		DrawRectGraph(900+i%6*UISIZE.cx,10+i/6*UISIZE.cy,(UISIZE.cx + UIBUFFER) * scorechipnum_[i].x, (UISIZE.cy + UIBUFFER) * scorechipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}

	this->DrawString("Score", 905, 20);
	this->DrawString(std::to_string(ScoreAndTimeAndMap::GetScore()), 905, 60);
}

void PlayGUI::Release()
{
}

void PlayGUI::DrawString(std::string _text, float _posx, float _posy)
{
	OutText* out = GetParent()->FindGameObject<OutText>();
	out->DrawString(_text, _posx, _posy);
}
