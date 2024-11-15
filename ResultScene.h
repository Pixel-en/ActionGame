#pragma once
#include "Engine/GameObject.h"
#include "ScoreAndTime.h"
#include "TitleText.h"

class ResultScene 
	: public GameObject
{
	TitleText* scoreText;
	TitleText* timeText;
	
	float TimeToScoreTimer{ 2.0 };

	float time_;

	float a_{ 0 };
public:
	ResultScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

