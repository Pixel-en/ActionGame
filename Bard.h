#pragma once
#include "Enemy.h"


class Bard :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateMove() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

	float Idoltimer_;
	float sinangle_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Bard(GameObject* parent);

	//�f�X�g���N�^
	~Bard();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

