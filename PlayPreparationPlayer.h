#pragma once
#include "Engine/GameObject.h"

const int ATTACKTYPENUM{ 5 };
const int PARAMMEMORY{ 5 };	//ステータスの最大割り振り

class PlayPreparationPlayer :public GameObject
{

	int hImage_;

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

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	PlayPreparationPlayer(GameObject* parent);

	//デストラクタ
	~PlayPreparationPlayer();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

