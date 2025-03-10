#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "OutText.h"
#include "Camera.h"
#include "ScoreAndTimeAndMap.h"
#include "ImGui/imgui.h"

namespace {
	const float WAITTIME{ 2.0f };
}

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hImage_(0),updown(true),button_(false),decision_(false),speed(0)
	,x(0),y(0),wait_(0)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{

	hImage_ = LoadGraph("Assets\\Image\\Title.png");
	assert(hImage_ > 0);
	hImage2_ = LoadGraph("Assets\\Image\\Arrow.png");
	assert(hImage2_ > 0);

	Instantiate<OutText>(this);
	transform_.position_.x = 0;
	transform_.position_.y = 0;
	x = 650;
	y = 500;

	ScoreAndTimeAndMap::MapReset();

	PlayMusic("Assets\\Sounds\\BGM\\Start.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(255);
}

void TitleScene::Update()
{

	GetJoypadXInputState(DX_INPUT_PAD1, &pad);

	if (!decision_) {
		if (button_ == false) {
			if (CheckHitKey(KEY_INPUT_UP)||pad.ThumbLY>=10000) {
				if (!updown) {
					if (SE::CheckSE(SE::SENAME::Pr_Choise) == 1)
						SE::StopSE(SE::SENAME::Pr_Choise);

					SE::PlaySE(SE::SENAME::Pr_Choise);
				}

				updown = true;
				button_ = true;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) || pad.ThumbLY <= -10000) {

				if (updown) {
					if (SE::CheckSE(SE::SENAME::Pr_Choise) == 1)
						SE::StopSE(SE::SENAME::Pr_Choise);

					SE::PlaySE(SE::SENAME::Pr_Choise);
				}

				updown = false;
				button_ = true;
			}
		}
		if (!CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && pad.ThumbLY > -10000 && pad.ThumbLY < 10000)
			button_ = false;

		if (updown) {
			y = 490;
		}
		else {
			y = 540;
		}
	}

	if ((CheckHitKey(KEY_INPUT_RETURN) || pad.Buttons[XINPUT_BUTTON_A] || pad.Buttons[XINPUT_BUTTON_B] || pad.Buttons[XINPUT_BUTTON_START]) && !decision_) {
		decision_ = true;
		SE::PlaySE(SE::SENAME::T_Choise);
	}

	if (decision_) {
		//BGMを止める
		if (CheckMusic() == 1)
			StopMusic();

		if (wait_ < WAITTIME)
			wait_ += Time::DeltaTime();
		else {
			SE::StopSE(SE::SENAME::T_Choise);
			wait_ = WAITTIME;
			speed += 20;
			transform_.position_.x -= speed * Time::DeltaTime();
			if (transform_.position_.x <= -1280 * 3) {
				if (updown) {
					SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PREPARATION);
				}
				else
					SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TUTORIAL);
			}

		}
	}

}

void TitleScene::Draw()
{
	int xpos = transform_.position_.x;
	int ypos = transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		xpos -= cam->GetValue();
		ypos -= cam->GetValueY();
	}

	DrawGraph(xpos, ypos, hImage_, true);

	DrawGraph(xpos+x, ypos+y, hImage2_, true);

	OutText* tt = FindGameObject<OutText>();
	tt->DrawStringJ("スタート", xpos + 700, ypos + 500);
	tt->DrawStringJ("チュートリアル", xpos + 700, ypos + 550,true);
}
