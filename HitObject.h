#pragma once
#include "Field.h"

/// <summary>
/// 地形との当たり判定
/// </summary>
class HitObject
{
	//VECTOR Lu_, Ru_, Ld_, Rd_;
	SIZE size_;
	GameObject* obj_;
	Field* field;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Lu">左上の点</param>
	/// <param name="_Ru">右上の点</param>
	/// <param name="_Ld">左下の点</param>
	/// <param name="_Rd">右下の点</param>
	/// <param name="_obj">チェック対象のオブジェクト</param>
	//HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj);

	HitObject(SIZE _size, GameObject* _obj);

	//デストラクタ
	~HitObject();

	/// <summary>
	/// 右側の当たり判定と押し出し
	/// </summary>
	/// <returns>当たっているか</returns>
	bool RightCollisionCheck();

	/// <summary>
	/// 左側の当たり判定と押し出し
	/// </summary>
	/// <returns>当たっているか</returns>
	bool LeftCollisionCheck();
	
	/// <summary>
	/// 上側の当たり判定と押し出し
	/// </summary>
	/// <returns>当たっているか</returns>
	bool UpCollisionCheck();

	/// <summary>
	/// 下側の当たり判定と押し出し
	/// </summary>
	/// <returns>当たっているか</returns>
	bool DownCollisionCheck();

	/// <summary>
	/// すべての当たり判定のチェックと押し出し　下→上→左→右の順番
	/// </summary>
	/// <returns>当たっているかの4ビット列</returns>
	short AllCollisionCheck();

	/// <summary>
	/// ビット列で指定した当たり判定のチェックと押し出し
	/// </summary>
	/// <param name="_bit">操作したい4ビット列　左から下、上、左、右</param>
	/// <returns>当たっているかの4ビット列</returns>
	short SelectCollisionCheck(short _bit);

};

