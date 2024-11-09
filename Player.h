#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };
const int PARAMMEMORY{ 5 };	//�X�e�[�^�X�̍ő劄��U��

class Player :public GameObject
{

	int hImage_;

	//�d�͉����x
	float Gaccel_;
	//���G
	bool invincible_;

	bool isjump_;

	float miningtime_;

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
		bool animloop_;			//�A�j���[�V���������[�v���邩
		bool Rdir_;				//�E�������Ă��邩�ǂ���
		bool animSkip_;			//�A�j���[�V����������ꏊ���X�L�b�v���邩
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
	
	int Damege;

	bool attackbuttondown;

	float rechargetimer_[ATTACKTYPENUM];

	/*----------�֐�----------*/

	/// <summary>
	/// �X�N���[���̌v�Z�ƃ|�W�V�����ւ̃Z�b�g
	/// </summary>
	void CameraScroll();

	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	void MoveControl();

	/// <summary>
	/// �v���C���[�̃A�N�V����
	/// </summary>
	/// <returns>�A�N�V���������ǂ���</returns>
	bool ActionControl();

	/// <summary>
	/// �p�����[�^��ǂݍ���
	/// </summary>
	void LoadParameter();

	/// <summary>
	/// �A�j���[�V�����̏�Ԃ�Z�b�g�̏���
	/// </summary>
	void AnimStatus();

	/// <summary>
	/// �X�e�[�g��Death��
	/// </summary>
	void DeadState();

	/// <summary>
	/// �U�����̃A�j���[�V����
	/// </summary>
	void AttackAnim();

public:

	//�����蔻��
	HitObject* hitobject_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iObjectManager�j
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/*��{�O������Q�Ƃ���p*/

	/// <summary>
	/// �m�b�N�o�b�N�̕������v�Z����
	/// </summary>
	/// <param name="_vec">���S���W</param>
	/// <returns>����</returns>
	VECTOR KnockBackDir(VECTOR _vec);

	XMFLOAT3 GetHitBoxPosition();

	/// <summary>
	/// �_���[�W���󂯂��Ƃ�
	/// </summary>
	/// <param name="_dir">�m�b�N�o�b�N�̕���</param>
	void HitDamage(VECTOR _dir);

	//�v���C���[�̏�Ԃƈ�v���Ă��邩
	bool IsAnimState(Animation _anim) {
		if (anim_.animtype_ == _anim)
			return true;
		return false;
	}

	/// <summary>
	/// �����蔻��̎���Transform���擾����
	/// </summary>
	/// <returns>�����蔻�莞��Transform</returns>
	Transform GetHitTrans();

	/// <summary>
	/// �����蔻��̃{�b�N�X��Ԃ�
	/// </summary>
	/// <returns>�����蔻��̃{�b�N�X</returns>
	VECTOR GetHitBox();

	float GetMiningTime() { return miningtime_; };

	bool PlayerAttackHitCheck(XMFLOAT3 _trans,VECTOR _hitbox);

	int GetDamege() { return Damege; };
};

