#pragma once
#include "Enemy.h"
class BlueSlime :public Enemy
{
	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	BlueSlime(GameObject* parent);

	~BlueSlime();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;
};

