#pragma once
#include "Enemy.h"
class BardA :public Enemy
{
	SIZE ENEMY_IMAGESIZE{ 80,80 };
	SIZE ENEMY_HITBOXSIZE{ 30,30 };
	const float ENEMY_LOOKRANGE{ 300 };

	XMFLOAT3 attackVector;

	bool yUp{ false };

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	BardA(GameObject* parent);

	~BardA();
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
