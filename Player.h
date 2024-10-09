#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };
const int STATUSMEMORY{ 5 };	//�X�e�[�^�X�̍ő劄��U��

class Player :public GameObject
{

	int hImage_;

	//�d�͉����x
	float Gaccel_;


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
		COLLECTION,
		MAGIC,
		DAMAGE,
		DEATH,
	};
	struct AnimParts
	{
		Animation animtype_;	//�A�j���[�V�����̎��
		Animation BEanimtype_;	//�O�̃t���[���̃A�j���[�V����
		int AFmax_;		//�A�j���[�V�����̃t���[����
		int animframe_;	//���݃A�j���[�V���������t���[���ڂ�
		int AFCmax_;	//�A�j���[�V�������ς��܂ł̃t���[����
		int animframecount_;	//���݃A�j���[�V�������ς��܂ŉ��t���[���ڂ�

	};
	struct Status
	{
		int strength_;	//�U����
		int speed_;		//�X�s�[�h
		int hp_;		//�̗�
		int technic_;	//�̎�

	};
	struct StatusCorrection
	{
		float strength_;
		int speed_;		//�X�s�[�h
		int hp_;		//�̗�
		int technic_;	//�̎�
	};

	AnimParts anim_;
	Status status_;
	StatusCorrection StaCorre_[STATUSMEMORY];

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
	/// �X�e�[�^�X��ǂݍ���
	/// </summary>
	void LoadStates();

	
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

	bool HitCheck(int _x, int _y, SIZE _size);

	XMFLOAT3 GetHitBoxPosition();

	void DeadState();

	bool isIdol() {
		if (anim_.animtype_ == Animation::IDOL)
			return true;
		return false;
	};

	bool isDie() {
		if (anim_.animtype_ == Animation::DEATH)
			return true;
		return false;
	};

};

