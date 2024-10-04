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
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	bool IsHitting() override;

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;
};


