#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };
const int STATUSMEMORY{ 5 };	//ステータスの最大割り振り

class Player :public GameObject
{

	int hImage_;

	//重力加速度
	float Gaccel_;


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
		COLLECTION,
		MAGIC,
		DAMAGE,
		DEATH,
	};
	struct AnimParts
	{
		Animation animtype_;	//アニメーションの種類
		Animation BEanimtype_;	//前のフレームのアニメーション
		int AFmax_;		//アニメーションのフレーム数
		int animframe_;	//現在アニメーションが何フレーム目か
		int AFCmax_;	//アニメーションが変わるまでのフレーム数
		int animframecount_;	//現在アニメーションが変わるまで何フレーム目か

	};
	struct Status
	{
		int strength_;	//攻撃力
		int speed_;		//スピード
		int hp_;		//体力
		int technic_;	//採取

	};
	struct StatusCorrection
	{
		float strength_;
		int speed_;		//スピード
		int hp_;		//体力
		int technic_;	//採取
	};

	AnimParts anim_;
	Status status_;
	StatusCorrection StaCorre_[STATUSMEMORY];

	/*----------関数----------*/

	/// <summary>
	/// スクロールの計算とポジションへのセット
	/// </summary>
	void CameraScroll();

	/// <summary>
	/// プレイヤーの動き
	/// </summary>
	void MoveControl();

	/// <summary>
	/// ステータスを読み込む
	/// </summary>
	void LoadStates();

	
public:

	//当たり判定
	HitObject* hitobject_;

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
		if (anim_.animtype_ == Animation::IDOL)
			return true;
		return false;
	};

	bool isDie() {
		if (anim_.animtype_ == Animation::DEATH)
			return true;
		return false;
	};

};

