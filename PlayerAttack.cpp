#include "PlayerAttack.h"
#include "Engine/CsvReader.h"
#include "Enemy.h"

void PlayerAttack::Update(int& _FCmax, int& _AFmax,int& _animtype)
{
	if (CheckHitKey(KEY_INPUT_0))
		Attack(0);



	std::list<Enemy*> enemies = GetParent()->FindGameObjects<Enemy>();
}

void PlayerAttack::Attack(int _type)
{
	attackon_ = true;
}

void PlayerAttack::Reset(int _type)
{
	enum States
	{
		DAMAGE,
		RANGE,
		FRAME,
		RECHAGE,
		MAX
	};


	CsvReader* csv = new CsvReader("Assets\\Status\\PlayerAttack.csv");
	for (int k = 0; k < ATTACKTYPENUM; k++) {
		for (int i = 1; i < csv->GetLines(); i++) {
			type[k].Damage = csv->GetInt(i, States::DAMAGE);
			type[k].Range = csv->GetInt(i, States::RANGE);
			type[k].FC = csv->GetInt(i, FRAME);
			type[k].RC = csv->GetInt(i, States::RECHAGE);
		}
	}
}
