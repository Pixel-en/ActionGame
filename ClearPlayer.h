#pragma once
#include "Engine/GameObject.h"


//�I�u�W�F�N�g�����Ƃ��̃R�s�[�p�e���v���[�g
//���ӁF���̃I�u�W�F�N�g���p�����Ȃ�����
class Clearplayer :public GameObject
{
	int hImage_;

	int framecnt_;	//�t���[���̃J�E���g
	int FCmax_;	//�t���[���J�E���g�̍ő�l
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int AFmax_;		//�A�j���[�V�����̃t���[����

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Clearplayer(GameObject* parent);

	//�f�X�g���N�^
	~Clearplayer();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

