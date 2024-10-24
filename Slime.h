#pragma once
#include "Enemy.h"

class Slime 
	: public Enemy
{
	float baseHurtTime_{ 0.5 };

	enum  SlimeAnimation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		HURT,
		DEATH
	};

	float ENEMY_ATTACKRANGE{ 101.5f };

	SIZE ENEMY_IMAGESIZE{ 48,48 };
	SIZE ENEMY_HITBOXSIZE{ 48 / 2,48 / 2 };

	void UpdateIdol() override;
	void UpdateMove() override;
	void UpdateRun() override;
	void UpdateAttack() override;
	void UpdateHurt() override;
	void UpdateDeath() override;
public:
	Slime(GameObject* parent);

	~Slime();
	//èâä˙âª
	void Initialize() override;

	//çXêV
	void Update() override;

	//ï`âÊ
	void Draw() override;

	//äJï˙
	void Release() override;

	SIZE GetImageSize();

	void DeadState();
};

