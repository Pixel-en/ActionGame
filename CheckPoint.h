#pragma once
#include "Object.h"


//�I�u�W�F�N�g�����Ƃ��̃R�s�[�p�e���v���[�g
//���ӁF���̃I�u�W�F�N�g���p�����Ȃ�����
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

	//�J��
	void Release() override;
};

