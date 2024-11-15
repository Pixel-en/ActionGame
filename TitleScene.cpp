#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "TitleText.h"
#include "Camera.h"

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

	Instantiate<TitleText>(this);
	transform_.position_.x = 0;
	transform_.position_.y = 0;
	x = 650;
	y = 500;
}

void TitleScene::Update()
{
	if (!decision_) {
		if (button_ == false) {
			if (CheckHitKey(KEY_INPUT_W)) {
				updown = true;
				button_ = true;
			}
			if (CheckHitKey(KEY_INPUT_S)) {
				updown = false;
				button_ = true;
			}
		}
		if (!CheckHitKey(KEY_INPUT_W) && !CheckHitKey(KEY_INPUT_S))
			button_ = false;

		if (updown)
			y = 500;
		else
			y = 550;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) || decision_) {
		decision_ = true;

		if (wait_ < WAITTIME)
			wait_ += Time::DeltaTime();
		else {
			wait_ = WAITTIME;
			speed += 20;
			transform_.position_.x -= speed * Time::DeltaTime();
			if (transform_.position_.x <= -1280 * 3) {
				if (updown) {
					SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PREPARATION);
				}
				else
					SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_CLEAR);
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

	TitleText* tt = FindGameObject<TitleText>();
	tt->DrawString(L"‚ ‚¢‚¤‚¦‚¨", xpos + 700, ypos + 500);
	tt->DrawString(L"Clear", xpos + 700, ypos + 550,false);
}
