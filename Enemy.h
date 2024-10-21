#pragma once
#include "Object.h"
#include "HitObject.h"
#include "Player.h"
#include "Camera.h"
#include "Clear.h"
#include <vector>

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//
namespace {

	const float ENEMY_ATTACKRANGE{ 101.5f };
	const float ENEMY_GRAVITY{ 9.8f / 60.0f };	//重力

	const float ENEMY_ATTACKSPEED{ 1500 };
	const float ENEMY_SPEEDDOWN{ 50 };
}

enum ENEMY_TYPE
{
	SLIME_A, SLIME_B, SLIME_C, BARD_A, ENEMY_TYPE_END
};
const int Status_Size{ 4 };

//敵のクラス
class Enemy:public Object
{
protected:
	const SIZE ENEMY_IMAGESIZE{ 48,48 };
	const SIZE ENEMY_HITBOXSIZE{ 48 / 2,48 / 2 };
	const float ENEMY_JUMPHEIGHT{ ENEMY_IMAGESIZE.cx * 1.5f };	//ジャンプの高さ
	const float ENEMY_LOOKRANGE{ 150 };
	//次に動くまでのタイマー
	float movetimer_;
	float baseMovetimer;
	//動き始めたか
	bool startmove_;
	//重力加速度？
	float Gaccel = 0;

	bool charge;
	//スピード
	float speed_;
	float baseSpeed;
	float baseRunSpeed;
	//検知距離
	int range_;
	//設置判定
	bool onGround_;
	//向き
	int dir_;
	//
	XMFLOAT3 Ppos;
	//体力
	int hp_;
	int baseHp;

	int attackfrm_;

	XMFLOAT3 SpawnPoint_;	//初期値
	XMFLOAT3 TargetPoint_;

	enum  EAnimation
	{
		MOVE,
		ATTACK,
		IDOL,
		RUN,
		HURT,
		DEATH
	};

	EAnimation state_;
	EAnimation BEanimtype_;

	void AnimationCheck();

	/// <summary>
	/// 敵とプレイヤーの距離
	/// </summary>
	float EPDistance();
	XMFLOAT3 EPVector();
	XMFLOAT3 TargetPos();

	virtual void UpdateIdol();
	virtual void UpdateMove();
	virtual void UpdateRun();
	virtual void UpdateAttack();
	virtual void UpdateDeath();

	//プレイヤーが検知エリアに入ったかどうか
	bool IsExistPlayer(float _range);

	HitObject* hitobj_;

	Transform hittransform_;

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

	bool isdeath() { return (state_ == EAnimation::DEATH); }
	
	void StatusReader(int _enemyNumber);

	VECTOR GetCenter() { return VECTOR{ transform_.position_.x + ENEMY_IMAGESIZE.cx / 2, transform_.position_.y + ENEMY_IMAGESIZE.cy / 2 }; };

	Transform GetHitTransform() { return hittransform_; };
};

