#pragma once
#include "Object.h"

//�S�[���������N���X
class Goal :public Object
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Goal(GameObject* parent);

	//�f�X�g���N�^
	~Goal();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�J��
	void Release() override;


};

