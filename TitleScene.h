#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
	int hImage_;
	int hImage2_;

	bool updown;
	bool button_;
	bool decision_;
	float speed;
	float x, y;
	float wait_;


	XINPUT_STATE pad;

public:
	TitleScene(GameObject* parent);
	~TitleScene();

	//èâä˙âª
	void Initialize() override;
	void Update() override;
	void Draw() override;
};