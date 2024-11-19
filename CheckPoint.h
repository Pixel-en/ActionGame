#pragma once
#include "Object.h"


class CheckPoint :public Object
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	CheckPoint(GameObject* parent);

	//�f�X�g���N�^
	~CheckPoint();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void AddScore();
};

