#pragma once
#include "Object.h"

//�v���C���[������������v���C���[�̕���
//�U�����Ă���
//

//�G�̃N���X
class Enemy:public Object
{

	float movetimer_;
	bool startmove_;

	float Gaccel = 0;

	float speed_;
	int range_;
	bool onGround_;

	int framecnt_;	//�t���[���̃J�E���g
	int FCmax_;	//�t���[���J�E���g�̍ő�l
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int AFmax_;		//�A�j���[�V�����̃t���[����

	XMFLOAT3 SpawnPoint_;	//�����l

	enum  Animation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		DEATH
	};

	Animation animtype_;

	/// <summary>
	/// �G�ƃv���C���[�̋���
	/// </summary>
	float EPDistance();

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();

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
	bool IsExistPlayer(float _range);

};

