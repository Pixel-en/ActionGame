#pragma once
#include "Enemy.h"


class Bard :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateMove() override;
	void UpdateRun() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

	float Idoltimer_;
	float sinangle_;
	VECTOR targetvec_;
	XMFLOAT3 targetpos_;
	float speed;
	XMFLOAT3 attackpos_;
	bool dirchenge_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Bard(GameObject* parent);

	//デストラクタ
	~Bard();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

