#pragma once
#include <DxLib.h>

const int ATTACKTYPENUM{ 5 };

namespace PlayerAttack {

	enum Attacktype
	{
		ATTACK1=0,
		ATTACK2,
		ATTACK3,
		MAGIC1,
		MAGIC2,
		MAX,
	};

	struct AttackStatus
	{
		int Damage;
		int Range;
		int AF;
		int FC;
		int RC;
	};

	AttackStatus type[ATTACKTYPENUM];

	bool attackon_;

	void Update(int& _FCmax,int& _AFmax,int& _animtype);

	void Attack(int type);

	void Reset(int type);
}