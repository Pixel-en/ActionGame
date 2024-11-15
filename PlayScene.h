#pragma once
#include "Engine/GameObject.h"
#include "vector"
#include "ScoreAndTime.h"

//テストシーンを管理するクラス
class PlayScene : public GameObject
{
private:
	std::string Filename_;

	//float playtimer_;	//プレイ中の制限時間

	float starttimer_;	//スタートするまでの待機時間のタイマー
	float counttimer_;	//クリアしてからの次に行くまでのタイマー
	float deathtimer_;	//死んでからのタイマー

	enum PlayState {
		STAY,
		PLAY,
		CLEAR,
		DEATH,
	};
	PlayState state;

	void UpdateStay();
	void UpdatePlay();
	void UpdateClear();
	void UpdateDeath();

	std::vector<std::string> maplist;
	int listnum;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	void Reset();

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool CanMove() { return (state == PlayState::PLAY); };

	void DeadState();

	float GetPlayTimer() { return Score::GetTime(); };
};