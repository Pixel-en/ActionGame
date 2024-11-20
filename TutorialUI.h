#pragma once
#include "Engine/GameObject.h"

class TutorialUI :public GameObject
{
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	TutorialUI(GameObject* parent);

	//デストラクタ
	~TutorialUI();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

