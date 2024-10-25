#include "Object.h"

namespace {
	const float ENEMY_GRAVITY{ 9.8f / 60.0f };
}

class Enemy :public Object {

	const VECTOR IMAGESIZE{ 64.0f,64.0f };
	const VECTOR HITBOXSIZE{ 32.0f,32.0f };

	enum EAnimation {
		IDOL,
		ATTACK,
		MOVE,
		HURT,
		DEATH,
	};
	EAnimation animtype_;
	EAnimation BEanimtype_;


	virtual void UpdateIdol();
	virtual void UpdateAttack();
	virtual void UpdateMove();
	virtual void UpdateHurt();
	virtual void UpdateDeath();

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Enemy(GameObject* parent);

	//デストラクタ
	virtual ~Enemy();

	//初期化
	virtual void Initialize() override;

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//開放
	virtual void Release() override;
};