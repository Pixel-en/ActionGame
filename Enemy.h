#pragma once
#include "Object.h"
#include "HitObject.h"

//�v���C���[������������v���C���[�̕���
//�U�����Ă���
//

//�G�̃N���X
class Enemy:public Object
{

	float movetimer_;
	bool startmove_;

	float Gaccel = 0;

	bool charge;

	float speed_;
	int range_;
	bool onGround_;

	int dir_;
	XMFLOAT3 Ppos;


	int attackfrm_;

	XMFLOAT3 SpawnPoint_;	//�����l

	enum  EAnimation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		HURT,
		DEATH
	};

	EAnimation animtype_;
	EAnimation BEanimtype_;

	void AnimationCheck();

	/// <summary>
	/// �G�ƃv���C���[�̋���
	/// </summary>
	float EPDistance();

	void UpdateIdol();
	void UpdateMove();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDeath();


	HitObject* hitobj_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize() override;

	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool IsHitting() override;

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;
private:

	//�v���C���[�����m�G���A�ɓ��������ǂ���
	bool IsExistPlayer(float _range);

};

