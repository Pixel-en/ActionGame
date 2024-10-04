#pragma once
#include "Enemy.h"
class BlueSlime :public Enemy
{
	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	BlueSlime(GameObject* parent);

	~BlueSlime();
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

	SIZE GetSize() override;
};

