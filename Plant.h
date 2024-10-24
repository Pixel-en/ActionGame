#pragma once
#include "Enemy.h"
#include "Bullet.h"

class Plant
	: public Enemy
{
	float baseHurtTime_{ 0.5 };

	enum  PlantAnimation
	{
		IDOL,
		ATTACK,
		HURT,
		DEATH
	};

	SIZE ENEMY_IMAGESIZE{ 80,80 };
	SIZE ENEMY_HITBOXSIZE{ 32,64 };

	Bullet* bullet_ = nullptr;

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateHurt() override;
	void UpdateDeath() override;
public:
	Plant(GameObject* parent);

	~Plant();
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	SIZE GetImageSize();

	void DeadState();
};

