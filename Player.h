#pragma once
#include "Engine/GameObject.h"


class Player :public GameObject
{

	int hImage_;

	void TestFunc();
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool HitCheck(int _x, int _y, SIZE _size);

};

