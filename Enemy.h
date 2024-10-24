#pragma once
#include "Object.h"
#include "HitObject.h"
#include "Player.h"
#include "Camera.h"
#include "Clear.h"
#include <vector>

//�v���C���[������������v���C���[�̕���
//�U�����Ă���
//
namespace {

	const float ENEMY_ATTACKRANGE{ 101.5f };
	const float ENEMY_GRAVITY{ 9.8f / 60.0f };	//�d��

	const float ENEMY_ATTACKSPEED{ 1500 };
	const float ENEMY_SPEEDDOWN{ 50 };
}

enum ENEMY_TYPE
{
	SLIME_A, SLIME_B, SLIME_C, BARD_A, PLANT_A, ZOMBIE_A, SKELETON_A, ENEMY_TYPE_END
};
const int Status_Size{ 4 };

//�G�̃N���X
class Enemy:public Object
{
protected:
	const SIZE ENEMY_IMAGESIZE{ 48,48 };
	const SIZE ENEMY_HITBOXSIZE{ 48 / 2,48 / 2 };
	const float ENEMY_JUMPHEIGHT{ ENEMY_IMAGESIZE.cx * 1.5f };	//�W�����v�̍���
	const float ENEMY_LOOKRANGE{ 150 };

	std::string filename;
	//���ɓ����܂ł̃^�C�}�[
	float movetimer_;
	float baseMovetimer;
	//�����n�߂���
	bool startmove_;
	//�d�͉����x�H
	float Gaccel = 0;

	bool charge;
	//�X�s�[�h
	float speed_;
	float baseSpeed;
	float baseRunSpeed;
	//���m����
	int range_;
	//�ݒu����
	bool onGround_;
	//����
	int dir_;
	int dir_y;//��ԓG�p
	//
	XMFLOAT3 Ppos;
	//�̗�
	int hp_;
	int baseHp;

	int attackfrm_;

	XMFLOAT3 SpawnPoint_;	//�����l
	XMFLOAT3 TargetPoint_;

	float baseHurtTime_;
	float hurtTime_;

	Transform hittransform_;

	enum  EAnimation
	{
		IDOL,
		MOVE,
		RUN,
		ATTACK,
		HURT,
		DEATH
	};

	int state_;
	int BEanimtype_;

	void AnimationCheck();
	bool AnimationEnd();
	int NowAnimFrame();

	/// <summary>
	/// �G�ƃv���C���[�̋���
	/// </summary>
	float EPDistance();
	XMFLOAT3 EPVector();
	XMFLOAT3 TargetPos();

	virtual void UpdateIdol();
	virtual void UpdateMove();
	virtual void UpdateRun();
	virtual void UpdateAttack();
	virtual void UpdateHurt();
	virtual void UpdateDeath();

	//�v���C���[�����m�G���A�ɓ��������ǂ���
	bool IsExistPlayer(float _range);

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

	SIZE GetImageSize();

	void DeadState();

	SIZE GetSize() override;

	bool isdeath() { return (state_ == EAnimation::DEATH); }
	
	void StatusReader(int _enemyNumber);

	VECTOR GetCenter() { return VECTOR{ transform_.position_.x + ENEMY_IMAGESIZE.cx / 2, transform_.position_.y + ENEMY_IMAGESIZE.cy / 2 }; };

	Transform GetHitTransform() { return hittransform_; };
};

