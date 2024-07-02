#pragma once
#include "Engine/GameObject.h"


class Player :public GameObject
{

	int hImage_;

	float pdir_;	//プレイヤーの向き
	void TestFunc();
	bool onjump_;	//ジャンプしているか

	bool flagon_;

	enum Animation {
		NONE = -1,
		IDOL = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		CLIMB,
		CRAFT,
		PUSH,
		DAMAGE,
		DEATH,
	};

	Animation animtype_;	//アニメーションの種類
	Animation BEanimtype_;


	bool attackon_;	//攻撃中かどうか
	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数
	bool attackbuffer_;	//攻撃後の待機中かどうか
	float bufferTime_;	//待機時間


	bool HitAttack(int _x, int _y, SIZE _size);

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

};

