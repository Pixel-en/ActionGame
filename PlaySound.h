#pragma once
#include "Engine/GameObject.h"
#include <map>

class Playsound :public GameObject
{
	std::map<std::string,int> hSound_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Playsound(GameObject* parent);

	//デストラクタ
	~Playsound();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SoundON(std::string str);

	void PlayMusics(std::string str);
};

