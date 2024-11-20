#pragma once
#include "Enemy.h"


class Skeleton :public Enemy
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
	float attacktimer_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Skeleton(GameObject* parent);

	//�f�X�g���N�^
	~Skeleton();

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

