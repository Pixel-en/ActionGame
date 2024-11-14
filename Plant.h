#pragma once
#include "Enemy.h"


class Plant :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Plant(GameObject* parent);

	//デストラクタ
	~Plant();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

