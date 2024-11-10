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
	};

	virtual void UpdateIdol() {};
	virtual void UpdateAttack() {};
	virtual void UpdateMove() {};
	virtual void UpdateDamege() {};
	virtual void UpdateDeath() {};

protected:

	EnemyAnimParts Eanim_;
	EParameter Eparam_;

	XMFLOAT3 originpos_;

	void AnimationCalculation();

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	virtual void Initialize() override;

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//�J��
	virtual void Release() override;

	void StatusReader(int _enemyNumber);
};

