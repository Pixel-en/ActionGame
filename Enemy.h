#pragma once
#include "Object.h"

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//

//敵のクラス
class Enemy:public Object
{
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//開放
	void Release() override;

	bool IsHitting() override;
};

