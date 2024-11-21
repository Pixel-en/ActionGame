#pragma once
#include "Engine\GameObject.h"


class TestOpenObject :
	public GameObject
{
	int hImage_;
	int weight;
	int hight;
	int height;
	int frame;
	float timer;
	bool isAnim;
public:
	TestOpenObject(GameObject* parent);

	//デストラクタ
	~TestOpenObject();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	XMFLOAT3 GetHitTransPos();
	VECTOR GetHitBox();
	void Open();
};
