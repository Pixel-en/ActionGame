#pragma once
#include "Object.h"

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//

//敵のクラス
class Enemy:public Object
{

	float movetimer_;
	bool startmove_;

	float Gaccel = 0;

	float speed_;
	int range_;
	bool onGround_;

	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数

	XMFLOAT3 SpawnPoint_;	//初期値

	enum  Animation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		DEATH
	};

	Animation animtype_;

	/// <summary>
	/// 敵とプレイヤーの距離
	/// </summary>
	float EPDistance();

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();

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

	SIZE GetImageSize();

private:

	//プレイヤーが検知エリアに入ったかどうか
	bool IsExistPlayer(float _range);

};

