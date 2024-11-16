#pragma once
#include "Engine/GameObject.h"

class PlayPreparationState :public GameObject
{

	int hImage_;
	int hImageState_;

	void ParameterReader();
	void ParameterWrite();

	int param_[4];

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayPreparationState(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

