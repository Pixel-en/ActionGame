#pragma once
#include "Engine/GameObject.h"

class PlayPreparationState :public GameObject
{

	int hImage_;
	int hImageState_;

	void ParameterReader();
	void ParameterWrite();

	int param_[4];

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayPreparationState(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

