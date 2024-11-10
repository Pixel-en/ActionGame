//#pragma once
//#include "Enemy.h"
//#include "Explosion.h"
//
//class Skeleton 
//	: public Enemy
//{
//	float baseHurtTime_{ 0.5 };
//
//	bool isAttack;
//
//	enum  SkeletonAnimation
//	{
//		IDOL,
//		MOVE,
//		RUN,
//		ATTACK,
//		HURT,
//		DEATH
//	};
//
//	float ENEMY_ATTACKRANGE{ 50.0f };
//
//	SIZE ENEMY_IMAGESIZE{ 64,64 };
//	SIZE ENEMY_HITBOXSIZE{ 48,48 };
//
//	Explosion* explosion_ = nullptr;
//
//	void UpdateIdol() override;
//	void UpdateMove() override;
//	void UpdateRun() override;
//	void UpdateAttack() override;
//	void UpdateHurt() override;
//	void UpdateDeath() override;
//public:
//	Skeleton(GameObject* parent);
//
//	~Skeleton();
//	//èâä˙âª
//	void Initialize() override;
//
//	//çXêV
//	void Update() override;
//
//	//ï`âÊ
//	void Draw() override;
//
//	//äJï˙
//	void Release() override;
//
//	SIZE GetImageSize();
//
//	void DeadState();
//};
//
