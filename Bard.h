#pragma once
#include "Enemy.h"

class Bard 
	: public Enemy
{
	float baseHurtTime_{ 0.5 };

	enum  BardAnimation
	{
		IDOL,
		MOVE,
		ATTACK,
		HURT,
		DEATH
	};
	SIZE ENEMY_IMAGESIZE{ 80,80 };
	SIZE ENEMY_HITBOXSIZE{ 30,30 };
	const float ENEMY_LOOKRANGE{ 300 };

	XMFLOAT3 attackVector;

	bool yUp{ false };

	void UpdateIdol() override;
	void UpdateMove() override;
	/*void UpdateRun() override;*/
	void UpdateAttack() override;
	void UpdateHurt() override;
	void UpdateDeath() override;
public:
	Bard(GameObject* parent);

	~Bard();
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
