#pragma once
#include "Enemy.h"

class GreenSlime :public Enemy
{
	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	GreenSlime(GameObject* parent);

	~GreenSlime();
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


