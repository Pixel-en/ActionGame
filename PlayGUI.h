#pragma once
#include "Engine/GameObject.h"

class PlayGUI final :public GameObject
{
	int hImage_;

	int CharNum(char c);

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	PlayGUI(GameObject* parent);

	//デストラクタ
	~PlayGUI();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

