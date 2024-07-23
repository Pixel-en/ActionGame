#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
	int hImage_;

public:
	TitleScene(GameObject* parent);
	~TitleScene();

	//‰Šú‰»
	void Initialize() override;
	void Update() override;
	void Draw() override;
};