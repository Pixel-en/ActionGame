#pragma once
#include "Engine/GameObject.h"

//�ޗ��̃N���X
class Material :public GameObject
{
	int hImage_;

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

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

