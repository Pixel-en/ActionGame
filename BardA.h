#pragma once
#include "Enemy.h"
class BardA :public Enemy
{
	SIZE ENEMY_IMAGESIZE{ 80,80 };
	SIZE ENEMY_HITBOXSIZE{ 30,30 };
	const float ENEMY_LOOKRANGE{ 300 };

	XMFLOAT3 attackVector;

	bool yUp{ false };

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();
public:
	BardA(GameObject* parent);

	~BardA();
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
