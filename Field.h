#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class Field :public GameObject
{
	int hImage_;
	CsvReader* csv;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Field(GameObject* parent);

	//デストラクタ
	~Field();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

