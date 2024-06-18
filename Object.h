#pragma once
#include "Engine/GameObject.h"

class Object :public GameObject
{
protected:
	int hImage_;

public:

	Object(GameObject* parent);
	Object(GameObject* parent, const std::string& name);

	//デストラクタ
	virtual ~Object();

	//初期化
 	virtual void Initialize() override;

	virtual void Reset();

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//開放
	virtual void Release() override;

	virtual bool IsHitting();
};

