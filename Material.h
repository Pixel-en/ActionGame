#pragma once
#include "Object.h"

//材料のクラス
class Material :public Object
{

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

	//開放
	void Release() override;
};

