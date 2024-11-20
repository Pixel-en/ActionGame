#pragma once
#include "Object.h"



class Explosion :
    public Object
{
	const int EXPLOSION_ANIMATION{ 4 };
	//int framecnt_{ 0 };

	SIZE explosionSize_{ 160,160 };
	SIZE explosionHitBoxSize_;

	int explosionType_;

public:

	enum EXPLOSION_TYPE
	{
		FIRE,
	};

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Explosion(GameObject* parent);

	//デストラクタ
	~Explosion();


	//初期化
	void Initialize() override;
	void Initialize(int _type,SIZE _hitBox);

	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	SIZE GetSize() override;

	VECTOR GetCenter() { return VECTOR{ transform_.position_.x + explosionSize_.cx / 2, transform_.position_.y + explosionSize_.cy / 2 }; };

	bool AnimationEnd();

	void SetPosition(XMFLOAT3 position) {
		transform_.position_.x = position.x; 
		transform_.position_.y = position.y + explosionHitBoxSize_.cy / 4;
		transform_.position_.z = position.z;
	}
};

