#pragma once
#include "Object.h"
#include "HitObject.h"

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//

//敵のクラス
class Enemy:public Object
{

	float movetimer_;
	bool startmove_;

	float Gaccel = 0;

	bool charge;

	float speed_;
	int range_;
	bool onGround_;

	int dir_;
	XMFLOAT3 Ppos;


	int attackfrm_;

	XMFLOAT3 SpawnPoint_;	//初期値

	enum  EAnimation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		HURT,
		DEATH
	};

	EAnimation animtype_;
	EAnimation BEanimtype_;

	void AnimationCheck();

	/// <summary>
	/// 敵とプレイヤーの距離
	/// </summary>
	float EPDistance();

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();


	HitObject* hitobj_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize() override;

	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool IsHitting() override;

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;
private:

	//プレイヤーが検知エリアに入ったかどうか
	bool IsExistPlayer(float _range);

};

