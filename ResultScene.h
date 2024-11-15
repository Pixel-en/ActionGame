#pragma once
#include "Engine/GameObject.h"
#include "ScoreAndTime.h"
#include "TitleText.h"

class ResultScene 
	: public GameObject
{
	TitleText* scoreText;
	TitleText* timeText;
	TitleText* resultText;
	
	float TimeToScoreTimer{ 2.0 };
	const int TimeToScoreValue{ 100 };

	float time_;

	float a_{ 0 };
public:
	ResultScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

