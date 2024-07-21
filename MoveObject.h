#pragma once
#include "Object.h"


class MoveObject :public Object
{
	float sinAngle_;
	float baseY_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	MoveObject(GameObject* parent);

	//デストラクタ
	~MoveObject() override;

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Setpos(float x, float y);
};

