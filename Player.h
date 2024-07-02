#pragma once
#include "Engine/GameObject.h"


class Player :public GameObject
{

	int hImage_;

	float pdir_;	//�v���C���[�̌���
	void TestFunc();
	bool onjump_;	//�W�����v���Ă��邩

	bool flagon_;

	enum Animation {
		NONE = -1,
		IDOL = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		CLIMB,
		CRAFT,
		PUSH,
		DAMAGE,
		DEATH,
	};

	Animation animtype_;	//�A�j���[�V�����̎��
	Animation BEanimtype_;


	bool attackon_;	//�U�������ǂ���
	int framecnt_;	//�t���[���̃J�E���g
	int FCmax_;	//�t���[���J�E���g�̍ő�l
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int AFmax_;		//�A�j���[�V�����̃t���[����
	bool attackbuffer_;	//�U����̑ҋ@�����ǂ���
	float bufferTime_;	//�ҋ@����


	bool HitAttack(int _x, int _y, SIZE _size);

public:

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

};

