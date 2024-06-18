#pragma once
#include "Engine/GameObject.h"

//クリアのクラス
class Clear :public GameObject
{
	bool isgoal_;	//ゴールしたかどうか
	bool isGetM_;	//材料を全部取ったか？
	int Mval_;		//とった材料の数
	int Eval_;		//残りの敵の数

	float cleartimer_;	//クリアした後のタイマー

public:

	bool isFlag_;	//次のステージに移動していいか
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

	void SetMaterialValue(int _val) { Mval_ = _val; };
};

