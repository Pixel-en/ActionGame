#pragma once
#include <DxLib.h>

const int ATTACKTYPENUM{ 5 };

namespace PlayerAttack {

	enum Attack
	{
		ATTACK1=0,
		ATTACK2,
		ATTACK3,
		MAGIC1,
		MAGIC2,
		MAX,
	};

	int Damage;
	int Range;
	int FCmax_;	//�t���[���J�E���g�̍ő�
	int AFmax_;	//�A�j���[�V�����̃J�E���g�̍ő�
	int RCmax_[ATTACKTYPENUM];	//���`���[�W���Ԃ̍ő�
	int animframe_;	//�A�j���[�V�����̃t���[���J�E���g
	int framecnt_;	//�t���[���̃J�E���g
	int Rechagecnt_[ATTACKTYPENUM];	//���`���[�W�̃J�E���g
	bool isAttack_[ATTACKTYPENUM]{ false,false,false,false,false };

	void Update(int& _FCmax,int& _AFmax);

	void Attack1();
	void Attack2();
	void Attack3();
	void Magic1();
	void Magic2();

	void Reset(int type);
}