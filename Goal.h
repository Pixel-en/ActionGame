#pragma once
#include "Engine/GameObject.h"

//ゴールを扱うクラス
class Goal :public GameObject
{

	int hImage_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Goal(GameObject* parent);

	//デストラクタ
	~Goal();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPosition(int _x, int _y) {
		transform_.position_.x = _x;
		transform_.position_.y = _y;
	};
};

