#pragma once
#include "Engine/GameObject.h"
#include "HitObject.h"

const int ATTACKTYPENUM{ 5 };
const int PARAMMEMORY{ 5 };	//ステータスの最大割り振り

class Player :public GameObject
{

	int hImage_;

	//重力加速度
	float Gaccel_;
	//無敵
	bool invincible_;

	bool isjump_;

	float miningtime_;

public:

	//アニメーションの番号
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
		MAGIC,
		COLLECTION,
		DAMAGE,
		DEATH,
		RESET = 20,
	};

private:

	//アニメーションに必要なパーツ
	struct AnimParts
	{
		Animation animtype_;	//アニメーションの種類
		Animation BEanimtype_;	//前のフレームのアニメーション
		int AFmax_;				//アニメーションのフレーム数
		int animframe_;			//現在アニメーションが何フレーム目か
		int AFCmax_;			//アニメーションが変わるまでのフレーム数
		int animframecount_;	//現在アニメーションが変わるまで何フレーム目か
		bool animloop_;			//アニメーションをループするか
		bool Rdir_;				//右を向いているかどうか
		bool animSkip_;			//アニメーションをする場所をスキップするか
	};
	//プレイヤーのパラメータ
	struct Parameter
	{
		int strength_;	//攻撃力
		int speed_;		//スピード
		int hp_;		//体力
		int technic_;	//採取

	};
	//パラメータによる補正
	struct ParameterCorrection
	{
		float strength_;
		int speed_;		//スピード
		int hp_;		//体力
		float technic_;	//採取
	};

	AnimParts anim_;
	Parameter param_;
	ParameterCorrection ParamCorre_[PARAMMEMORY];

	enum AttackType
	{
		TNONE,
		ATTACKT,
		ATTACK2T,
		ATTACK3T,
		MAGIC1T,
		MAGIC2T,
	};

	struct PlayerAttackParts {
		int power_;
		int range_;
		int attackframe_;
		int recharge_;
	};

	PlayerAttackParts attack_[6];
	AttackType Atype_;
	
	int Damege;

	bool attackbuttondown;

	float rechargetimer_[ATTACKTYPENUM];

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
	/// プレイヤーのアクション
	/// </summary>
	/// <returns>アクション中かどうか</returns>
	bool ActionControl();

	/// <summary>
	/// パラメータを読み込む
	/// </summary>
	void LoadParameter();

	/// <summary>
	/// アニメーションの状態やセットの処理
	/// </summary>
	void AnimStatus();

	/// <summary>
	/// ステートをDeathに
	/// </summary>
	void DeadState();

	/// <summary>
	/// 攻撃時のアニメーション
	/// </summary>
	void AttackAnim();

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

	/*基本外部から参照する用*/

	/// <summary>
	/// ノックバックの方向を計算する
	/// </summary>
	/// <param name="_vec">中心座標</param>
	/// <returns>方向</returns>
	VECTOR KnockBackDir(VECTOR _vec);

	XMFLOAT3 GetHitBoxPosition();

	/// <summary>
	/// ダメージを受けたとき
	/// </summary>
	/// <param name="_dir">ノックバックの方向</param>
	void HitDamage(VECTOR _dir);

	//プレイヤーの状態と一致しているか
	bool IsAnimState(Animation _anim) {
		if (anim_.animtype_ == _anim)
			return true;
		return false;
	}

	/// <summary>
	/// 当たり判定の時のTransformを取得する
	/// </summary>
	/// <returns>当たり判定時のTransform</returns>
	Transform GetHitTrans();

	/// <summary>
	/// 当たり判定のボックスを返す
	/// </summary>
	/// <returns>当たり判定のボックス</returns>
	VECTOR GetHitBox();

	float GetMiningTime() { return miningtime_; };

	bool PlayerAttackHitCheck(XMFLOAT3 _trans,VECTOR _hitbox);

	int GetDamege() { return Damege; };
};

