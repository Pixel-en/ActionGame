#pragma once
#include "Enemy.h"


class Plant :public Enemy
{

	void UpdateIdol() override;
	void UpdateAttack() override;
	void UpdateDamege() override;
	void UpdateDeath() override;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Plant(GameObject* parent);

	//�f�X�g���N�^
	~Plant();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

