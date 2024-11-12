#pragma once
#include "Object.h"
#include "Camera.h"

//�p����S�̂Ŏg�����̂̂�
namespace {
	const float GRAVITY{ 9.8f / 60.0f };

}

class Enemy :public Object
{
protected:

	enum EAnimation
	{
		NONE=-1,
		IDOL,
		ATTACK,
		MOVE,
		DAMEGE,
		DEATH,
	};

private:

	struct EnemyAnimParts
	{
		EAnimation animtype_;
		EAnimation BEanimtype_;
		int AFmax_;				//�A�j���[�V�����̃t���[����
		int animframe_;			//���݃A�j���[�V���������t���[���ڂ�
		int AFCmax_;			//�A�j���[�V�������ς��܂ł̃t���[����
		int animframecount_;	//���݃A�j���[�V�������ς��܂ŉ��t���[���ڂ�
		bool animloop_;			//�A�j���[�V���������[�v���邩
		bool Rdir_;				//�E�������Ă��邩�ǂ���
		bool animSkip_;			//�A�j���[�V����������ꏊ���X�L�b�v���邩
	};

	struct EParameter
	{
		float speed_;
		float runspeed_;
		int hp_;
		float movetimer_;
		std::string filename_;
		float range_;
	};

	virtual void UpdateIdol() {};
	virtual void UpdateAttack() {};
	virtual void UpdateMove() {};
	virtual void UpdateDamege() {};
	virtual void UpdateDeath() {};

	XMFLOAT3 CenterTransPos_;

	//���G���ǂ���
	bool invincible_;
	//���Ԍv��
	float invincibleTimer_;

	//�����蔻��̍���
	VECTOR LU;
	//�����蔻��̑傫��
	VECTOR Hitbox_;

protected:

	EnemyAnimParts Eanim_;
	EParameter Eparam_;

	XMFLOAT3 originpos_;
	float Gaccel = 0;

	void AnimationCalculation();

	float EPDistance();

	void SetLUPOINT(VECTOR _lu) { LU = _lu; };
	void SetHitBox(VECTOR _box) { Hitbox_ = _box; };
	
	/// <summary>
	/// �v���C���[���͈͓��ɑ��݂��Ă��邩�ǂ���
	/// </summary>
	/// <param name="_range">���a</param>
	/// <returns>���݂��Ă��邩</returns>
	bool IsExistPlayer(float _range);

	/// <summary>
	/// �����蔻��̒��S���Z�b�g����
	/// </summary>
	/// <param name="_trans">�����蔻��̍���̓_</param>
	/// <param name="_size">�����蔻��̃T�C�Y</param>
	void SetCenterTransPos(XMFLOAT3 _trans, VECTOR _size);

	void SetHitTransPos(XMFLOAT3 _pos);

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	virtual void Initialize() override;

	virtual void Reset() override;
	virtual void Reset(XMFLOAT3 pos);

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//�J��
	virtual void Release() override;

	void StatusReader(int _enemyNumber);

	void StatusDamege();

	void HitDamege(int _damege);

	XMFLOAT3 GetCenterTransPos() { return CenterTransPos_; };

	XMFLOAT3 GetHitTransPos();

	VECTOR GetHitBox() override;
};

