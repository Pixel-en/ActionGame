#pragma once
#include "Object.h"

//�ޗ��̃N���X
class Material :public Object
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Material(GameObject* parent);

	//�f�X�g���N�^
	~Material();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�J��
	void Release() override;
};

