#pragma once
#include "Engine/GameObject.h"

const int ATTACKTYPENUM{ 5 };
const int PARAMMEMORY{ 5 };	//�X�e�[�^�X�̍ő劄��U��

class PlayPreparationPlayer :public GameObject
{

	int hImage_;

public:

	//�A�j���[�V�����̔ԍ�
	enum Animation {
		NONE = -1,
		IDOL = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		ATTACK2,
		ATTACK3,
		CLIMB,
		MAGIC,
		COLLECTION,
		DAMAGE,
		DEATH,
		RESET = 20,
	};

private:

	//�A�j���[�V�����ɕK�v�ȃp�[�c
	struct AnimParts
	{
		Animation animtype_;	//�A�j���[�V�����̎��
		Animation BEanimtype_;	//�O�̃t���[���̃A�j���[�V����
		int AFmax_;				//�A�j���[�V�����̃t���[����
		int animframe_;			//���݃A�j���[�V���������t���[���ڂ�
		int AFCmax_;			//�A�j���[�V�������ς��܂ł̃t���[����
		int animframecount_;	//���݃A�j���[�V�������ς��܂ŉ��t���[���ڂ�
	};
	//�v���C���[�̃p�����[�^
	struct Parameter
	{
		int strength_;	//�U����
		int speed_;		//�X�s�[�h
		int hp_;		//�̗�
		int technic_;	//�̎�

	};
	//�p�����[�^�ɂ��␳
	struct ParameterCorrection
	{
		float strength_;
		int speed_;		//�X�s�[�h
		int hp_;		//�̗�
		float technic_;	//�̎�
	};

	AnimParts anim_;
	Parameter param_;
	ParameterCorrection ParamCorre_[PARAMMEMORY];

	enum AttackType
	{
		TNONE,
		ATTACKT,
		ATTACK2T,
		ATTACK3T,
		MAGIC1T,
		MAGIC2T,
	};

	struct PlayerAttackParts {
		int power_;
		int range_;
		int attackframe_;
		int recharge_;
	};

	PlayerAttackParts attack_[6];
	AttackType Atype_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	PlayPreparationPlayer(GameObject* parent);

	//�f�X�g���N�^
	~PlayPreparationPlayer();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

