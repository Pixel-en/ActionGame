#pragma once
#include "Engine/GameObject.h"

class Field :public GameObject
{
	int hImage_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Field(GameObject* parent);

	//�f�X�g���N�^
	~Field();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

