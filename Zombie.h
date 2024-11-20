#pragma once
#include "Enemy.h"


class Zombie :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateMove() override;
	void UpdateRun() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

	float Idoltimer_;
	float damegetimer_;

	bool isattack_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Zombie(GameObject* parent);

	//�f�X�g���N�^
	~Zombie();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool EnemyAttackHitCheck(XMFLOAT3 _trans, VECTOR _hitbox) override;

};

