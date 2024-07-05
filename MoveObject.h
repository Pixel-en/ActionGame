#pragma once
#include "Engine/GameObject.h"


class MoveObject :public GameObject
{

	int hImage_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	MoveObject(GameObject* parent);

	//デストラクタ
	~MoveObject();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

