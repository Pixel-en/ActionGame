#pragma once
#include "Enemy.h"


class Skeleton :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateMove() override;
	void UpdateRun() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

	float Idoltimer_;
	float damegetimer_;

	bool isattack_;
	float attacktimer_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Skeleton(GameObject* parent);

	//デストラクタ
	~Skeleton();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool EnemyAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox) override;

};

