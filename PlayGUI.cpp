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
	const float COUNTTIMER{ 0.5f };
	const float STARTTIMER{ 1.0f };
	const SIZE UIICON{ 32,32 };
	const SIZE HEARTNUM{ 39,10 };
}

PlayGUI::PlayGUI(GameObject* parent)
	:hImage_(0),hImageUI_(0),x(0),y(0),text(""),CDtimer_(0),outset_(false),playtimer_(0),hImageHeart_(0)
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
	hImageHeart_ = LoadGraph("Assets\\Image\\UI_ICON.png");
	assert(hImageHeart_ > 0);
	hImageBonus_ = LoadGraph("Assets\\Image\\Bonus.png");
	assert(hImageBonus_ > 0);

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
	starttimer_ = STARTTIMER;

	Bonusalpha_ = 0;
	bonusE = true;
	bonusM = true;
}

void PlayGUI::Update()
{

	PlayScene* pc = dynamic_cast<PlayScene*>(GetParent());
	playtimer_ = pc->GetPlayTimer();
	if (pc->isStart() && starttimer_ > 0.0) {
		starttimer_ -= Time::DeltaTime();
	}

	if (Bonusalpha_ > -1) {
		Bonusalpha_-=5;
		bonuspos_.y -= 100 * Time::DeltaTime();
	}

	Player* p = GetParent()->FindGameObject<Player>();
	Clear* c = GetParent()->FindGameObject<Clear>();
	if (c->GetBonusEnemy()&&bonusE) {
		Bonusalpha_ = 255;
		c->DeleteEnemy();
		bonuspos_ = p->GetPosition();
		bonusE = false;
	}
	if (c->GetBonusMaterial() && bonusM){
		Bonusalpha_ = 255;
		c->DeleteMaterial();
		bonuspos_ = p->GetPosition();
		bonusM = false;
	}

	std::list<Material*> m = GetParent()->FindGameObjects<Material>();
	std::list<Enemy*> e = GetParent()->FindGameObjects<Enemy>();
	Enum = e.size();
	Mnum = m.size();
	if (p == nullptr)
		return;
	
	if (p->IsAnimState(p->IDOL) && outset_) {
		if (CDtimer_ > 0)
			CDtimer_ -= Time::DeltaTime();
		else {
			CDtimer_ = 0;
			transform_.position_.x += 150 * Time::DeltaTime();
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
	pHP_ = p->GetHp();

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
		
	//体力表示
	for (int i = 0; i < chipnum_.size(); i++) {
		//DrawRectGraph(0 + i * UISIZM.cx, 0, 0 + (UISIZM.cx+8) * (i + 6), (UISIZM.cy+8)* 16, UISIZM.cx, UISIZM.cy, hImageUI_, true);
		DrawRectGraph(xpos + 10 + i % 4 * UISIZE.cx, 150 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}
	DrawRectGraph(xpos + 20, 165, (UIICON.cx+2) * HEARTNUM.cx, (UIICON.cy+2) * HEARTNUM.cy, UIICON.cx, UIICON.cy, hImageHeart_, true);
	DrawString(std::to_string(pHP_), xpos + UIICON.cx + 30, 170);

	//残り時間表示
	for (int i = 0; i < chipnum_.size(); i++) {
		DrawRectGraph(550 + i % 4 * UISIZE.cx, 10 + i / 4 * UISIZE.cy, (UISIZE.cx + UIBUFFER) * chipnum_[i].x, (UISIZE.cy + UIBUFFER) * chipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}

	DrawString(std::to_string(playtimer_), 565, 30);

	//文字表示
	Clear* c = GetParent()->FindGameObject<Clear>();
	PlayScene* pc = GetRootJob()->FindGameObject<PlayScene>();
	if (!pc->isStart()) {
		DrawString("ready", 550, 350);
	}
	else {
		if (starttimer_ > 0.0) {
			DrawString("Start", 550, 350);
		}
	}
	if (c->GetFlag()) {
		DrawString("CLEAR", 550, 350);
	}

	//スコア表示
	for (int i = 0; i < scorechipnum_.size(); i++) {
		DrawRectGraph(900+i%6*UISIZE.cx,10+i/6*UISIZE.cy,(UISIZE.cx + UIBUFFER) * scorechipnum_[i].x, (UISIZE.cy + UIBUFFER) * scorechipnum_[i].y, UISIZE.cx, UISIZE.cy,
			hImageUI_, true);
	}

	this->DrawString("Score", 905, 20);
	this->DrawString(std::to_string(ScoreAndTimeAndMap::GetScore()), 905, 60);

	Camera* cam = GetParent()->FindGameObject<Camera>();

	if (Bonusalpha_>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Bonusalpha_);
		DrawGraph(bonuspos_.x-cam->GetValue(), bonuspos_.y-cam->GetValueY(), hImageBonus_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Bonusalpha_);
	}
}

void PlayGUI::Release()
{
}

void PlayGUI::DrawString(std::string _text, float _posx, float _posy)
{
	OutText* out = GetParent()->FindGameObject<OutText>();
	out->DrawString(_text, _posx, _posy);
}
