#pragma once
#include "Engine\GameObject.h"


class OpenObject :
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
	OpenObject(GameObject* parent);

	//デストラクタ
	~OpenObject();

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
	void SetPos(int x,int y);
};
