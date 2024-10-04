#include "PlayerAttack.h"

void PlayerAttack::Update(int& _FCmax, int& _AFmax)
{
	if (CheckHitKey(KEY_INPUT_U)) {
		if(Rechagecnt_[Attack::ATTACK1]>RCmax_[Attack::ATTACK1])
			Attack1();
	}
	if (CheckHitKey(KEY_INPUT_I)) {
		if (Rechagecnt_[Attack::ATTACK2] > RCmax_[Attack::ATTACK2])
			Attack2();
	}
	if (CheckHitKey(KEY_INPUT_O)) {
		if (Rechagecnt_[Attack::ATTACK3] > RCmax_[Attack::ATTACK3])
			Attack3();
	}
	if (CheckHitKey(KEY_INPUT_J)) {
		if (Rechagecnt_[Attack::MAGIC1] > RCmax_[Attack::MAGIC1])
			Magic1();
	}
	if (CheckHitKey(KEY_INPUT_K)) {
		if (Rechagecnt_[Attack::MAGIC2] > RCmax_[Attack::MAGIC2])
			Magic2();
	}

	for (int i = 0; i < ATTACKTYPENUM; i++) {
		if (isAttack_[i])
			Rechagecnt_[i]++;
	}
}

void PlayerAttack::Attack1()
{
	Reset(Attack::ATTACK1);
	isAttack_[Attack::ATTACK1] = true;
}

void PlayerAttack::Attack2()
{
	Reset(Attack::ATTACK2);
	isAttack_[Attack::ATTACK2] = true;
}

void PlayerAttack::Attack3()
{
	Reset(Attack::ATTACK3);
	isAttack_[Attack::ATTACK3] = true;
}

void PlayerAttack::Magic1()
{
	Reset(Attack::MAGIC1);
	isAttack_[Attack::MAGIC1] = true;
}

void PlayerAttack::Magic2()
{
	Reset(Attack::MAGIC2);
	isAttack_[Attack::MAGIC2] = true;

}

void PlayerAttack::Reset(int type)
{
	Damage = 0;
	Range = 0;
	AFmax_ = 0;
	FCmax_ = 0;
	animframe_ = 0;
	framecnt_ = 0;
	RCmax_[type] = 0;
	Rechagecnt_[type] = 0;
	isAttack_[type] = false;
}
