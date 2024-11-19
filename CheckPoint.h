#pragma once
#include "Object.h"


class CheckPoint :public Object
{

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	CheckPoint(GameObject* parent);

	//デストラクタ
	~CheckPoint();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void AddScore();
};

