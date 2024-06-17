#pragma once
#include "Engine/GameObject.h"

//材料のクラス
class Material :public GameObject
{
	int hImage_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Material(GameObject* parent);

	//デストラクタ
	~Material();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

