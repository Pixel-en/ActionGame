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
		float range_;
	};

	virtual void UpdateIdol() {};
	virtual void UpdateAttack() {};
	virtual void UpdateMove() {};
	virtual void UpdateDamege() {};
	virtual void UpdateDeath() {};

	XMFLOAT3 CenterTransPos_;

	//無敵かどうか
	bool invincible_;
	//時間計測
	float invincibleTimer_;

	//当たり判定の左上
	VECTOR LU;
	//当たり判定の大きさ
	VECTOR Hitbox_;

protected:

	EnemyAnimParts Eanim_;
	EParameter Eparam_;

	XMFLOAT3 originpos_;
	float Gaccel = 0;

	void AnimationCalculation();

	float EPDistance();

	void SetLUPOINT(VECTOR _lu) { LU = _lu; };
	void SetHitBox(VECTOR _box) { Hitbox_ = _box; };
	
	/// <summary>
	/// プレイヤーが範囲内に存在しているかどうか
	/// </summary>
	/// <param name="_range">半径</param>
	/// <returns>存在しているか</returns>
	bool IsExistPlayer(float _range);

	/// <summary>
	/// 当たり判定の中心をセットする
	/// </summary>
	/// <param name="_trans">当たり判定の左上の点</param>
	/// <param name="_size">当たり判定のサイズ</param>
	void SetCenterTransPos(XMFLOAT3 _trans, VECTOR _size);

	void SetHitTransPos(XMFLOAT3 _pos);

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	virtual void Initialize() override;

	virtual void Reset() override;
	virtual void Reset(XMFLOAT3 pos);

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//開放
	virtual void Release() override;

	void StatusReader(int _enemyNumber);

	void StatusDamege();

	void HitDamege(int _damege);

	XMFLOAT3 GetCenterTransPos() { return CenterTransPos_; };

	XMFLOAT3 GetHitTransPos();

	VECTOR GetHitBox() override;
};

