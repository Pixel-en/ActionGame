#include "sceneManager.h"

#include "../TestScene.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "../ClaerScene.h"
#include "../PlayPreparationScene.h"
#include "../TutorialScene.h"
#include "time.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	Time::Init();
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
	SE::InitSE();
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();
		InitGraph();

		std::string filename = "";

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this);	break;
		case SCENE_ID_TUTORIAL: Instantiate<TutorialScene>(this); break;
		case SCENE_ID_PREPARATION: Instantiate<PlayPreparationScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_CLEAR:Instantiate<ClearScene>(this); break;

		}
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
	Time::Refresh();
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
	StopMusic();
}