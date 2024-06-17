#pragma once
#include "Engine/GameObject.h"

class Camera :public GameObject
{
	int value;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Camera(GameObject* parent) :GameObject(parent) { value = 0; };
	//デストラクタ
	~Camera() {};

	void SetValue(int v) { value = v; }
	int GetValue() { return value; }

	////初期化
	//void Initialize() override;

	////更新
	//void Update() override;

	////描画
	//void Draw() override;

	////開放
	//void Release() override;
};

