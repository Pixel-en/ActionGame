#pragma once
#include "Object.h"

//�G�̃N���X
class Enemy:public Object
{
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�J��
	void Release() override;
};

