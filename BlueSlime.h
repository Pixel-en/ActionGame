#pragma once
#include "Enemy.h"
class BlueSlime :public Enemy
{
	SIZE ENEMY_IMAGESIZE{ 48,48 };
	SIZE ENEMY_HITBOXSIZE{ 48 / 2,48 / 2 };

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	BlueSlime(GameObject* parent);

	~BlueSlime();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;
};

