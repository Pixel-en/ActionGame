#pragma once
#include "Object.h"

//�v���C���[������������v���C���[�̕���
//�U�����Ă���
//

//�G�̃N���X
class Enemy:public Object
{
	bool inmoving_;
	XMVECTOR despos_;

	float movetimer_;
	bool startmove_;

	float Gaccel = 0;

	float speed_;
	float distance;
	int range_;
	float EPDistance();
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool IsHitting() override;

	SIZE GetImageSize();

private:

	//�v���C���[�����m�G���A�ɓ��������ǂ���
	bool IsExistPlayer();

};

