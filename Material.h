#pragma once
#include "Object.h"
#include <vector>

//材料のクラス
class Material :public Object
{
	int sizeX_;
	int sizeY_;

	std::vector<std::string> Mlist;
	float Gaccel;

	float durability_;	//耐久(秒)
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Material(GameObject* parent);

	//デストラクタ
	~Material();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Mining(float _mintime);

};

