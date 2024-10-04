#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };

class Player :public GameObject
{
	enum Attacktype
	{
		ATTACKTYPE1 = 0,
		ATTACKTYPE2,
		ATTACKTYPE3,
		MAGICTYPE1,
		MAGICTYPE2,
		MAX,
	};

	struct AttackStatus
	{
		int Damage;
		int Range;
		int AF;
		int ASF;	//攻撃フレームのはじめ
		int AEF;	//攻撃フレームの終わり
		int FC;
		int RC;
	};
	AttackStatus type[ATTACKTYPENUM];
	void AttackUpdate();
	void Attack(int _type);
	void AttackReset(int _type);



	int hImage_;

	float Gaccel_;	//重力加速

	bool pRdir_;	//プレイヤーが右を向いているか
	bool onjump_;	//ジャンプしているか

	bool flagon_;

	enum Animation {
		NONE = -1,
		IDOL = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		ATTACK2,
		ATTACK3,
		CLIMB,
		CRAFT,
		PUSH,
		DAMAGE,
		DEATH,
	};

	Animation animtype_;	//アニメーションの種類
	Animation BEanimtype_;	//前のフレームのアニメーション


	bool attackon_;	//攻撃中かどうか
	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数
	bool attackbuffer_;	//攻撃後の待機中かどうか
	float bufferTime_;	//待機時間

	//前フレームにリフトに乗っていたかどうか
	bool beCol_;

	bool HitAttack(int _x, int _y, SIZE _size);
	HitObject* hitobj_;


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool HitCheck(int _x, int _y, SIZE _size);

	XMFLOAT3 GetHitBoxPosition();

	void DeadState();

	bool isIdol() {
		if (animtype_ == Animation::IDOL)
			return true;
		return false;
	};

	bool isDie() {
		if (animtype_ == Animation::DEATH)
			return true;
		return false;
	};

};

