#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

class Object :public GameObject
{
protected:
	int hImage_;

	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数

	SIZE hitsize_;

	HitObject* hitobj_;

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

	virtual int GetImageHandle() { return hImage_; }
	virtual Transform GetHitTrans();
	virtual SIZE GetSize();

	virtual VECTOR GetHitBox();
};

