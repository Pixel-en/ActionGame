#include "TutorialUI.h"
#include "Field.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include <list>

namespace {
	const VECTOR ICONSIZE{ 64,64 };
	const VECTOR ICON{ 570,300 };
	const VECTOR ICON2{ 660,300 };
	const VECTOR ICONORIGIN{ 620,300 };
	const VECTOR FRAMESIZE{ 32,32 };
	const int FRAMEBUFFER{ 4 };
	const int FRAMEX[6]{ 0,1,1,1,1,2 };
}

TutorialUI::TutorialUI(GameObject* parent)
	:GameObject(parent,"TutorialUI"),hImageGuide_(0),guidenum_(0),hImageFrame_(0)
{
	UIpos_ = { -1,-1 };
	Player* p = GetParent()->FindGameObject<Player>();
	transform_.position_ = { ICON.x,ICON.y,0 };

	UIpos2_ = { -1,-1 };
}

TutorialUI::~TutorialUI()
{
}

void TutorialUI::Initialize()
{
	hImageGuide_ = LoadGraph("Assets\\Image\\XBoxButton.png");
	assert(hImageGuide_ > 0);
	hImageFrame_ = LoadGraph("Assets\\Image\\UI2.png");
}

void TutorialUI::Update()
{

	std::list<Enemy*>Elist = GetParent()->FindGameObjects<Enemy>();
	for (auto E : Elist) {
		E->StateIDOL();
		E->DebugHp();
	}

	Field* f = GetParent()->FindGameObject<Field>();
	Player* p = GetParent()->FindGameObject<Player>();
	p->Invincible();
	switch (f->CollisionObjectCheckNumber(p->GetObjectCheckPos().x,p->GetObjectCheckPos().y))
	{
	case 300:	//移動
		UIpos_ = {0,0};
		UIpos2_ = { -1,-1 };
		break;
	case 301:	//ダッシュ
		UIpos_ = { 0,0 };
		UIpos2_ = { 0,1 };
		break;
	case 302:	//ジャンプ
		UIpos_ = { 0,3 };
		UIpos2_ = { -1,-1 };
		break;
	case 303:	//梯子
		UIpos_ = { 0,2 };
		UIpos2_ = { -1,-1 };
		break;
	case 304:	//採掘
		UIpos_ = { 0,4 };
		UIpos2_ = { -1,-1 };
		break;
	case 305:	//攻撃
		UIpos_ = { 0,5 };
		UIpos2_ = { 0,6 };
		break;
	case 306:	//攻撃
		UIpos_ = { 0,5 };
		UIpos2_ = { 0,7 };
		break;
	case 307:	//攻撃
		UIpos_ = { 0,5 };
		UIpos2_ = { 0,4 };
		break;
	case 308:	//魔法
		UIpos_ = { 0,8 };
		UIpos2_ = { 0,6 };
		break;
	case 309:	//魔法
		UIpos_ = { 0,8 };
		UIpos2_ = { 0,7 };
		break;
	default:
		break;
	}
}

void TutorialUI::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			DrawRectGraph(xpos + ((j - 1) * FRAMESIZE.x) + FRAMESIZE.x / 2, ypos + ((i - 1) * FRAMESIZE.y) + FRAMESIZE.y / 2,
				(FRAMESIZE.x + FRAMEBUFFER) * (FRAMEX[j] + 6), (FRAMESIZE.y + FRAMEBUFFER) * (18 + i), FRAMESIZE.x, FRAMESIZE.y, hImageFrame_, true);
		}
	}
	if (UIpos2_.y < 0) {
		DrawRectGraph(ICONORIGIN.x, ICONORIGIN.y, 0, UIpos_.y * ICONSIZE.y, ICONSIZE.x, ICONSIZE.y, hImageGuide_, true);
	}
	else {
		DrawRectGraph(ICON.x, ICON.y, 0, UIpos_.y * ICONSIZE.y, ICONSIZE.x, ICONSIZE.y, hImageGuide_, true);
		DrawRectGraph(ICON2.x, ICON2.y, 0, UIpos2_.y * ICONSIZE.y, ICONSIZE.x, ICONSIZE.y, hImageGuide_, true);
	}
}

void TutorialUI::Release()
{
}
