#include "ClaerScene.h"
#include "Engine/SceneManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Camera.h"
#include "ClearPlayer.h"
#include "CleraLogo.h"
#include "TitleText.h"
#include "PlaySound.h"

#if 0
#include"RankingsSystem.h"

int InputHandle;
char Name[256];
std::string PlayerName;
#endif


ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent,"ClearScene"),hImage_(0)
{
}

void ClearScene::Initialize()
{
	Playsound* pc = Instantiate<Playsound>(this);
	pc->PlayMusics("Clear");

	Camera* cam=Instantiate<Camera>(this);

	Instantiate<BackGround>(this);

	Field* f = Instantiate<Field>(this);
	f->SetFileName("Clear.csv");
	cam->SetValue(100);
	cam->SetValueY(300);
	f->Reset();
	Clearplayer* cp = Instantiate<Clearplayer>(this);
	ClearLogo* logo = Instantiate<ClearLogo>(this);
	TitleText* tt = Instantiate<TitleText>(this);

#if 0
	// 描画先を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	InputHandle = MakeKeyInput(10, TRUE, FALSE, FALSE);
	SetActiveKeyInput(InputHandle);
#endif
}

void ClearScene::Update()
{
#if 0
	////入力が終了している場合は終了
	//if (CheckKeyInput(InputHandle) != 0) {
	//	GetKeyInputString(Name, InputHandle);
	//	PlayerName = Name;
	//	RankingsSystem::SetRankings(PlayerName, 100);
	//	// 用済みのインプットハンドルを削除する
	//	DeleteKeyInput(InputHandle);
	//}

	/*if(CheckHitKey(KEY_INPUT_RETURN)) {
		StopSound();
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_TITLE);
	}*/

	while (!ProcessMessage())
	{
		// 入力が終了している場合は終了
		if (CheckKeyInput(InputHandle) != 0) {
			/*GetKeyInputString(Name, InputHandle);

			PlayerName = Name;

			RankingsSystem::SetRankings(PlayerName, 100);*/
			break;
		}

		// 画面の初期化
		ClearDrawScreen();

		// 入力モードを描画
		DrawKeyInputModeString(640, 480);

		// 入力途中の文字列を描画
		DrawKeyInputString(0, 0, InputHandle);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	// 用済みのインプットハンドルを削除する
	DeleteKeyInput(InputHandle);

	//// 画面の初期化
	//ClearDrawScreen();
#endif
}


void ClearScene::Draw()
{
	DrawGraph(transform_.position_.x, transform_.position_.y, hImage_, true);

}

void ClearScene::Release()
{
}
