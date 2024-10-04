#pragma once
#include "Enemy.h"

class RedSlime :public Enemy
{
	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	RedSlime(GameObject* parent);

	~RedSlime();
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

	void DeadState();

	SIZE GetSize() override;
};


