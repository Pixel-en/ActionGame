#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class PlayScene : public GameObject
{
	std::string Filename_;

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
};