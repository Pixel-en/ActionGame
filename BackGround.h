#pragma once
#include "Engine/GameObject.h"

class BackGround :public GameObject
{

	int hImage_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	BackGround(GameObject* parent);

	//デストラクタ
	~BackGround();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

