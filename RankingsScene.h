#pragma once
#include"Engine//GameObject.h"
class RankingsScene :
    public GameObject
{
public:
	RankingsScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
private:
};

