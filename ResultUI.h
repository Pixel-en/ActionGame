#pragma once
#include "Engine/GameObject.h"
#include "OutText.h"

class ResultUI :public GameObject
{
	OutText* text_;

	float TimeToScoreTimer{ 2.0 };

	float time_;

	float oneSecond_;
public:

	ResultUI(GameObject* parent);

	~ResultUI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

