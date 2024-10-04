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
	int FCmax_;	//フレームカウントの最大
	int AFmax_;	//アニメーションのカウントの最大
	int RCmax_[ATTACKTYPENUM];	//リチャージ時間の最大
	int animframe_;	//アニメーションのフレームカウント
	int framecnt_;	//フレームのカウント
	int Rechagecnt_[ATTACKTYPENUM];	//リチャージのカウント
	bool isAttack_[ATTACKTYPENUM]{ false,false,false,false,false };

	void Update(int& _FCmax,int& _AFmax);

	void Attack1();
	void Attack2();
	void Attack3();
	void Magic1();
	void Magic2();

	void Reset(int type);
}