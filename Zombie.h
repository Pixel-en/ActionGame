//#pragma once
//#include "Enemy.h"
//
//class Zombie :
//    public Enemy
//{
//	float baseHurtTime_{ 0.5 };
//
//	enum  ZombieAnimation
//	{
//		IDOL,
//		RUN,
//		ATTACK,
//		HURT,
//		DEATH
//	};
//
//	float ENEMY_ATTACKRANGE{ 50.0f };
//
//	SIZE ENEMY_IMAGESIZE{ 80,80 };
//	SIZE ENEMY_HITBOXSIZE{ 32,64 };
//
//	void UpdateIdol() override;
//	void UpdateRun() override;
//	void UpdateAttack() override;
//	void UpdateHurt() override;
//	void UpdateDeath() override;
//public:
//	Zombie(GameObject* parent);
//
//	~Zombie();
//	//初期化
//	void Initialize() override;
//
//	//更新
//	void Update() override;
//
//	//描画
//	void Draw() override;
//
//	//開放
//	void Release() override;
//
//	SIZE GetImageSize();
//
//	void DeadState();
//};
//
