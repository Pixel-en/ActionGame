#pragma once
#include "Engine/GameObject.h"
#include "OutText.h"
#include "Engine/SceneManager.h"

class ResultUI :public GameObject
{
	OutText* text_;

	float TimeToScoreTimer{ 2.0 };

	float time_;

	float oneSecond_;

	bool moveflag_;
	float movetimer_;

	int DrawSpace(float max);

	bool isrank_;

	XINPUT_STATE pad;

	bool recvmove_;

	void CSVReadRank();
	void DrawRank();

	int hImage_;

	bool outranking = false;
	bool check = false;
	int height;

	VECTOR choice1;
	VECTOR choice2;
	bool a;

public:

	ResultUI(GameObject* parent);

	~ResultUI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	bool DrawRankOK() { return isrank_; };

	void isRecvok_(bool _recvok) { recvmove_ = _recvok; };
};

