#pragma once
#include "Object.h"

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//

//敵のクラス
class Enemy:public Object
{
	bool inmoving_;
	XMVECTOR despos_;

	float movetimer_;
	bool startmove_;

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

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool IsHitting() override;

private:

	//プレイヤーが検知エリアに入ったかどうか
	bool IsExistPlayer();

};

