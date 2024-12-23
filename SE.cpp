#include "SE.h"
#include <map>
#include "DxLib.h"
#include "assert.h"

namespace SE{

	std::map<SENAME::SEs, int> sHandol_;
	
}

void SE::InitSE()
{
	DeleteSE();

	sHandol_ = { {SENAME::SEs::T_Choise,    LoadSoundMem("Assets\\Sounds\\SE\\Choise.mp3")},
				 {SENAME::SEs::Pr_Choise,	LoadSoundMem("Assets\\Sounds\\SE\\Choise2.mp3")},
				 {SENAME::SEs::Pr_Chenge,	LoadSoundMem("Assets\\Sounds\\SE\\Chenge.mp3")},
				 {SENAME::SEs::G_P_Attack,  LoadSoundMem("Assets\\Sounds\\SE\\Attack.mp3")},
				 {SENAME::SEs::G_P_Death,   LoadSoundMem("Assets\\Sounds\\SE\\death.mp3")},
				 {SENAME::SEs::G_E_Attack,  LoadSoundMem("Assets\\Sounds\\SE\\EAttack.mp3")},
				 {SENAME::SEs::G_E_Death,   LoadSoundMem("Assets\\Sounds\\SE\\Edeath.mp3")},
				 {SENAME::SEs::G_Flag,      LoadSoundMem("Assets\\Sounds\\SE\\Flag.mp3")},
				 {SENAME::SEs::G_Ladder,    LoadSoundMem("Assets\\Sounds\\SE\\ladder.mp3")},
				 {SENAME::SEs::G_Mine,      LoadSoundMem("Assets\\Sounds\\SE\\mine.mp3")},
				 {SENAME::SEs::G_Rune,      LoadSoundMem("Assets\\Sounds\\SE\\Rune.mp3")},
				 {SENAME::SEs::R_Score,     LoadSoundMem("Assets\\Sounds\\SE\\Score.mp3")},
	};
	for (auto i : sHandol_)
		assert(i.second >= 0);
}

int SE::PlaySE(SENAME::SEs _se)
{
	//çƒê∂Ç≥ÇÍÇƒÇ»Ç¢Ç»ÇÁ
	if (CheckSoundMem(sHandol_[_se]) == 0) {
		PlaySoundMem(sHandol_[_se], DX_PLAYTYPE_BACK);
		return 1;
	}
	//çƒê∂Ç≥ÇÍÇƒÇ¢ÇÈÇ»ÇÁ
	else if (CheckSoundMem(sHandol_[_se]) == 1)
		return 1;

	return 0;
}

int SE::CheckSE(SENAME::SEs _se)
{
	if (CheckSoundMem(sHandol_[_se]) == 1)
		return 1;
	return 0;
}

void SE::StopSE(SENAME::SEs _se)
{
	if (CheckSoundMem(sHandol_[_se]) == 1)
		StopSoundMem(sHandol_[_se]);
}

void SE::StopSE()
{
	for (auto i : sHandol_) {
		if (CheckSoundMem(i.second) == 1)
			StopSoundMem(i.second);
	}
}

void SE::DeleteSE(SENAME::SEs _se)
{
	DeleteSoundMem(sHandol_[_se]);
}

void SE::DeleteSE()
{
	InitSoundMem();
}
