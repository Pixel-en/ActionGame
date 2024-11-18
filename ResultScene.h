#pragma once
#include "Engine/GameObject.h"
#include "ScoreAndTime.h"
#include "OutText.h"

class ResultScene 
	: public GameObject
{
	OutText* scoreText;
	OutText* timeText;
	OutText* resultText;
	
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

