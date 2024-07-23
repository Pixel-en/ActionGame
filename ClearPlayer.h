#pragma once
#include "Engine/GameObject.h"


//オブジェクトを作るときのコピー用テンプレート
//注意：このオブジェクトを継承しないこと
class Clearplayer :public GameObject
{
	int hImage_;

	int framecnt_;	//フレームのカウント
	int FCmax_;	//フレームカウントの最大値
	int animframe_;	//アニメーションのフレームカウント
	int AFmax_;		//アニメーションのフレーム数

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Clearplayer(GameObject* parent);

	//デストラクタ
	~Clearplayer();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

