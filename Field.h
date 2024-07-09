#pragma once
#include "Engine/GameObject.h"

class Field :public GameObject
{
	int hImage_;

	int* Map;
	int width;
	int height;

	std::string filename;

	bool IsWallBlock(int x, int y);

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
};

