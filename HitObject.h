#pragma once
#include "Field.h"

/// <summary>
/// 地形との当たり判定
/// </summary>
class HitObject
{
	VECTOR Lu_, Ru_, Ld_, Rd_;
	VECTOR size_;
	GameObject* obj_;
	Field* field;

	Transform trans_;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Lu">左上の点</param>
	/// <param name="_Ru">右上の点</param>
	/// <param name="_Ld">左下の点</param>
	/// <param name="_Rd">右下の点</param>
	/// <param name="_obj">チェック対象のオブジェクト</param>
	HitObject(VECTOR _Lu, VECTOR _Ru, VECTOR _Ld, VECTOR _Rd, GameObject* _obj);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_size">当たり判定のサイズ</param>
	/// <param name="_obj">オブジェクト</param>
	HitObject(SIZE _size, GameObject* _obj);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_size">当たり判定のサイズ</param>
	/// <param name="_obj">オブジェクト</param>
	HitObject(VECTOR _size, GameObject* _obj);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="trans">当たり判定のヒットボックス</param>
	/// <param name="_size">当たり判定のサイズ</param>
	/// <param name="_obj">オブジェクト</param>
	HitObject(Transform& trans,VECTOR _size, GameObject* _obj);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="trans">当たり判定のヒットボックス</param>
	/// <param name="_size">当たり判定のサイズ</param>
	/// <param name="_obj">オブジェクト</param>
	HitObject(Transform& trans, SIZE _size, GameObject* _obj);

	//デストラクタ
	~HitObject();

	/// <summary>
	/// 当たり判定のヒットボックスのセット
	/// </summary>
	/// <param name="trans">当たり判定のTransform</param>
	void SetHitTransform(Transform trans) { trans_ = trans; };

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

	/// <summary>
	/// オブジェクト同士の当たり判定
	/// </summary>
	/// <param name="_trans1">対象1のTransform</param>
	/// <param name="_size1">対象1の当たり判定のボックス</param>
	/// <param name="_trans2">対象2のTransform</param>
	/// <param name="_size2">対象2の当たり判定のボックス</param>
	/// <returns>当たっているかどうか</returns>
	bool HitObjectANDObject(XMFLOAT3 _trans1,VECTOR _size1, XMFLOAT3 _trans2, VECTOR _size2);

	/// <summary>
	/// ヒットボックスを出力する
	/// </summary>
	/// <param name="trans">出力するtrans</param>
	void DrawHitBox(XMFLOAT3 trans);

	/// <summary>
	/// ヒットボックスを色指定で出力する
	/// </summary>
	/// <param name="trans">出力するtrans</param>
	/// <param name="Red">赤(上限255)</param>
	/// <param name="Green">緑(上限255)</param>
	/// <param name="Blue">青(上限255)</param>
	void DrawHitBox(XMFLOAT3 trans,int Red,int Green,int Blue);

};

