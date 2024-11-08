#pragma once
#include "Engine/GameObject.h"

enum ObjectNumber
{
	GOAL = 102,//ゴール
	CHECKPOINT = 103,//チェックポイント
	PLAYER = 105,//プレイヤー
	ITEM = 106,//回収アイテム
	RIFT_L = 107,//リフト右
	RIFT_C = 108,//リフト中
	RIFT_R = 109,//リフト左

	SLIMEA=201,
	SLIMEB,
	SLIMEC,
	BARDA,
	PLANTA,
	ZOMBIEA,
	SKELETONA
	//201 青スライム
	//202 赤スライム
	//203 黄スライム
	//204 鳥A
	//207 植物A
};

class Field :public GameObject
{
	int hImage_;

	int* Map;
	int width;
	int height;

	std::string filename;

	/// <summary>
	/// 何のブロックか
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns>ブロックの名前</returns>
	std::string WhatBlock(int x, int y);

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（ObjectManager）
	Field(GameObject* parent);

	//デストラクタ
	~Field();

	//初期化
	void Initialize() override;

	void Reset();

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	/// <summary>
	/// ファイルの名前をセットする
	/// </summary>
	/// <param name="_filename">ファイルの名前</param>
	void SetFileName(std::string _filename) { filename = _filename; };

	/// <summary>
	/// 下方向の当たり判定のチェック
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns></returns>
	int CollisionDownCheck(int x, int y);

	/// <summary>
	/// 上方向の当たり判定のチェック
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns></returns>
	int CollisionUpCheck(int x, int y);

	/// <summary>
	/// 左方向の当たり判定チェック
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns></returns>
	int CollisionLeftCheck(int x, int y);

	/// <summary>
	/// 右方向の当たり判定チェック
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns></returns>
	int CollisionRightCheck(int x, int y);
	
	/// <summary>
	/// オブジェクトとの当たり判定をチェック
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns></returns>
	bool CollisionObjectCheck(int x, int y);
};

