#pragma once
#include "Engine/GameObject.h"


//�I�u�W�F�N�g�����Ƃ��̃R�s�[�p�e���v���[�g
//���ӁF���̃I�u�W�F�N�g���p�����Ȃ�����
class ClearLogo :public GameObject
{
	int hImage_;

	bool output_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	ClearLogo(GameObject* parent);

	//�f�X�g���N�^
	~ClearLogo();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

