#pragma once
#include "Enemy.h"

class Skeleton 
	: public Enemy
{
	float baseHurtTime_{ 0.5 };

	enum  SkeletonAnimation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		HURT,
		DEATH
	};

	float ENEMY_ATTACKRANGE{ 50.0f };

	SIZE ENEMY_IMAGESIZE{ 64,64 };
	SIZE ENEMY_HITBOXSIZE{ 48,48 };

	void UpdateIdol() override;
	void UpdateMove() override;
	void UpdateRun() override;
	void UpdateAttack() override;
	void UpdateHurt() override;
	void UpdateDeath() override;
public:
	Skeleton(GameObject* parent);

	~Skeleton();
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
};

