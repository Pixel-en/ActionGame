#pragma once
#include "Object.h"
#include "Camera.h"

//継承先全体で使うもののみ
namespace {
	const float GRAVITY{ 9.8f / 60.0f };

}

class Enemy :public Object
{
protected:

	enum EAnimation
	{
		NONE=-1,
		IDOL,
		ATTACK,
		MOVE,
		DAMEGE,
		DEATH,
	};

private:

	struct EnemyAnimParts
	{
		EAnimation animtype_;
		EAnimation BEanimtype_;
		int AFmax_;				//アニメーションのフレーム数
		int animframe_;			//現在アニメーションが何フレーム目か
		int AFCmax_;			//アニメーションが変わるまでのフレーム数
		int animframecount_;	//現在アニメーションが変わるまで何フレーム目か
		bool animloop_;			//アニメーションをループするか
		bool Rdir_;				//右を向いているかどうか
		bool animSkip_;			//アニメーションをする場所をスキップするか
	};

	struct EParameter
	{
		float speed_;
		float runspeed_;
		int hp_;
		float movetimer_;
		std::string filename_;
	};

	virtual void UpdateIdol() {};
	virtual void UpdateAttack() {};
	virtual void UpdateMove() {};
	virtual void UpdateDamege() {};
	virtual void UpdateDeath() {};

protected:

	EnemyAnimParts Eanim_;
	EParameter Eparam_;

	XMFLOAT3 originpos_;

	void AnimationCalculation();

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	virtual void Initialize() override;

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//開放
	virtual void Release() override;

	void StatusReader(int _enemyNumber);
};

