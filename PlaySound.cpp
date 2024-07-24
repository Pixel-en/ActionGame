#include "PlaySound.h"

Playsound::Playsound(GameObject* parent)
	:GameObject(parent,"Playsound")
{
}

Playsound::~Playsound()
{
	InitSoundMem();
}

void Playsound::Initialize()
{
	hSound_ = { {"Attack",LoadSoundMem("Assets\\Sound\\Attack.mp3")},
				{"EAttack",LoadSoundMem("Assets\\Sound\\EAttack.mp3")},
				{"Death",LoadSoundMem("Assets\\Sound\\death.mp3")},
				{"EDeath",LoadSoundMem("Assets\\Sound\\Edeath.mp3")},
				{"Mine",LoadSoundMem("Assets\\Sound\\mine.mp3")}, 
				{"Choise",LoadSoundMem("Assets\\Sound\\Choise.mp3")},
				{"Ladder",LoadSoundMem("Assets\\Sound\\ladder.mp3")},
				{"Flag",LoadSoundMem("Assets\\Sound\\Flag.mp3")}, 
				{"Rune",LoadSoundMem("Assets\\Sound\\Rune.mp3")},
				{"Clear",LoadSoundMem("Assets\\Sound\\clear01.mp3")}, };
	for (auto i:hSound_) {
		assert(i.second > 0);
	}
}

void Playsound::Update()
{
	for (auto i : hSound_) {
		if (CheckSoundMem(i.second) <= 0)
			StopSoundMem(i.second);
	}
}

void Playsound::Draw()
{
}

void Playsound::Release()
{
}

void Playsound::SoundON(std::string str)
{
	if(hSound_.find(str)!=hSound_.end())
		PlaySoundMem(hSound_[str], DX_PLAYTYPE_BACK);
}

void Playsound::PlayMusics(std::string str)
{	
	StopMusic();
	if (str == "Play") {
		PlayMusic("Assets\\Sound\\Play.mp3", DX_PLAYTYPE_LOOP);

		SetVolumeMusic(255);
		return;
	}
	if(str=="Title")
		PlayMusic("Assets\\Sound\\Start.mp3", DX_PLAYTYPE_LOOP);
	if(str=="Clear")
		PlayMusic("Assets\\Sound\\Clear.mp3", DX_PLAYTYPE_LOOP);

	SetVolumeMusic(255);

}
