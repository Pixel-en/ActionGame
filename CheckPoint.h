#pragma once
#include "Object.h"


//オブジェクトを作るときのコピー用テンプレート
//注意：このオブジェクトを継承しないこと
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

	//開放
	void Release() override;
};

