#pragma once
#include "Engine/GameObject.h"


//オブジェクトを作るときのコピー用テンプレート
//注意：このオブジェクトを継承しないこと
class ClearLogo :public GameObject
{
	int hImage_;

	bool output_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	ClearLogo(GameObject* parent);

	//デストラクタ
	~ClearLogo();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

