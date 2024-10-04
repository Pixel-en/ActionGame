#pragma once
#include "Object.h"
#include "HitObject.h"
#include "Player.h"
#include "Camera.h"
#include "Clear.h"

//プレイヤーが当たったらプレイヤーの負け
//攻撃してくる
//
namespace {
	const SIZE ENEMY_IMAGESIZE{ 128,128 };
	const float ENEMY_LOOKRANGE{ 150 };
	const float ENEMY_ATTACKRANGE{ 101.5f };
	const float ENEMY_GRAVITY{ 9.8f / 60.0f };	//重力
	const VECTOR ENEMY_LUPOINT{ 34.0f,90.0f };	//左上の座標
	const VECTOR ENEMY_RUPOINT{ 94.0f,90.0f };	//右上の座標
	const VECTOR ENEMY_LDPOINT{ 34.0f,127.0f };	//左下の座標
	const VECTOR ENEMY_RDPOINT{ 94.0f,127.0f };	//右下の座標
	const SIZE ENEMY_HITBOXSIZE{ 60,37 };
	const float ENEMY_JUMPHEIGHT{ ENEMY_IMAGESIZE.cx * 1.5f };	//ジャンプの高さ
	//const float ENEMY_MOVESPEED{ 85 };
	//const float ENEMY_RUNSPEED{ 170 };	//ダッシュスピード
	const float ENEMY_ATTACKSPEED{ 1500 };
	const float ENEMY_SPEEDDOWN{ 50 };
	/*const float ENEMY_MOVETIME{ 1.0f };
	const int ENEMY_HP{ 10 };*/
}

enum ENEMY_TYPE
{
	BLUE_SLIME, GREEN_SLIME, RED_SLIME, ENEMY_TYPE_END
	//今はENEMY_TYPE_END以外使ってない
};
const int Status_Size{ 4 };

//敵のクラス
class Enemy:public Object
{
protected:
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

	virtual void UpdateIdol();
	virtual void UpdateMove();
	virtual void UpdateRun();
	virtual void UpdateAttack();
	virtual void UpdateDeath();

	//プレイヤーが検知エリアに入ったかどうか
	bool IsExistPlayer(float _range);

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

	bool isdeath() { return (animtype_ == EAnimation::DEATH); }
	
	void StatusReader(int _enemyNumber);
};

