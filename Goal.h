#pragma once
#include "Object.h"

//ゴールを扱うクラス
class Goal :public Object
{

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

	//開放
	void Release() override;


};

