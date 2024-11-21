#pragma once
#include "Engine/GameObject.h"

//クリアのクラス
class Clear :public GameObject
{
	bool isgoal_;	//ゴールしたかどうか
	bool isGetM_;	//材料を全部取った
	bool isKillE_;
	bool ischeck_;	//チェックポイントを通ったかどうか
	int Mcount_;		//材料の数
	int Ecount_;		//敵の数

	bool isFlag_;	//次のステージに移動していいか

	bool isBonusEnemy_;
	bool isBonusMaterial_;

	void BonusScore();
public:

	bool GetFlag() { return isFlag_; };


	//コンストラクタ
	Clear(GameObject* parent);

	//デストラクタ
	~Clear();

	//初期化
	void Initialize() override;

	void Reset();

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void AddMcount() { Mcount_ += 1; };
	void AddEcount() { Ecount_ += 1; };

	void DeleteMaterial() { Mcount_ = -1; }
	void DeleteEnemy() { Ecount_ = -1; }
	bool GetBonusEnemy() { return isBonusEnemy_; };
	bool GetBonusMaterial() { return isBonusMaterial_; };
};

