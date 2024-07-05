#pragma once
#include "Engine/GameObject.h"


class MoveObject :public GameObject
{

	int hImage_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	MoveObject(GameObject* parent);

	//�f�X�g���N�^
	~MoveObject();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

